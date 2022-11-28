#include "client.h"

void Client::init(QObject * parent)
{
    clientSocket = new QTcpSocket(parent);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Client::slotReadyToRead);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
}

void Client::connectToServer(QString address, quint16 port)
{
    try {
        clientSocket->connectToHost(address, port);
    }
    catch (std::exception &e) {
        qDebug() << "Already Connected";
    }
}

void Client::sendStringToServer(QString message)
{
    transportingData.clear();
    QDataStream out(&transportingData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << message;
    clientSocket->write(transportingData);
}

void Client::sendTextMessage(const TextMessage &message)
{
    clientSocket->write(message.getBytes());
}

void Client::join(const JoinInfo &info)
{
    clientSocket->write(info.getBytes());
}

void Client::sendMessage(const BasicMessage &message)
{
    clientSocket->write(message.getBytes());
}

void Client::sendClientInfo(const ClientInfo &info)
{
    clientSocket->write(info.getBytes());
}

void Client::sendFile(const ClientImage &fileInfo)
{
    clientSocket->write(fileInfo.getBytes());
}

void Client::disconnect()
{
    clientSocket->disconnect();
}

QString Client::getIp()
{
    return clientSocket->peerAddress().toString();
}

QVector<TextMessage *> Client::getMessages() const
{
    return messages;
}

void Client::slotReadyToRead()
{
    QByteArray bytes = clientSocket->readAll();
    BasicMessage *message = new BasicMessage(bytes);

    if (message->isFile) {
        ClientImage *sentFile = new ClientImage(bytes);
        emit newFile(sentFile);
    }

    if (message->getEvent() == SocketEvents::MESSAGE) {
        TextMessage *message = new TextMessage(bytes);
        messages.push_back(message);
        emit newMessage(*message);
    }

    if (message->getEvent() == SocketEvents::UPDATE_CLIENT) {
        ClientInfo *info = new ClientInfo(bytes);
        Vuex::Instance().setMyId(info->getUuid());
        qDebug() << Vuex::Instance().getMyId();
        delete info;
    }

    if (message->getEvent() == SocketEvents::UPDATE_CLIENTS) {
        qDebug() << "UPDATED CLIENTS";
        ClientsInfo *info = new ClientsInfo(bytes);
        emit clientInfoUpdated(info->getClients());
    }

    delete message;
}
