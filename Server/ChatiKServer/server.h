#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QMap>
#include <QException>
#include <QDateTime>
#include <algorithm>
#include <QJsonArray>

#include "transportinginterfaces.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    static Server& Instance() {
        static Server server;
        return server;
    }
    QTcpSocket * serverSocket;
    void init(QHostAddress ip, quint16 port);
    QString getIp();
    quint16 getPort();

private:
    Server() {}
    ~Server() {}
    Server(const Server&);
    Server& operator=(const Server&);

    QString ip;
    quint16 port;

    QVector<QTcpSocket*> clients;
    QMap<qintptr, ClientInfo*> clientsInfo;
    QByteArray transportingData;

    void sendToClient(QString message);
    void broadcast(QString message);
    void broadcast(QByteArray bytes);
    void deleteClientsInfo();
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();
    void handleDisconnect();
signals:
    void clientsUpdated(const QJsonArray &info);
    void clientConnected(const ClientInfo &info);
    void clientDisconnected(const ClientInfo &info);
};

#endif // SERVER_H
