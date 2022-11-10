#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
    QImage img("author.jpg");
    QImage author = img.scaled(img.width() / 6, img.height() / 6);
    QString data = QDate::currentDate().toString("dd.MM.yyyy");
    QLabel *label = new QLabel;
    QPushButton *buttonClose = new QPushButton("Close");

    label->setPixmap(QPixmap::fromImage(author));
    label->setScaledContents(true);

    layout->addWidget(label);
    layout->addWidget(new QLabel("Версия соборки: 6.3.1"));
    layout->addWidget(new QLabel("Версия Qt с которой собиралось: " + QString(QT_VERSION_STR)));
    layout->addWidget(new QLabel("Зотьев Егор Евгеньевич"));
    layout->addWidget(new QLabel("Дата сборки: " + data));

    ui->setLayout(layout);

    connect(buttonClose, &QPushButton::clicked, dialog, &QDialog::close);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
