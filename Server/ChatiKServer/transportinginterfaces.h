#ifndef TRANSPORTINTERFACES_H
#define TRANSPORTINTERFACES_H

#include<QString>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QByteArray>
#include<QJsonParseError>
#include<QList>
#include<exception>

enum SocketEvents {
    JOIN,
    MESSAGE,
    UPDATE_CLIENTS
};

enum ClientStatuses {
    ONLINE,
    AWAY,
    DONT_DISTURB
};

std::string unixTimeToHumanReadable(quint64 seconds);

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
    int getStatus() const;
};

class JoinInfo : public BasicMessage {
public:
    explicit JoinInfo(QString name);
    JoinInfo(QByteArray fromJson);

    QString getName() const;
};

class ClientsInfo : public BasicMessage {
public:
    ClientsInfo(QList<ClientInfo*> clientsInfo);
    ClientsInfo(QByteArray fromJson);

    QJsonArray getClients() const;
};

#endif // TRANSPORTINTERFACES_H
