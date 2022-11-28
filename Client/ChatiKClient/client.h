#ifndef CLIENT_H
#define CLIENT_H

#include <QtCore>
#include <QTcpSocket>
#include <QVector>
#include <QJsonArray>
#include <QFile>
#include"transportinginterfaces.h"
#include"vuex.h"

class Client : public QObject
{
    Q_OBJECT
public:
    static Client& Instance() {
        static Client client;
        return client;
    }
    void init(QObject * parent = 0);
    void connectToServer(QString address, quint16 port);
    void sendStringToServer(QString message);
    void sendTextMessage(const TextMessage &message);
    void join(const JoinInfo &info);
    void sendMessage(const BasicMessage &message);
    void sendClientInfo(const ClientInfo &info);
    void disconnect();
    QString getIp();
    QVector<TextMessage*> getMessages() const;
signals:
    void newMessage(QString str);
    void newMessage(const TextMessage &message);
    void clientInfoUpdated(const QJsonArray &info);

private:
    Client() {}
    ~Client() {}
    Client(const Client&);
    Client& operator=(const Client&);

    QTcpSocket * clientSocket;
    QByteArray transportingData;
    QVector<TextMessage*> messages = QVector<TextMessage*>();
private slots:
    void slotReadyToRead();
};

#endif // CLIENT_H
