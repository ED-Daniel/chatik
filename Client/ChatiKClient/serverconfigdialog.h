#ifndef SERVERCONFIGDIALOG_H
#define SERVERCONFIGDIALOG_H

#include <QDialog>
#include "vuex.h"

namespace Ui {
class ServerConfigDialog;
}

class ServerConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerConfigDialog(QWidget *parent = nullptr);
    ~ServerConfigDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ServerConfigDialog *ui;
};

#endif // SERVERCONFIGDIALOG_H
