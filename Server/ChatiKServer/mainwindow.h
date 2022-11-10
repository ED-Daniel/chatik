#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJsonArray>
#include <QJsonObject>

#include "server.h"
#include "transportinginterfaces.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void setClients(const QJsonArray &info);
    void handleConnect(const ClientInfo &info);
    void handleDisconnect(const ClientInfo &info);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
