#include "server.h"

Server::Server()
{
    if (this->listen(QHostAddress::LocalHost, 45678)) {
        qDebug() << "Socket started";
    }
    else {
        qDebug() << "SOCKET FAILED TO START";
    }
}

void Server::sendToClient(QString message)
{
    transportingData.clear();
    QDataStream out(&transportingData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << message;
    serverSocket->write(transportingData);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    serverSocket = new QTcpSocket;
    if (serverSocket->setSocketDescriptor(socketDescriptor)) {
        connect(serverSocket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
        connect(serverSocket, &QTcpSocket::disconnected, serverSocket, &QTcpSocket::deleteLater);
        clients.push_back(serverSocket);
    }
    else {
        delete serverSocket;
    }
}

void Server::slotReadyRead()
{
    serverSocket = (QTcpSocket*) sender();
    QDataStream in(serverSocket);
    in.setVersion(QDataStream::Qt_6_2);

    if (in.status() == QDataStream::Ok) {
        QString str;
        in >> str;

    }
    else {
        qDebug() << "DATA STREAM ERROR";
    }
}




