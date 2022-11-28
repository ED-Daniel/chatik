#include "server.h"

void Server::init(QHostAddress ip, quint16 port)
{
    if (this->listen(ip, port)) {
        qDebug() << "Socket started";
    }
    else {
        qDebug() << "SOCKET FAILED TO START";
    }

    this->ip = ip.toString();
    this->port = port;
}

QString Server::getIp()
{
    return ip;
}

quint16 Server::getPort()
{
    return port;
}

uint Server::getClientsCount()
{
    return clients.count();
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
            ClientInfo *info = clientsInfo.take(desc);
            tempClients.insert(desc, ClientInfo(info->getName(), info->getIp(), info->getConnectedTime(), (ClientStatuses)info->getStatus()));
        }
    }

    for (auto const &desc : clientsInfo.keys()) {
        emit clientDisconnected(*clientsInfo[desc]);
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

        if (message->isFile) {
            qDebug() << "FILE";
            broadcast(bytes);
        }

        if (message->getEvent() == SocketEvents::JOIN) {
            qDebug() << "JOIN";

            JoinInfo * info = new JoinInfo(bytes);
            qDebug() << info->getName();
            ClientInfo *newClient = new ClientInfo(
                        info->getName(),
                        serverSocket->peerAddress().toString(),
                        QDateTime::currentDateTime().toString(),
                        info->getStatus()
                     );
            clientsInfo.insert(serverSocket->socketDescriptor(), newClient);
            emit clientConnected(*newClient);

            ClientsInfo *clientsToTransport = new ClientsInfo(clientsInfo.values());
            broadcast(clientsToTransport->getBytes());

            QTime dieTime= QTime::currentTime().addSecs(1);
            while (QTime::currentTime() < dieTime)
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

            serverSocket->write(newClient->getBytes());
            emit clientsUpdated(clientsToTransport->getClients());
            delete clientsToTransport;
        }

        if (message->getEvent() == SocketEvents::MESSAGE) {
            broadcast(bytes);
        }

        if (message->getEvent() == SocketEvents::UPDATE_CLIENT) {
            ClientInfo *info = new ClientInfo(bytes);
            clientsInfo.insert(serverSocket->socketDescriptor(), info);
            ClientsInfo *clientsToTransport = new ClientsInfo(clientsInfo.values());
            broadcast(clientsToTransport->getBytes());
            emit clientsUpdated(clientsToTransport->getClients());
            delete clientsToTransport;
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
        emit clientsUpdated(clientsToTransport->getClients());
        delete clientsToTransport;
    }
}
