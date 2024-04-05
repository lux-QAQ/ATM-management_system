#include "forget.h"
#include "ui_forget.h"
#include <qstring.h>
#include <QMessageBox>
#include "login_with_lock.h"
#include "data.h"

Forget::Forget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Forget)
{
    ui->setupUi(this);
}

Forget::~Forget()
{
    delete ui;
}

void Forget::on_commitButton_clicked()
{
    bool card_ID_check;
    QString card_ID_qstring =  ui->card_IDlineEdit->text();
    QString phone = ui->phonelineEdit->text();
    QString password = ui->passwordlineEdit->text();
    QString confirm_password = ui->commitlineEdit->text();
    int card_ID = card_ID_qstring.toInt(&card_ID_check);
    int index=login_with_lock::findAccountIndexByCardID(card_ID);
    if((!card_ID_check)||(index==-1))
    {
        QMessageBox::warning(this, "输入错误", "请输入有效的卡号（整数）");
        ui->card_IDlineEdit->clear();
        return;
    }
    if(accounts[index].phone!=phone)
    {
        QMessageBox::warning(this, "安全保护", "卡号未与手机号绑定");
        ui->phonelineEdit->clear();
        //ui->commitlineEdit->clear();
        return;
    }
    if(password=="123456"||confirm_password=="123456")
    {
        QMessageBox::warning(this, "安全保护", "修改的密码不能是默认密码");
        ui->passwordlineEdit->clear();
        ui->commitlineEdit->clear();
        return;
    }
    accounts[index].passward=password;
    accounts[index].login_failures=0;
    QMessageBox::warning(this, "修改密码", "修改密码成功！");
    data::saveAccountsToFile();
    this->hide();
    login_with_lock *l=new login_with_lock;
    l->show();
    return;
}


void Forget::on_pushButton_clicked()
{
    this->hide();
    login_with_lock *l=new login_with_lock;
    l->show();
    return;
}

