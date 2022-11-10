#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QJsonArray>
#include<QJsonObject>
#include<QLabel>
#include "client.h"
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

private slots:
    void on_connectButton_clicked();

    void on_sendButton_clicked();
    void createMessage(QString message);
    void createMessage(const TextMessage &message);
    void setClients(const QJsonArray &info);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
