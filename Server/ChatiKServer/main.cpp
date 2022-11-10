#include "mainwindow.h"
#include "server.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server::Instance().init(QHostAddress::LocalHost, 45678);
    MainWindow w;
    w.show();
    return a.exec();
}
