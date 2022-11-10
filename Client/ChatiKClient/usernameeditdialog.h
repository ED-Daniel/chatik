#ifndef USERNAMEEDITDIALOG_H
#define USERNAMEEDITDIALOG_H

#include <QDialog>
#include "vuex.h"

namespace Ui {
class UsernameEditDialog;
}

class UsernameEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsernameEditDialog(QWidget *parent = nullptr);
    ~UsernameEditDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::UsernameEditDialog *ui;
};

#endif // USERNAMEEDITDIALOG_H
