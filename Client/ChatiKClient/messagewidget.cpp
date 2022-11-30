#include "messagewidget.h"
#include "vuex.h"

#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QMenu>
#include <QFileDialog>
#include <QPalette>

MessageWidget::MessageWidget(QWidget *parent, TextMessage messageInfo)
{
    messageText = new QLabel(this);
    messageText->setText(messageInfo.getText());

    ipText = new QLabel(this);
    ipText->setText(messageInfo.getIp());

    senderText = new QLabel(this);
    senderText->setText(messageInfo.getSender());

    timeText = new QLabel(this);
    timeText->setText(messageInfo.getTime());

    layout->addWidget(senderText);
    layout->addWidget(ipText);
    layout->addWidget(messageText);
    layout->addWidget(timeText);

    messageString = messageInfo.getText();
    ipString = messageInfo.getIp();
    timeString = messageInfo.getTime();
    senderString = messageInfo.getSender();

    applyColor();
}

MessageWidget::MessageWidget(QWidget *parent, ClientImage *sentFile)
{
    this->sentFile = sentFile;

    messageText = new QLabel(this);
    messageText->setText(sentFile->getFileName());

    ipText = new QLabel(this);
    ipText->setText(sentFile->getIp());

    senderText = new QLabel(this);
    senderText->setText(sentFile->getSender());

    timeText = new QLabel(this);
    timeText->setText(sentFile->getTime());

    fileOpenButton = new QPushButton(this);
    connect(fileOpenButton, &QPushButton::clicked, this, &MessageWidget::openMenu);
    fileOpenButton->setText("FILE");
    layout->addWidget(senderText);
    layout->addWidget(ipText);
    layout->addWidget(messageText);
    layout->addWidget(fileOpenButton);
    layout->addWidget(timeText);

    messageString = sentFile->getFileName();
    ipString = sentFile->getIp();
    timeString = sentFile->getTime();
    senderString = sentFile->getSender();

    applyColor();
}

void MessageWidget::redraw() {
    ipText->setText(Vuex::Instance().showIp ? ipString : "");
    timeText->setText(Vuex::Instance().showTime ? timeString : "");

    applyColor();
}

void MessageWidget::applyColor()
{
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Vuex::Instance().messagesColor);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->update();
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
        QDesktopServices::openUrl(QUrl("file://" + QDir::currentPath() + "/" + sentFile->getFileName()));
    }
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
