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
};

#endif // MESSAGEWIDGET_H
