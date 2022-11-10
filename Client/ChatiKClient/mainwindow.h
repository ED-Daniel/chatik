#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QJsonArray>
#include<QJsonObject>
#include<QLabel>
#include<QDateTime>

#include "client.h"
#include "vuex.h"
#include "transportinginterfaces.h"
#include "usernameeditdialog.h"
#include "serverconfigdialog.h"
#include "xmlsavedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();

    void on_sendButton_clicked();
    void createMessage(QString message);
    void createMessage(const TextMessage &message);
    void setClients(const QJsonArray &info);

    void on_actionConnect_triggered();

    void on_actionDisconnect_triggered();

    void on_actionExit_triggered();

    void on_actionServer_triggered();

    void on_actionUsername_triggered();

    void on_actionSave_History_triggered();

private:
    Ui::MainWindow *ui;
    void connectToServer();
};
#endif // MAINWINDOW_H
