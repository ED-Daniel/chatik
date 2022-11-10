#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->serverLabel->setText(Server::Instance().getIp() + "\t" + QString::number(Server::Instance().getPort()));
    ui->clientsCount->setText(QString::number(Server::Instance().getClientsCount()));

    connect(&Server::Instance(), SIGNAL(clientsUpdated(QJsonArray)), this, SLOT(setClients(QJsonArray)));
    connect(&Server::Instance(), SIGNAL(clientConnected(ClientInfo)), this, SLOT(handleConnect(ClientInfo)));
    connect(&Server::Instance(), SIGNAL(clientDisconnected(ClientInfo)), this, SLOT(handleDisconnect(ClientInfo)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setClients(const QJsonArray &info) {
    ui->clinetsList->clear();
    for (const auto client : info) {
        QJsonObject clientObject = client.toObject();
        ui->clinetsList->append(clientObject["name"].toString() + ": " + clientObject["ip"].toString() + "\n" + clientObject["connected_time"].toString() + "\n\n");
    }
    ui->clientsCount->setText(QString::number(Server::Instance().getClientsCount()));
}

void MainWindow::handleConnect(const ClientInfo &info)
{
    ui->console->append(info.getConnectedTime());
    ui->console->append(info.getName() + "-" + info.getIp() + ": " + "connected");
    ui->clientsCount->setText(QString::number(Server::Instance().getClientsCount()));
}

void MainWindow::handleDisconnect(const ClientInfo &info)
{
    ui->console->append(info.getConnectedTime());
    ui->console->append(info.getName() + "-" + info.getIp() + ": " + "disconnected");
    ui->clientsCount->setText(QString::number(Server::Instance().getClientsCount()));
}

