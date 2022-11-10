#include "userelements.h"

UserElements::UserElements(QWidget *parent, QString title) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout( this );
    QLabel *label = new QLabel(this);
    label->setText(title);
    layout->addWidget(label);
}

UserElements::~UserElements() {
    delete info;
}

void UserElements::setClientInfo(ClientInfo *info)
{
    this->info = info;
}

void UserElements::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        if (info) {
            QDialog *dialog = new QDialog(this);
            dialog->setModal(true);
            QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);

            QLabel *ip = new QLabel(this);
            ip->setText(info->getIp());

            QLabel *connectTime = new QLabel(this);
            connectTime->setText(info->getConnectedTime());

            ClientStatuses status = (ClientStatuses) info->getStatus();
            QString statusStr = "";

            switch (status) {
            case ClientStatuses::ONLINE:
                statusStr = "ONLINE";
                break;
             case ClientStatuses::AWAY:
                statusStr = "AWAY";
                break;
             case ClientStatuses::DONT_DISTURB:
                statusStr = "DO NOT DISTURB";
                break;
            default:
                break;
            }

            QLabel *statusLabel = new QLabel(this);
            statusLabel->setText(statusStr);

            QPushButton *buttonClose = new QPushButton("Close");
            connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);

            layout->addWidget(ip);
            layout->addWidget(connectTime);
            layout->addWidget(statusLabel);
            layout->addWidget(buttonClose);

            dialog->setLayout(layout);
            dialog->show();
        }
    }
}
