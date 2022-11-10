#ifndef USERELEMENTS_H
#define USERELEMENTS_H

#include <QWidget>
#include <QBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QDialog>
#include <QPushButton>

#include "transportinginterfaces.h"

class UserElements : public QWidget
{
    Q_OBJECT
 public:
     UserElements( QWidget *parent = 0, QString title = "");
     ~UserElements();

     void setClientInfo(ClientInfo *info);
private:
     ClientInfo *info = nullptr;
protected:
     void mousePressEvent(QMouseEvent *e);
};

#endif // USERELEMENTS_H
