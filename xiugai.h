#ifndef XIUGAI_H
#define XIUGAI_H

#include <QWidget>
#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <data.h>
#include<login_with_lock.h>

namespace Ui {
class xiugai;
}

class xiugai : public QWidget
{
    Q_OBJECT

public:
    explicit xiugai(QWidget *parent = nullptr);
    ~xiugai();
    static  int findStatementIndexByAccountID(int accountID);
    static int findAccountIndexByCardID(int cardID);

private slots:
    void on_pushButton_2_clicked();
    void password_check();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_pushButton_clicked();



    void on_lineEdit_3_textEdited(const QString &arg1);

    void on_lineEdit_2_textEdited(const QString &arg1);

private:
    Ui::xiugai *ui;
};

#endif // XIUGAI_H
