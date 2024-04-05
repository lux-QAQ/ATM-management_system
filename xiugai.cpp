#include "xiugai.h"
#include "ui_xiugai.h"
#include "data.h"
#include "administrator.h"
#include "login_with_lock.h"
#include <QDebug>


xiugai::xiugai(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::xiugai)
{
    ui->setupUi(this);
    password_check();
}

xiugai::~xiugai()
{
    delete ui;
}

void xiugai::on_pushButton_2_clicked()//返回主界面
{
    this->hide();
    //qDebug()<<accountID<<"在修改界面查询";

    if(accounts[login_with_lock::findAccountIndexByCardID(accountID)].isAdministrator==1)
    {
        administrator *a=new administrator;
        this->hide();
        a->show();
        return;
    }
    Widget *m=new Widget;

    int card_ID_index = login_with_lock::findAccountIndexByCardID(accountID);
    qDebug() << card_ID_index << "debug";
    qDebug() << accountID << "debug";

    if (card_ID_index != -1)
    {
        int numberid = accounts[card_ID_index].card_ID;
        QString numberStr = QString::number(numberid);

        // 处理卡号显示逻辑
        QString maskedNumber;
        if (numberStr.length() <= 4) {
            maskedNumber = numberStr;
        } else {
            maskedNumber = "**** **** **** " + numberStr.right(4);
        }

        m->ui->numberLabel->setText(maskedNumber);

        // 处理用户名显示逻辑
        QString username = accounts[card_ID_index].username;
        QString firstName = username.left(1);
        QString maskedUsername = firstName + QString(username.length() - 1, '*');

        m->ui->usernameLabal->setText(maskedUsername);
        m->show();
    }
    else {
        // 账户未找到，显示错误信息
        QMessageBox::warning(this, "ATM", "账户未找到");
    }

}

void xiugai::on_checkBox_stateChanged(int arg1)
{
    if (ui->checkBox->isChecked()) {
        ui->lineEdit->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit->setEchoMode(QLineEdit::Password);
    }
}

void xiugai::on_checkBox_2_stateChanged(int arg1)
{
    if (ui->checkBox_2->isChecked()) {
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}

void xiugai::on_checkBox_3_stateChanged(int arg1)
{
    if (ui->checkBox_3->isChecked()) {
        ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    }
}




void xiugai::on_pushButton_clicked()
{
    QString oldpassword=ui->lineEdit->text();
    QString newpassword=ui->lineEdit_2->text();
    QString newpassword2=ui->lineEdit_3->text();
    int card_ID_index=login_with_lock::findAccountIndexByCardID(accountID);
    if(oldpassword != accounts[card_ID_index].passward )
    { QMessageBox::information(this, "ATM ", "原密码错误");}
    if (oldpassword == accounts[card_ID_index].passward )
    {
        if(newpassword.isEmpty())
        {
            QMessageBox::warning(this, "ATM ", "密码不能为空");
            return;
        }


        else{
            if (oldpassword == newpassword&&newpassword==newpassword2)
            {QMessageBox::information(this, "ATM ", "不能与原密码相同");
                return;
            }
            if (newpassword=="123456")
            {QMessageBox::information(this, "ATM ", "为了安全，不允许将密码修改为默认密码！");
                return;
            }
            if ( newpassword==newpassword2)
            {QMessageBox::information(this, "ATM ", "修改成功");
                accounts[card_ID_index].passward=newpassword;
                data::saveAccountsToFile();

                if(accounts[card_ID_index].isAdministrator==1)
                {
                    administrator *a=new administrator;
                    this->hide();
                    a->show();
                    return;
                }


                this->hide();
                Widget *m=new Widget;

                int card_ID_index = login_with_lock::findAccountIndexByCardID(accountID);
                qDebug() << card_ID_index << "debug";
                qDebug() << accountID << "debug";

                if (card_ID_index != -1)
                {
                    int numberid = accounts[card_ID_index].card_ID;
                    QString numberStr = QString::number(numberid);

                    // 处理卡号显示逻辑
                    QString maskedNumber;
                    if (numberStr.length() <= 4) {
                        maskedNumber = numberStr;
                    } else {
                        maskedNumber = "**** **** **** " + numberStr.right(4);
                    }

                    m->ui->numberLabel->setText(maskedNumber);

                    // 处理用户名显示逻辑
                    QString username = accounts[card_ID_index].username;
                    QString firstName = username.left(1);
                    QString maskedUsername = firstName + QString(username.length() - 1, '*');

                    m->ui->usernameLabal->setText(maskedUsername);
                    m->show();
                }
                else {
                    // 账户未找到，显示错误信息
                    QMessageBox::warning(this, "ATM", "账户未找到");
                }




                //Widget *m=new Widget;
                //Widget:main_menu->show();
            }
            else
                QMessageBox::information(this, "ATM ", "两次密码不一致");

        }

    }
}

void xiugai::on_lineEdit_3_textEdited(const QString &arg1)
{
    QString newpassword = ui->lineEdit_2->text();
    QString commitpassword = ui->lineEdit_3->text();



    if(newpassword==commitpassword&!newpassword.isEmpty()&&newpassword!="123456")
    {

        ui->newPasswordLabel->setText("<font color='green'>✓</font>"); // 在输入框后面显示绿色的勾
        ui->commitPasswardLabel->setText("<font color='green'>✓</font>"); // 在输入框后面显示绿色的勾

    }
    else {
        if(!newpassword.isEmpty())
        {
            if(newpassword=="123456")
            {
                ui->commitPasswardLabel->setText("<font color='red'>为了安全，不允许将密码修改为默认密码！</font>");
                ui->newPasswordLabel->setText("<font color='red'>为了安全，不允许将密码修改为默认密码！</font>");

            }
            else
            {
            ui->newPasswordLabel->setText("<font color='red'>两次输入的密码不一致</font>");
            ui->commitPasswardLabel->setText("<font color='red'>两次输入的密码不一致</font>");
            }
        }
        else {
            ui->newPasswordLabel->setText("<font color='red'>密码不能为空</font>");
            ui->commitPasswardLabel->setText("<font color='red'>密码不能为空</font>");
        }


    }
}
void xiugai::password_check()
{
    if(accounts[login_with_lock::findAccountIndexByCardID(accountID)].passward=="123456")
    {
        ui->pushButton_2->setEnabled(false);
    }
}


void xiugai::on_lineEdit_2_textEdited(const QString &arg1)
{
    QString newpassword = ui->lineEdit_2->text();
    QString commitpassword = ui->lineEdit_3->text();
    if(newpassword=="123456")
    {
        ui->newPasswordLabel->setText("<font color='red'>为了安全，不允许将密码修改为默认密码！</font>");
    }
}

