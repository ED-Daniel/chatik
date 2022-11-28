#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <QString>
#include <QLabel>

#include "transportinginterfaces.h"

class MessageWidget : public QWidget
{
public:
    MessageWidget(QWidget *parent, TextMessage mesageInfo);
    MessageWidget(QWidget *parent, ClientImage *sentFile = nullptr);
private:
    ClientImage *sentFile = nullptr;
private slots:
    void saveToFile();
};

#endif // MESSAGEWIDGET_H
