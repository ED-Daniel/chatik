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
    BasicMessage(QJsonObject jsonObject);

    QByteArray getBytes() const;
    int getEvent() const;
    QJsonObject getJsonObject() const;
    bool isFile = false;
protected:
    QJsonDocument document;
    QJsonObject jsonObject;
};

class JoinInfo : public BasicMessage {
public:
    explicit JoinInfo(QString name, ClientStatuses status);
    JoinInfo(QByteArray fromJson);

    QString getName() const;
    ClientStatuses getStatus() const;
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
    QImage getImage() const;
    int getStatus() const;
private:
    QImage image;
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

class ClientImage : public BasicMessage {
public:
    ClientImage(QString ip, QString sender, QString fileName, QString time, QByteArray imageBytes);
    ClientImage(QByteArray fromJson);
    ClientImage(QJsonObject fromObject);

    QByteArray getBytes() const;

    void saveToFile();
    void saveToFile(QString path);

    QString getIp();
    QString getFileName();
    QString getTime();
    QString getSender();
private:
    QByteArray imageBytes;
};

#endif // TRANSPORTINGINTERFACES_H
