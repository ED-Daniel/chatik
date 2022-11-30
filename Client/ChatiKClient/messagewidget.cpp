#include "messagewidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QMenu>
#include <QFileDialog>

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

    QLabel *messageText = new QLabel(this);
    messageText->setText(sentFile->getFileName());

    QLabel *ipText = new QLabel(this);
    ipText->setText(sentFile->getIp());

    QLabel *senderText = new QLabel(this);
    senderText->setText(sentFile->getSender());

    QLabel *timeText = new QLabel(this);
    timeText->setText(sentFile->getTime());

    QPushButton *fileOpenButton = new QPushButton(this);
    connect(fileOpenButton, &QPushButton::clicked, this, &MessageWidget::openMenu);
    fileOpenButton->setText("FILE");
    layout->addWidget(senderText);
    layout->addWidget(ipText);
    layout->addWidget(messageText);
    layout->addWidget(fileOpenButton);
    layout->addWidget(timeText);


}

void MessageWidget::saveToFile()
{
    if (sentFile != nullptr) {
        QString path = QFileDialog::getSaveFileName(0, QObject::tr("Укажите путь для сохранения"), QDir::homePath() + "/" + "test.txt");
        sentFile->saveToFile(path);
    }
}

void MessageWidget::openInApplication()
{
    if (sentFile != nullptr) {
        sentFile->saveToFile();
    }

    QDesktopServices::openUrl(QUrl("file:///Users/danielemelyanenko/Documents/test.jpg"));
}

void MessageWidget::openMenu()
{
    QMenu * contextMenu = new QMenu();
    QAction * openAction = new QAction("Open", this);
    QAction * saveAction = new QAction("Save", this);

    connect(openAction, &QAction::triggered, this, &MessageWidget::openInApplication);
    connect(saveAction, &QAction::triggered, this, &MessageWidget::saveToFile);

    contextMenu->addAction(openAction);
    contextMenu->addAction(saveAction);

    contextMenu->popup(this->mapToGlobal(this->pos()));
}
