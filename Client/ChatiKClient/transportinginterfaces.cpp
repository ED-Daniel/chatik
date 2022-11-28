#include"transportinginterfaces.h"

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


ClientImage::ClientImage(QString ip, QByteArray imageBytes) : BasicMessage(SocketEvents::SEND_CLIENT_IMAGE)
{
    jsonObject.insert("ip", ip);
    jsonObject.insert("size", imageBytes.size());
    this->imageBytes = std::move(imageBytes);

    document.setObject(jsonObject);
}

ClientImage::ClientImage(QByteArray fromJson) : BasicMessage(fromJson)
{
    QByteArray jsonSizeBytes = fromJson.first(8);
    qsizetype jsonSize = to_qsizetype(jsonSizeBytes);
    QByteArray jsonArray;
    for (qsizetype i = 8; i < jsonSize + 8; i++) {
        jsonArray.append(fromJson[i]);
    }

    QJsonParseError parseError;
    document = QJsonDocument::fromJson(jsonArray, &parseError);
    jsonObject = document.object();

    qsizetype imageSize = jsonObject["size"].toInteger();
    qDebug() << imageSize;
    QByteArray imageBytes = fromJson.last(imageSize);
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
    QSaveFile file("/Users/danielemelyanenko/Documents/test.txt");
    file.open(QIODevice::WriteOnly);
    file.write(imageBytes);
    file.commit();
}

qsizetype to_qsizetype(QByteArray data) {
    qsizetype v = 0;
    for (int i = 0; i < 8; i++) {
      v = (v << 8) | data[i];
    }

    return v;
}
