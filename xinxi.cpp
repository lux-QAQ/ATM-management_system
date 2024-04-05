#include "xinxi.h"
#include "ui_xinxi.h"
#include "transaction_history.h"
#include  "jichu.h"
#include "history.h"
#include "data.h"
#include "login_with_lock.h"
#include "forecast.h"

xinxi::xinxi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::xinxi)
{
    ui->setupUi(this);
}

xinxi::~xinxi()
{
    delete ui;
}

void xinxi::on_pushButton_clicked()//查看基础信息界面
{
    int index = login_with_lock::findAccountIndexByCardID(accountID);
    QString message = "卡号: " + QString::number(accountID) + "\n用户名："+ accounts[index].username +"\n余额："+QString::number(accounts[index].money);
    QMessageBox::information(this, "账户详情", message);
}

void xinxi::on_pushButton_2_clicked()//查看历史交易界面
{
    this->hide();
    transaction_history *h=new transaction_history;
    h->show();
}

void xinxi::on_pushButton_3_clicked()//返回主界面
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


void xinxi::on_forecastButton_clicked()
{
    Forecast *f=new Forecast;
    this->hide();
    f->show();
}

