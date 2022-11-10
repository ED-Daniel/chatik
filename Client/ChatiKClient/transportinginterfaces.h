#ifndef TRANSPORTINGINTERFACES_H
#define TRANSPORTINGINTERFACES_H

#include<QString>
#include<QJsonDocument>
#include<QJsonObject>
#include<QByteArray>
#include<QJsonParseError>
#include<QJsonArray>
#include<QVector>
#include<exception>

enum SocketEvents {
    JOIN,
    MESSAGE,
    UPDATE_CLIENT,
    UPDATE_CLIENTS
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
    BasicMessage(QJsonObject jsonObject);

    QByteArray getBytes() const;
    int getEvent() const;
    QJsonObject getJsonObject() const;
protected:
    QJsonDocument document;
    QJsonObject jsonObject;
};

class JoinInfo : public BasicMessage {
public:
    explicit JoinInfo(QString name);
    JoinInfo(QByteArray fromJson);

    QString getName() const;
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

class ClientsInfo : public BasicMessage {
public:
    ClientsInfo(QList<ClientInfo*> clientsInfo);
    ClientsInfo(QByteArray fromJson);

    QJsonArray getClients() const;
};

class TextMessage : public BasicMessage {
public:
    TextMessage(QString sender, QString message, QString time, QString ip);
    TextMessage(QByteArray fromJson);

    QString getText() const;
    QString getSender() const;
    QString getTime() const;
    QString getIp() const;
};

#endif // TRANSPORTINGINTERFACES_H
