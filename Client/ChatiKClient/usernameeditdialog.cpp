#include "usernameeditdialog.h"
#include "ui_usernameeditdialog.h"

UsernameEditDialog::UsernameEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsernameEditDialog)
{
    ui->setupUi(this);
    ui->usernameInput->setText(Vuex::Instance().getUsername());
}

UsernameEditDialog::~UsernameEditDialog()
{
    delete ui;
}

void UsernameEditDialog::on_buttonBox_accepted()
{
    Vuex::Instance().setUsername(ui->usernameInput->text());
}

