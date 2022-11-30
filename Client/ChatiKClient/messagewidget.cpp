#include "messagewidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>

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

MessageWidget::MessageWidget(QWidget *parent, ClientImage *sentFile)
{
    this->sentFile = sentFile;
    QVBoxLayout *layout = new QVBoxLayout( this );

    QPushButton *fileOpenButton = new QPushButton(this);
    connect(fileOpenButton, &QPushButton::clicked, this, &MessageWidget::saveToFile);
    fileOpenButton->setText("OPEN FILE");
    layout->addWidget(fileOpenButton);


}

void MessageWidget::saveToFile()
{
    if (sentFile != nullptr) {
        sentFile->saveToFile();
    }

    QDesktopServices::openUrl(QUrl("file:///Users/danielemelyanenko/Documents/test.jpg"));
}
