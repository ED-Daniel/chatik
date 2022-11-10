#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QMap>
#include <QException>
#include <QDateTime>
#include <algorithm>

#include "transportinginterfaces.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket * serverSocket;

private:
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
};

#endif // SERVER_H
