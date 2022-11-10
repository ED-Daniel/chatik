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
    connectToServer();
}


void MainWindow::on_sendButton_clicked()
{
    TextMessage * message = new TextMessage(Vuex::Instance().username, ui->messageInput->text(), QDateTime::currentDateTime().toString(), Client::Instance().getIp());
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


void MainWindow::on_actionConnect_triggered()
{
    connectToServer();
}

void MainWindow::connectToServer()
{
    Client::Instance().connectToServer(Vuex::Instance().serverIp, Vuex::Instance().port);
    JoinInfo * info = new JoinInfo(Vuex::Instance().username);
    Client::Instance().join(*info);
    delete info;
}


void MainWindow::on_actionDisconnect_triggered()
{
    Client::Instance().disconnect();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionServer_triggered()
{
    ServerConfigDialog * serverConfigDialog = new ServerConfigDialog(this);
    serverConfigDialog->show();
}


void MainWindow::on_actionUsername_triggered()
{
    UsernameEditDialog * usernameEditDialog = new UsernameEditDialog(this);
    usernameEditDialog->show();
}


void MainWindow::on_actionSave_History_triggered()
{
    XmlSaveDialog * saveDialog = new XmlSaveDialog(this);
    saveDialog->show();
}


void MainWindow::on_actionShow_triggered()
{
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
    QImage img("/Users/danielemelyanenko/Documents/QtProjects/ChatiK/Client/ChatiKClient/author.jpg");
    QImage author = img.scaled(img.width() / 6, img.height() / 6);
    QString data = QDate::currentDate().toString("dd.MM.yyyy");
    QLabel *label = new QLabel;
    QPushButton *buttonClose = new QPushButton("Close");

    label->setPixmap(QPixmap::fromImage(author));
    label->setScaledContents(true);

    layout->addWidget(label);
    layout->addWidget(new QLabel("Build version: 6.3.1"));
    layout->addWidget(new QLabel("Qt Version: " + QString(QT_VERSION_STR)));
    layout->addWidget(new QLabel("Daniel Emelyanenko"));
    layout->addWidget(new QLabel("Build date: " + data));
    layout->addWidget(buttonClose);

    dialog->setLayout(layout);
    dialog->show();

    connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
}

