#include "messagecolordialog.h"
#include "ui_messagecolordialog.h"

#include <QColorDialog>

MessageColorDialog::MessageColorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageColorDialog)
{
    ui->setupUi(this);
}

MessageColorDialog::~MessageColorDialog()
{
    delete ui;
}

void MessageColorDialog::on_bgColorPicker_clicked()
{
    Vuex::Instance().messagesColor = QColorDialog::getColor();
}


void MessageColorDialog::on_textColorPicker_clicked()
{
    Vuex::Instance().textMessageColor = QColorDialog::getColor();
}


void MessageColorDialog::on_buttonBox_rejected()
{
    Vuex::Instance().messagesColor = messageColor;
    Vuex::Instance().textMessageColor = textMessageColor;
}

