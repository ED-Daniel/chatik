#ifndef TRANSPORTINTERFACES_H
#define TRANSPORTINTERFACES_H

#include<QString>
#include<QJsonDocument>
#include<QJsonObject>
#include<QByteArray>
#include<QJsonParseError>
#include<QJsonArray>
#include<QVector>
#include<exception>
#include<QImage>
#include<QBuffer>
#include<QSaveFile>
#include<QFile>

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

qsizetype to_qsizetype(QByteArray data);

class BasicMessage {
public:
    BasicMessage(SocketEvents event);
    BasicMessage(QByteArray basicMessage);
    BasicMessage(QJsonObject basicObject);

    QByteArray getBytes() const;
    int getEvent() const;
    QJsonObject getJsonObject() const;

    bool isFile = false;
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

class ClientImage : public BasicMessage {
public:
    ClientImage(QString ip, QByteArray imageBytes);
    ClientImage(QByteArray fromJson);
    ClientImage(QJsonObject fromObject);

    QByteArray getBytes() const;
private:
    QByteArray imageBytes;
};

#endif // TRANSPORTINTERFACES_H
