#ifndef TRANSPORTINTERFACES_H
#define TRANSPORTINTERFACES_H

#include<QString>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QByteArray>
#include<QJsonParseError>
#include<QList>
#include<QUuid>
#include<exception>

enum SocketEvents {
    JOIN,
    MESSAGE,
    UPDATE_CLIENT,
    UPDATE_CLIENTS,
    SEND_CLIENT_IMAGE
};

enum ClientStatuses {
    ONLINE,
    AWAY,
    DONT_DISTURB
};

class BasicMessage {
public:
    BasicMessage(SocketEvents event);
    BasicMessage(QByteArray basicMessage);
    BasicMessage(QJsonObject basicObject);

    QByteArray getBytes() const;
    int getEvent() const;
    QJsonObject getJsonObject() const;
protected:
    QJsonDocument document;
    QJsonObject jsonObject;
};

class ClientInfo : public BasicMessage {
public:
    ClientInfo(QString name, QString ip, QString connectedTime, ClientStatuses status);
    ClientInfo(QByteArray fromJson);
    ClientInfo(QJsonObject fromObject);

    QString getName() const;
    QString getIp() const;
    QString getConnectedTime() const;
    QString getUuid() const;
    int getStatus() const;
};

class JoinInfo : public BasicMessage {
public:
    explicit JoinInfo(QString name, ClientStatuses status);
    JoinInfo(QByteArray fromJson);

    QString getName() const;
    ClientStatuses getStatus() const;
};

class ClientsInfo : public BasicMessage {
public:
    ClientsInfo(QList<ClientInfo*> clientsInfo);
    ClientsInfo(QByteArray fromJson);

    QJsonArray getClients() const;
};

#endif // TRANSPORTINTERFACES_H
