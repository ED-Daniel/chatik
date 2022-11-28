#include "messagewidget.h"

#include <QVBoxLayout>

MessageWidget::MessageWidget(QWidget *parent, TextMessage messageInfo)
{
    QLabel *messageText = new QLabel(this);
    messageText->setText(messageInfo.getText());

    QLabel *ipText = new QLabel(this);
    ipText->setText(messageInfo.getIp());

    QLabel *senderText = new QLabel(this);
    senderText->setText(messageInfo.getSender());

    QLabel *timeText = new QLabel(this);
    timeText->setText(messageInfo.getTime());

    QVBoxLayout *layout = new QVBoxLayout( this );
    layout->addWidget(senderText);
    layout->addWidget(ipText);
    layout->addWidget(messageText);
    layout->addWidget(timeText);
}
