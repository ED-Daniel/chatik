#ifndef XMLSAVEDIALOG_H
#define XMLSAVEDIALOG_H

#include <QDialog>
#include <QDomDocument>
#include <QFileDialog>

#include "client.h"
#include "transportinginterfaces.h"

namespace Ui {
class XmlSaveDialog;
}

class XmlSaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit XmlSaveDialog(QWidget *parent = nullptr);
    ~XmlSaveDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::XmlSaveDialog *ui;
};

#endif // XMLSAVEDIALOG_H
