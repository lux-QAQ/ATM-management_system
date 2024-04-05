// change.cpp

#include "change.h"
#include "ui_change.h"
#include<QFile>
#include<QTextStream>
#include "data.h"
#include "widget.h"
#include"login_with_lock.h"


change::change(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::change)
{
    ui->setupUi(this);


    int card_ID_index = findAccountIndexByCardID(accountID); // 找到对应卡号的索引
    if (card_ID_index != -1) {
        ui->balanceLineEdit->setText(QString::number(accounts[card_ID_index].money));
    } else {
        // 如果找不到对应卡号的账户，显示错误信息
        ui->balanceLineEdit->setText("Account not found");
    }
}

change::~change()
{
    delete ui;
}

void change::on_pushButton_clicked()//返回交易界面
{
    this->hide();
    jiaoyi *j=new jiaoyi;
    j->show();

}
int change::findAccountIndexByCardID(int cardID)
{
    for (int i = 0; i < accounts.size(); ++i) {
        if (accounts[i].matchCardID(cardID)) {
            return i; // 找到对应的索引
        }
    }
    return -1; // 没有找到
}



