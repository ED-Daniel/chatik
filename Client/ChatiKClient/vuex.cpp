#include "vuex.h"

void Vuex::setServerIp(QString ip)
{
    QSettings settings(filename, QSettings::IniFormat);
    this->serverIp = ip;
    settings.setValue("ip", serverIp);
}

void Vuex::setPort(quint16 port)
{
    this->port = port;
    QSettings settings(filename, QSettings::IniFormat);
    settings.setValue("port", port);
}

void Vuex::setUsername(QString username)
{
    this->username = username;
    QSettings settings(filename, QSettings::IniFormat);
    settings.setValue("username", username);
}

void Vuex::setStatus(ClientStatuses status)
{
    this->status = status;
    QSettings settings(filename, QSettings::IniFormat);
    settings.setValue("status", (uint) status);
}

void Vuex::setProfileImageBytes(QByteArray image)
{
    this->profileImageBytes = std::move(image);
}

void Vuex::setMyId(QString id)
{
    this->myId = id;
}

void Vuex::init(QString filename)
{
    QSettings settings(filename, QSettings::IniFormat);
    this->serverIp = settings.value("ip").toString();
    this->port = settings.value("port").toUInt();
    this->username = settings.value("username").toString();
    this->status = (ClientStatuses)settings.value("status").toUInt();

    this->filename = filename;
}

QString Vuex::getServerIp()
{
    return serverIp;
}

quint16 Vuex::getPort()
{
    return port;
}

QString Vuex::getUsername()
{
    return username;
}

QByteArray Vuex::getProfileImageBytes()
{
    return profileImageBytes;
}

ClientStatuses Vuex::getStatus()
{
    return status;
}

QString Vuex::getMyId()
{
    return this->myId;
}
