#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Client::Instance().init(this);
    connect(&Client::Instance(), SIGNAL(newMessage(QString)), this, SLOT(createMessage(QString)));
    connect(&Client::Instance(), SIGNAL(newMessage(TextMessage)), this, SLOT(createMessage(TextMessage)));
    connect(&Client::Instance(), SIGNAL(clientInfoUpdated(QJsonArray)), this, SLOT(setClients(QJsonArray)));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    Client::Instance().connectToServer("127.0.0.1", 45678);
    JoinInfo * info = new JoinInfo((QString)"edaniel");
    Client::Instance().join(*info);
    delete info;
}


void MainWindow::on_sendButton_clicked()
{
    TextMessage * message = new TextMessage("edaniel", ui->messageInput->text());
    Client::Instance().sendTextMessage(*message);
    ui->messageInput->clear();
    delete message;
}

void MainWindow::createMessage(QString message)
{
    ui->statusbar->showMessage(message);
}

void MainWindow::createMessage(const TextMessage &message)
{
    ui->messagesArea->append(message.getSender() + ":\n" + message.getText() + "\n\n");
    ui->statusbar->showMessage(message.getSender() + ": " + message.getText());
}

void MainWindow::setClients(const QJsonArray &info)
{
    qDebug() << "SET CLIENTS TRIGGERED";
    ui->clientsList->clear();
    for (const auto client : info) {
        QJsonObject clientObject = client.toObject();
        ui->clientsList->append(clientObject["name"].toString() + ": " + clientObject["ip"].toString() + "\n" + clientObject["connected_time"].toString() + "\n\n");
    }
}

