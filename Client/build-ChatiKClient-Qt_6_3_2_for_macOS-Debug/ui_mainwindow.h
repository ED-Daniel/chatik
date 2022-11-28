/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionSave_History;
    QAction *actionExit;
    QAction *actionServer;
    QAction *actionUsername;
    QAction *actionOnline;
    QAction *actionAway;
    QAction *actionDo_Not_Disturb;
    QAction *actionShow;
    QAction *actionProfile_Picture;
    QWidget *centralwidget;
    QLineEdit *messageInput;
    QPushButton *sendButton;
    QPushButton *connectButton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *clientsListHolder;
    QWidget *gridLayoutWidget;
    QGridLayout *messageArea;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSettings;
    QMenu *menuStatus;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QString::fromUtf8("actionDisconnect"));
        actionSave_History = new QAction(MainWindow);
        actionSave_History->setObjectName(QString::fromUtf8("actionSave_History"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionServer = new QAction(MainWindow);
        actionServer->setObjectName(QString::fromUtf8("actionServer"));
        actionUsername = new QAction(MainWindow);
        actionUsername->setObjectName(QString::fromUtf8("actionUsername"));
        actionOnline = new QAction(MainWindow);
        actionOnline->setObjectName(QString::fromUtf8("actionOnline"));
        actionAway = new QAction(MainWindow);
        actionAway->setObjectName(QString::fromUtf8("actionAway"));
        actionDo_Not_Disturb = new QAction(MainWindow);
        actionDo_Not_Disturb->setObjectName(QString::fromUtf8("actionDo_Not_Disturb"));
        actionShow = new QAction(MainWindow);
        actionShow->setObjectName(QString::fromUtf8("actionShow"));
        actionProfile_Picture = new QAction(MainWindow);
        actionProfile_Picture->setObjectName(QString::fromUtf8("actionProfile_Picture"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        messageInput = new QLineEdit(centralwidget);
        messageInput->setObjectName(QString::fromUtf8("messageInput"));
        messageInput->setGeometry(QRect(10, 500, 541, 41));
        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(560, 500, 61, 41));
        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(630, 500, 161, 41));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(630, 30, 160, 461));
        clientsListHolder = new QVBoxLayout(verticalLayoutWidget);
        clientsListHolder->setObjectName(QString::fromUtf8("clientsListHolder"));
        clientsListHolder->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 29, 611, 461));
        messageArea = new QGridLayout(gridLayoutWidget);
        messageArea->setObjectName(QString::fromUtf8("messageArea"));
        messageArea->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuStatus = new QMenu(menuSettings);
        menuStatus->setObjectName(QString::fromUtf8("menuStatus"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionConnect);
        menuFile->addAction(actionDisconnect);
        menuFile->addAction(actionSave_History);
        menuFile->addAction(actionExit);
        menuSettings->addAction(actionServer);
        menuSettings->addAction(actionUsername);
        menuSettings->addAction(menuStatus->menuAction());
        menuSettings->addAction(actionProfile_Picture);
        menuStatus->addAction(actionOnline);
        menuStatus->addAction(actionAway);
        menuStatus->addAction(actionDo_Not_Disturb);
        menuAbout->addAction(actionShow);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        actionDisconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        actionSave_History->setText(QCoreApplication::translate("MainWindow", "Save History", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionServer->setText(QCoreApplication::translate("MainWindow", "Server", nullptr));
        actionUsername->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        actionOnline->setText(QCoreApplication::translate("MainWindow", "Online", nullptr));
        actionAway->setText(QCoreApplication::translate("MainWindow", "Away", nullptr));
        actionDo_Not_Disturb->setText(QCoreApplication::translate("MainWindow", "Do Not Disturb", nullptr));
        actionShow->setText(QCoreApplication::translate("MainWindow", "Show", nullptr));
        actionProfile_Picture->setText(QCoreApplication::translate("MainWindow", "Profile Picture", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuStatus->setTitle(QCoreApplication::translate("MainWindow", "Status", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
