#ifndef VUEX_H
#define VUEX_H

#include <QString>
#include <QSettings>
#include <QByteArray>
#include <QColor>
#include "transportinginterfaces.h"

class Vuex
{
public:
    static Vuex& Instance() {
        static Vuex vuex;
        return vuex;
    }

    QColor messagesColor;
    bool showIp = true;
    bool showTime = true;

    QString connectedTime;

    void setServerIp(QString ip);
    void setPort(quint16 port);
    void setUsername(QString username);
    void setStatus(ClientStatuses status);
    void setProfileImageBytes(QByteArray image);
    void setMyId(QString id);

    void init(QString filename);

    QString getServerIp();
    quint16 getPort();
    QString getUsername();
    QByteArray getProfileImageBytes();
    ClientStatuses getStatus();
    QString getMyId();

private:
    Vuex() {}
    ~Vuex() {}
    Vuex(const Vuex&);
    Vuex& operator=(const Vuex&);

    QSettings settings;

    QString serverIp = "127.0.0.1";
    quint16 port = 45678;
    QString username = "Unkown User";
    ClientStatuses status = ClientStatuses::ONLINE;

    QString filename;
    QByteArray profileImageBytes;
    QString myId;
};

#endif // VUEX_H
