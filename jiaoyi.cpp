#include "jiaoyi.h"
#include "ui_jiaoyi.h"
#include "widget.h"
#include "ui_widget.h"
#include "change.h"
#include "out.h"
#include "in.h"
#include "transfer.h"
#include "login_with_lock.h"
#include "data.h"

jiaoyi::jiaoyi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jiaoyi)
{
    ui->setupUi(this);
}

jiaoyi::~jiaoyi()
{
    delete ui;
}

void jiaoyi::on_pushButton_5_clicked()//返回主界面
{
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
}

void jiaoyi::on_pushButton_4_clicked()//查看余额
{
    this->hide();
    change *g=new change;
    g->show();
}

void jiaoyi::on_pushButton_clicked()//进入取款界面
{
    this->hide();
    out *o=new out;
    o->show();
}

void jiaoyi::on_pushButton_3_clicked()//进入存款界面
{
    this->hide();
    in *i=new in;
    i->show();
}

void jiaoyi::on_pushButton_2_clicked()//进入转账界面
{
    this->hide();
    transfer *t=new transfer;
    t->show();
}
