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

void Server::broadcast(QString message)
{
    transportingData.clear();
    QDataStream out(&transportingData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << message;

    for (const auto client : clients) {
        client->write(transportingData);
    }
}

void Server::broadcast(QByteArray bytes)
{
    for (const auto client : clients) {
        client->write(bytes);
    }
}

void Server::deleteClientsInfo()
{
    QMap<qintptr, ClientInfo> tempClients = QMap<qintptr, ClientInfo>();
    for (const auto &client : clients) {
        qintptr desc = client->socketDescriptor();
        if (clientsInfo.count(desc)) {
            ClientInfo *info = clientsInfo[desc];
            tempClients.insert(desc, ClientInfo(info->getName(), info->getIp(), info->getConnectedTime(), (ClientStatuses)info->getStatus()));
        }
    }

    clientsInfo.clear();

    for (auto const &desc : tempClients.keys()) {
        ClientInfo info = tempClients.value(desc, ClientInfo("ERROR", "ERROR", "ERROR", ClientStatuses::DONT_DISTURB));
        clientsInfo.insert(desc, new ClientInfo(
                               info.getName(),
                               info.getIp(),
                               info.getConnectedTime(),
                               (ClientStatuses)info.getStatus()
                               ));
    }
    tempClients.clear();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    serverSocket = new QTcpSocket;
    if (serverSocket->setSocketDescriptor(socketDescriptor)) {
        connect(serverSocket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
        connect(serverSocket, &QTcpSocket::disconnected, this, &Server::handleDisconnect);
        clients.push_back(serverSocket);
        qDebug() << "Connected client: " << socketDescriptor;
    }
    else {
        delete serverSocket;
    }
}

void Server::slotReadyRead()
{
    serverSocket = (QTcpSocket*) sender();
    QByteArray bytes = serverSocket->readAll();
    BasicMessage *message;
    try {
        qDebug() << bytes.length();
        message = new BasicMessage(bytes);
        if (message->getEvent() == SocketEvents::JOIN) {
            qDebug() << "JOIN";

            JoinInfo * info = new JoinInfo(bytes);
            qDebug() << info->getName();
            clientsInfo.insert(serverSocket->socketDescriptor(),
                               new ClientInfo(
                                   info->getName(),
                                   serverSocket->peerAddress().toString(),
                                   QDateTime::currentDateTime().toString(),
                                   ClientStatuses::ONLINE
                                ));
            ClientsInfo *clientsToTransport = new ClientsInfo(clientsInfo.values());
            broadcast(clientsToTransport->getBytes());
            delete clientsToTransport;
        }

        if (message->getEvent() == SocketEvents::MESSAGE) {
            broadcast(bytes);
        }

        delete message;
    } catch (const QException &exception) {
        qDebug() << "FAILED TO CERATE BASIC MESSAGE";
        delete message;
    }
}

void Server::handleDisconnect()
{
    qDebug() << "DISCONNECT TRIGGERED";
    serverSocket = (QTcpSocket*)sender();
    if (serverSocket) {
        auto foundClient = std::find(clients.begin(), clients.end(), serverSocket);
        clients.erase(foundClient);
        serverSocket->deleteLater();
        deleteClientsInfo();

        ClientsInfo *clientsToTransport = new ClientsInfo(clientsInfo.values());
        broadcast(clientsToTransport->getBytes());
        delete clientsToTransport;
    }
}
