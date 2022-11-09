#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Client::Instance().init(this);
    connect(&Client::Instance(), SIGNAL(newMessage(QString)), this, SLOT(createMessage(QString)));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    Client::Instance().connectToServer("127.0.0.1", 45678);
}


void MainWindow::on_sendButton_clicked()
{
    Client::Instance().sendToServer(ui->messageInput->text());
}

void MainWindow::createMessage(QString message)
{
    ui->statusbar->showMessage(message);
}

