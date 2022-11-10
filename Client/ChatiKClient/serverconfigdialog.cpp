#include "serverconfigdialog.h"
#include "ui_serverconfigdialog.h"

ServerConfigDialog::ServerConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerConfigDialog)
{
    ui->setupUi(this);
    ui->address->setText(Vuex::Instance().getServerIp());
    ui->port->setText(QString::number(Vuex::Instance().getPort()));
}

ServerConfigDialog::~ServerConfigDialog()
{
    delete ui;
}

void ServerConfigDialog::on_buttonBox_accepted()
{
    Vuex::Instance().setServerIp(ui->address->text());
    Vuex::Instance().setPort(ui->port->text().toUInt());
}

