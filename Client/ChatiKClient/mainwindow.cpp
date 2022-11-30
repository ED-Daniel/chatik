#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "messagewidget.h"
#include "messagecolordialog.h"

#include <QScrollArea>
#include <QColorDialog>
#include <QObjectList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Client::Instance().init(this);
    Vuex::Instance().init("/Users/danielemelyanenko/Documents/QtProjects/ChatiK/Client/ChatiKClient/settings.ini");
    connect(&Client::Instance(), SIGNAL(newMessage(QString)), this, SLOT(createMessage(QString)));
    connect(&Client::Instance(), SIGNAL(newMessage(TextMessage)), this, SLOT(createMessage(TextMessage)));
    connect(&Client::Instance(), SIGNAL(newFile(ClientImage*)), this, SLOT(createFileMessage(ClientImage*)));
    connect(&Client::Instance(), SIGNAL(clientInfoUpdated(QJsonArray)), this, SLOT(setClients(QJsonArray)));
    ui->setupUi(this);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    ui->messageArea->addWidget(scrollArea);

    QWidget *scrollWidget = new QWidget();
    scrollArea->setWidget(scrollWidget);

    messageScrollLayout = new QVBoxLayout(scrollWidget);
    messageSpacer = new QSpacerItem(100, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    messageScrollLayout->addItem(messageSpacer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath() + "/");

    QFile* imageFile = new QFile(fileName);
    imageFile->open(QIODevice::ReadOnly);
    QByteArray imageBytes = imageFile->readAll();

    QFileInfo fileInfo(imageFile->fileName());
    QString filename(fileInfo.fileName());

    imageFile->close();
    delete imageFile;

    Vuex::Instance().setProfileImageBytes(imageBytes);
    ClientImage *clientImg = new ClientImage(Client::Instance().getIp(),
                                             Vuex::Instance().getUsername(),
                                             filename,
                                             QDateTime::currentDateTime().toString(),
                                             Vuex::Instance().getProfileImageBytes()
                                             );
    Client::Instance().sendFile(*clientImg);
    delete clientImg;
}

void MainWindow::updateMessagesSlot()
{

    updateMessages();
}

void MainWindow::on_connectButton_clicked()
{
    connectToServer();
}


void MainWindow::on_sendButton_clicked()
{
    TextMessage * message = new TextMessage(Vuex::Instance().getUsername(), ui->messageInput->text(), QDateTime::currentDateTime().toString(), Client::Instance().getIp());
    Client::Instance().sendTextMessage(*message);
    ui->messageInput->clear();
    delete message;
}

void MainWindow::createMessage(QString message)
{
    ui->statusbar->showMessage(message);
}

void MainWindow::createMessage(const TextMessage &message)
{
    // ui->messagesArea->append(message.getSender() + ":\n" + message.getText() + "\n\n");
    MessageWidget *newMessage = new MessageWidget(this, message);

    messageScrollLayout->removeItem(messageSpacer);
    messageScrollLayout->addWidget(newMessage);
    messageScrollLayout->addItem(messageSpacer);

    ui->statusbar->showMessage(message.getSender() + ": " + message.getText());
    if (Vuex::Instance().getStatus() != ClientStatuses::DONT_DISTURB) {
        QMediaPlayer *player = new QMediaPlayer;
        QAudioOutput *audio = new QAudioOutput;
        player->setAudioOutput(audio);
        player->setSource(QUrl::fromLocalFile("/Users/danielemelyanenko/Documents/QtProjects/ChatiK/Client/ChatiKClient/sound.wav"));
        audio->setVolume(50);
        player->play();
        qDebug() << "AUDIO";
    }

    messageWidgets.append(newMessage);
}

void MainWindow::createFileMessage(ClientImage *sentFile)
{
    MessageWidget *newMessage = new MessageWidget(this, sentFile);

    messageScrollLayout->removeItem(messageSpacer);
    messageScrollLayout->addWidget(newMessage);
    messageScrollLayout->addItem(messageSpacer);

    if (Vuex::Instance().getStatus() != ClientStatuses::DONT_DISTURB) {
        QMediaPlayer *player = new QMediaPlayer;
        QAudioOutput *audio = new QAudioOutput;
        player->setAudioOutput(audio);
        player->setSource(QUrl::fromLocalFile("/Users/danielemelyanenko/Documents/QtProjects/ChatiK/Client/ChatiKClient/sound.wav"));
        audio->setVolume(50);
        player->play();
        qDebug() << "AUDIO";
    }

    messageWidgets.append(newMessage);
}

void MainWindow::setClients(const QJsonArray &info)
{
    qDebug() << "SET CLIENTS TRIGGERED";
    //ui->clientsListHolder->children().toList()[0]->deleteLater();

    QLayoutItem* item;
        while ( ( item = ui->clientsListHolder->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }

    for (const auto client : info) {
        QJsonObject clientObject = client.toObject();

        if (clientObject["name"].toString() == Vuex::Instance().getUsername() && clientObject["ip"].toString() == Client::Instance().getIp()) {
            Vuex::Instance().connectedTime = clientObject["connected_time"].toString();
        }

        ClientStatuses status = (ClientStatuses) clientObject["status"].toInt();
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
        UserElements *element = new UserElements(this, clientObject["name"].toString());

        element->setClientInfo(new ClientInfo(clientObject));

        ui->clientsListHolder->addWidget(element);
    }
}


void MainWindow::on_actionConnect_triggered()
{
    connectToServer();
}

void MainWindow::connectToServer()
{
    Client::Instance().connectToServer(Vuex::Instance().getServerIp(), Vuex::Instance().getPort());
    JoinInfo * info = new JoinInfo(Vuex::Instance().getUsername(), Vuex::Instance().getStatus());
    Client::Instance().join(*info);
    delete info;
}

void MainWindow::updateMessages()
{
    for (MessageWidget* message : messageWidgets) {
        message->redraw();
    }
}

void MainWindow::on_actionDisconnect_triggered()
{
    Client::Instance().disconnect();
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionServer_triggered()
{
    ServerConfigDialog * serverConfigDialog = new ServerConfigDialog(this);
    serverConfigDialog->show();
}


void MainWindow::on_actionUsername_triggered()
{
    UsernameEditDialog * usernameEditDialog = new UsernameEditDialog(this);
    usernameEditDialog->show();
}


void MainWindow::on_actionSave_History_triggered()
{
    XmlSaveDialog * saveDialog = new XmlSaveDialog(this);
    saveDialog->show();
}


void MainWindow::on_actionShow_triggered()
{
    QDialog *dialog = new QDialog(this);
    dialog->setModal(true);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
    QImage img("/Users/danielemelyanenko/Documents/QtProjects/ChatiK/Client/ChatiKClient/author.jpg");
    QImage author = img.scaled(img.width() / 6, img.height() / 6);
    QString data = QDate::currentDate().toString("dd.MM.yyyy");
    QLabel *label = new QLabel;
    QPushButton *buttonClose = new QPushButton("Close");

    label->setPixmap(QPixmap::fromImage(author));
    label->setScaledContents(true);

    layout->addWidget(label);
    layout->addWidget(new QLabel("Build version: 6.3.1"));
    layout->addWidget(new QLabel("Qt Version: " + QString(QT_VERSION_STR)));
    layout->addWidget(new QLabel("Daniel Emelyanenko"));
    layout->addWidget(new QLabel("Build date: " + data));
    layout->addWidget(buttonClose);

    dialog->setLayout(layout);
    dialog->show();

    connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
}


void MainWindow::on_actionOnline_triggered()
{
    Vuex::Instance().setStatus(ClientStatuses::ONLINE);
    ClientInfo *info = new ClientInfo(Vuex::Instance().getUsername(), Client::Instance().getIp(), Vuex::Instance().connectedTime, Vuex::Instance().getStatus());
    Client::Instance().sendClientInfo(*info);
    delete info;
}


void MainWindow::on_actionAway_triggered()
{
    Vuex::Instance().setStatus(ClientStatuses::AWAY);
    ClientInfo *info = new ClientInfo(Vuex::Instance().getUsername(), Client::Instance().getIp(), Vuex::Instance().connectedTime, Vuex::Instance().getStatus());
    Client::Instance().sendClientInfo(*info);
    delete info;
}


void MainWindow::on_actionDo_Not_Disturb_triggered()
{
    Vuex::Instance().setStatus(ClientStatuses::DONT_DISTURB);
    ClientInfo *info = new ClientInfo(Vuex::Instance().getUsername(), Client::Instance().getIp(), Vuex::Instance().connectedTime, Vuex::Instance().getStatus());
    Client::Instance().sendClientInfo(*info);
    delete info;
}


void MainWindow::on_actionProfile_Picture_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), QDir::homePath() + "/", tr("Image Files (*.png *.jpg *.bmp)"));

    QFile* imageFile = new QFile(fileName);
    imageFile->open(QIODevice::ReadOnly);
    QByteArray imageBytes = imageFile->readAll();

    QFileInfo fileInfo(imageFile->fileName());
    QString filename(fileInfo.fileName());

    imageFile->close();
    delete imageFile;

    Vuex::Instance().setProfileImageBytes(imageBytes);
    ClientImage *clientImg = new ClientImage(Client::Instance().getIp(),
                                             Vuex::Instance().getUsername(),
                                             filename,
                                             QDateTime::currentDateTime().toString(),
                                             Vuex::Instance().getProfileImageBytes()
                                             );
    Client::Instance().sendFile(*clientImg);
    delete clientImg;
}


void MainWindow::on_moreOptions_clicked()
{
    QMenu * contextMenu = new QMenu();
    QAction * openAction = new QAction("Open File", this);
    connect(openAction, &QAction::triggered, this, &MainWindow::openFileDialog);
    contextMenu->addAction(openAction);
    contextMenu->popup(this->mapToGlobal(ui->moreOptions->pos()));
}


void MainWindow::on_actionBackground_Color_triggered()
{
    QColor color = QColorDialog::getColor();
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, color);

    this->setAutoFillBackground(true);
    this->setPalette(pal);
    this->update();
}


void MainWindow::on_actionMessage_Color_triggered()
{
    MessageColorDialog * messageColorDialog = new MessageColorDialog(this);
    messageColorDialog->show();
    connect(messageColorDialog, &MessageColorDialog::accepted, this, &MainWindow::updateMessagesSlot);
}


void MainWindow::on_actionIP_show_hide_triggered()
{
    Vuex::Instance().showIp = !Vuex::Instance().showIp;
    updateMessages();
}


void MainWindow::on_actionTime_Show_Hide_triggered()
{
    Vuex::Instance().showTime = !Vuex::Instance().showTime;
    updateMessages();
}

