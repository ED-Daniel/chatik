#ifndef MESSAGECOLORDIALOG_H
#define MESSAGECOLORDIALOG_H

#include <QDialog>
#include <QColor>
#include "vuex.h"

namespace Ui {
class MessageColorDialog;
}

class MessageColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MessageColorDialog(QWidget *parent = nullptr);
    ~MessageColorDialog();

    QColor messageColor = Vuex::Instance().messagesColor;
    QColor textMessageColor = Vuex::Instance().textMessageColor;

private slots:
    void on_bgColorPicker_clicked();
    void on_textColorPicker_clicked();
    void on_buttonBox_rejected();
private:
    Ui::MessageColorDialog *ui;
};

#endif // MESSAGECOLORDIALOG_H
