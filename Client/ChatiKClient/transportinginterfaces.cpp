#include"transportinginterfaces.h"

#include <QFileDialog>

TextMessage::TextMessage(QString sender, QString message, QString time, QString ip) : BasicMessage(SocketEvents::MESSAGE)
{
    jsonObject.insert("sender", sender);
    jsonObject.insert("message", message);
    jsonObject.insert("time", time);
    jsonObject.insert("ip", ip);

    document.setObject(jsonObject);
}

TextMessage::TextMessage(QByteArray fromJson) : BasicMessage(fromJson) {}

QString TextMessage::getText() const
{
    return jsonObject["message"].toString();
}

QString TextMessage::getSender() const
{
    return jsonObject["sender"].toString();
}

QString TextMessage::getTime() const
{
    return jsonObject["time"].toString();
}

QString TextMessage::getIp() const
{
    return jsonObject["ip"].toString();
}

BasicMessage::BasicMessage(SocketEvents event)
{
    jsonObject.insert("event", event);
    document.setObject(jsonObject);
}

BasicMessage::BasicMessage(QByteArray basicMessage)
{
    QJsonParseError parseError;
    document = QJsonDocument::fromJson(basicMessage, &parseError);
    jsonObject = document.object();

    if (jsonObject.value("event").isUndefined()) {
        isFile = true;
    }
}

BasicMessage::BasicMessage(QJsonObject jsonObject)
{
    this->jsonObject = jsonObject;
    document.setObject(jsonObject);

}

QByteArray BasicMessage::getBytes() const
{
    QByteArray bytes(document.toJson(QJsonDocument::Indented));
    return bytes;
}

int BasicMessage::getEvent() const
{
    return jsonObject["event"].toInt();
}

QJsonObject BasicMessage::getJsonObject() const
{
    return jsonObject;
}

JoinInfo::JoinInfo(QString name, ClientStatuses status) : BasicMessage(SocketEvents::JOIN) {
    jsonObject.insert("name", name);
    jsonObject.insert("status", status);

    document.setObject(jsonObject);
}

JoinInfo::JoinInfo(QByteArray bytes) : BasicMessage(bytes) {}

QString JoinInfo::getName() const {
    return jsonObject["name"].toString();
}

ClientStatuses JoinInfo::getStatus() const
{
    return (ClientStatuses) jsonObject["status"].toInt();
}

ClientInfo::ClientInfo(QString name, QString ip, QString connectedTime, ClientStatuses status) : BasicMessage(SocketEvents::UPDATE_CLIENT) {
    jsonObject.insert("name", name);
    jsonObject.insert("ip", ip);
    jsonObject.insert("connected_time", connectedTime);
    jsonObject.insert("status", status);

    document.setObject(jsonObject);
}

ClientInfo::ClientInfo(QByteArray fromJson) : BasicMessage(fromJson) {}

ClientInfo::ClientInfo(QJsonObject fromObject) : BasicMessage(fromObject) {}

QString ClientInfo::getName() const
{
    return jsonObject["name"].toString();
}

QString ClientInfo::getIp() const {
    return jsonObject["ip"].toString();
}

QString ClientInfo::getConnectedTime() const {
    return jsonObject["connected_time"].toString();
}

QString ClientInfo::getUuid() const {
    return jsonObject["uuid"].toString();
}

QImage ClientInfo::getImage() const
{
    return image;
}

int ClientInfo::getStatus() const {
    return jsonObject["status"].toInt();
}

ClientsInfo::ClientsInfo(QList<ClientInfo *> clientsInfo) : BasicMessage(SocketEvents::UPDATE_CLIENTS)
{
    QJsonArray clients;
    for (const auto client : clientsInfo) {
        clients.append(client->getJsonObject());
    }
    jsonObject.insert("clients", clients);
    document.setObject(jsonObject);
}

ClientsInfo::ClientsInfo(QByteArray fromJson) : BasicMessage(fromJson) {}

QJsonArray ClientsInfo::getClients() const
{
    return jsonObject["clients"].toArray();
}


ClientImage::ClientImage(QString ip, QString sender, QString fileName, QString time, QByteArray imageBytes) : BasicMessage(SocketEvents::SEND_CLIENT_IMAGE)
{
    jsonObject.insert("ip", ip);
    jsonObject.insert("sender", sender);
    jsonObject.insert("time", time);
    jsonObject.insert("file_name", fileName);
    jsonObject.insert("size", imageBytes.size());
    this->imageBytes = std::move(imageBytes);

    document.setObject(jsonObject);
}

ClientImage::ClientImage(QByteArray fromJson) : BasicMessage(fromJson)
{
    QSaveFile file1("/Users/danielemelyanenko/Documents/recievedBytes.txt");
    file1.open(QIODevice::WriteOnly);
    file1.write(fromJson);
    file1.commit();

    QByteArray jsonSizeBytes = fromJson.first(8);
    qsizetype jsonSize = to_qsizetype(jsonSizeBytes);
    qDebug() << jsonSize << "RECV JSON SIZE";
    QByteArray jsonArray = fromJson.mid(8, jsonSize);

    QJsonParseError parseError;
    document = QJsonDocument::fromJson(jsonArray, &parseError);
    jsonObject = document.object();

    qsizetype imageSize = jsonObject["size"].toInteger();
    qDebug() << imageSize;
    QByteArray imageBytes = fromJson.mid(8 + jsonSize, imageSize);
    QSaveFile file("/Users/danielemelyanenko/Documents/recievedImage.jpg");
    file.open(QIODevice::WriteOnly);
    file.write(imageBytes);
    file.commit();

    this->imageBytes = std::move(imageBytes);
}

ClientImage::ClientImage(QJsonObject fromObject) : BasicMessage(fromObject)
{

}

QByteArray ClientImage::getBytes() const
{
    QByteArray bytes(document.toJson(QJsonDocument::Indented));
    QByteArray bytesSize;

    qsizetype s = bytes.size();
    qDebug() << s << "SENT JSON SIZE";
    for(int i = 0; i != sizeof(s); ++i)
    {
      bytesSize.prepend((char)((s & (0xFF << (i*8))) >> (i*8)));
    }

    bytes.prepend(bytesSize);
    bytes.append(imageBytes);

    QSaveFile file("/Users/danielemelyanenko/Documents/bytes.txt");
    file.open(QIODevice::WriteOnly);
    file.write(bytes);
    file.commit();

    return bytes;
}

void ClientImage::saveToFile()
{
    QSaveFile file("/Users/danielemelyanenko/Documents/test.jpg");
    file.open(QIODevice::WriteOnly);
    file.write(imageBytes);
    file.commit();
}

void ClientImage::saveToFile(QString path)
{
    QSaveFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(imageBytes);
    file.commit();
}

QString ClientImage::getIp()
{
    return jsonObject["ip"].toString();
}

QString ClientImage::getFileName()
{
    return jsonObject["file_name"].toString();
}

QString ClientImage::getTime()
{
    return jsonObject["time"].toString();
}

QString ClientImage::getSender()
{
    return jsonObject["sender"].toString();
}

qsizetype to_qsizetype(QByteArray data) {
    qsizetype v = 0;
    v = ((unsigned char)data[0]<<56) | ((unsigned char)data[1]<<48) | ((unsigned char)data[2]<<40) | ((unsigned char)data[3]<<32) | (unsigned char)(data[4]<<24) | (unsigned char)(data[5]<<16) | (unsigned char)(data[6]<<8) | (unsigned char)data[7];

    return v;
}
