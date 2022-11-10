#include "serverconfigdialog.h"
#include "ui_serverconfigdialog.h"

ServerConfigDialog::ServerConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerConfigDialog)
{
    ui->setupUi(this);
    ui->address->setText(Vuex::Instance().serverIp);
    ui->port->setText(QString::number(Vuex::Instance().port));
}

ServerConfigDialog::~ServerConfigDialog()
{
    delete ui;
}

void ServerConfigDialog::on_buttonBox_accepted()
{
    Vuex::Instance().serverIp = ui->address->text();
    Vuex::Instance().port = ui->port->text().toUInt();
}

