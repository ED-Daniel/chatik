#include "xmlsavedialog.h"
#include "ui_xmlsavedialog.h"

XmlSaveDialog::XmlSaveDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::XmlSaveDialog)
{
    ui->setupUi(this);
}

XmlSaveDialog::~XmlSaveDialog()
{
    delete ui;
}

void XmlSaveDialog::on_buttonBox_accepted()
{
    QDomDocument doc("chatiKHistory.xml");
    QDomElement root = doc.createElement("chat");
    doc.appendChild(root);

    for (const auto message : Client::Instance().getMessages()) {
        QDomElement msgElement = doc.createElement("message");
        root.appendChild(msgElement);

        QDomElement dateTag = doc.createElement("datetime");
        msgElement.appendChild(dateTag);

        QDomText dateText = doc.createTextNode(message->getTime());
        dateTag.appendChild(dateText);

        QDomElement ipTag = doc.createElement("ip");
        msgElement.appendChild(ipTag);

        QDomText ipText = doc.createTextNode(message->getIp());
        ipTag.appendChild(ipText);

        QDomElement nameTag = doc.createElement("username");
        msgElement.appendChild(nameTag);

        QDomText usernameText = doc.createTextNode(message->getSender());
        nameTag.appendChild(usernameText);

        QDomElement text = doc.createElement("text");
        msgElement.appendChild(text);

        QDomText messageText = doc.createTextNode(message->getSender());
        text.appendChild(messageText);
    }
    QString path = QFileDialog::getSaveFileName(0, QObject::tr("Укажите путь для сохранения"), QDir::homePath() + "/" + ui->fileName->text().trimmed() + ".xml", QObject::tr("XML files (*.xml)"));

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug("Failed to open file for writing");
        return;
    }

    QTextStream stream( &file );
    stream << doc.toString();
    qDebug() << file.fileName();
    file.close();
}

