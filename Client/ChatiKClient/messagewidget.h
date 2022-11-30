#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "transportinginterfaces.h"

class MessageWidget : public QWidget
{
public:
    MessageWidget(QWidget *parent, TextMessage mesageInfo);
    MessageWidget(QWidget *parent, ClientImage *sentFile = nullptr);
    ClientImage *sentFile = nullptr;

    QString messageString;
    QString senderString;
    QString ipString;
    QString timeString;

    void redraw();

private:
    QLabel *messageText = nullptr;
    QLabel *senderText = nullptr;
    QLabel *ipText = nullptr;
    QLabel *timeText = nullptr;
    QPushButton *fileOpenButton = nullptr;

    QVBoxLayout *layout = new QVBoxLayout(this);

    void applyColor();
public slots:
    void openMenu();
    void saveToFile();
    void openInApplication();
};

#endif // MESSAGEWIDGET_H
