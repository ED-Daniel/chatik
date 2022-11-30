#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QJsonArray>
#include<QJsonObject>
#include<QLabel>
#include<QDateTime>
#include <QBoxLayout>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVBoxLayout>
#include <QFile>
#include <QSpacerItem>

#include "client.h"
#include "vuex.h"
#include "transportinginterfaces.h"
#include "usernameeditdialog.h"
#include "serverconfigdialog.h"
#include "xmlsavedialog.h"
#include "userelements.h"
#include "messagewidget.h"

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
    void openFileDialog();
    void updateMessagesSlot();

private slots:
    void on_connectButton_clicked();

    void on_sendButton_clicked();
    void createMessage(QString message);
    void createMessage(const TextMessage &message);
    void createFileMessage(ClientImage *sentFile);
    void setClients(const QJsonArray &info);

    void on_actionConnect_triggered();

    void on_actionDisconnect_triggered();

    void on_actionExit_triggered();

    void on_actionServer_triggered();

    void on_actionUsername_triggered();

    void on_actionSave_History_triggered();

    void on_actionShow_triggered();

    void on_actionOnline_triggered();

    void on_actionAway_triggered();

    void on_actionDo_Not_Disturb_triggered();

    void on_actionProfile_Picture_triggered();

    void on_moreOptions_clicked();

    void on_actionBackground_Color_triggered();

    void on_actionMessage_Color_triggered();

    void on_actionIP_show_hide_triggered();

    void on_actionTime_Show_Hide_triggered();

private:
    Ui::MainWindow *ui;
    QVBoxLayout *messageScrollLayout;
    QSpacerItem *messageSpacer;
    QVector<MessageWidget*> messageWidgets = QVector<MessageWidget*>();
    void connectToServer();
    void updateMessages();
};
#endif // MAINWINDOW_H
