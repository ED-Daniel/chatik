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

JoinInfo::JoinInfo(QString name) : BasicMessage(SocketEvents::JOIN) {
    jsonObject.insert("name", name);

    document.setObject(jsonObject);
}

JoinInfo::JoinInfo(QByteArray bytes) : BasicMessage(bytes) {}

QString JoinInfo::getName() const {
    return jsonObject["name"].toString();
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

