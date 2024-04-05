#include "out.h"
#include "ui_out.h"
#include "login_with_lock.h"
#include "data.h"
#include "change.h"
#include <QMessageBox>
#include"in.h"
#include <QDebug>


out::out(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::out)
{
    ui->setupUi(this);
}

out::~out()
{
    delete ui;
}

void out::on_pushButton_2_clicked()//返回交易界面
{
    this->hide();
    jiaoyi *j=new jiaoyi;
    j->show();
}





void out::on_withdrawallButton_clicked()
{

    bool transferdepositValid;
    double deposit = ui->withdrawalllineEdit->text().toDouble(&transferdepositValid);
    if (!transferdepositValid||deposit<=0)
       {
           QMessageBox::warning(this, "输入错误", "请输入有效的取款金额（浮点数）");
           ui->withdrawalllineEdit->clear();
           return;
       }
    in instance;
       int card_ID_index = instance.findAccountIndexByCardID(accountID);
       if(accounts[card_ID_index].money < deposit)
       {
           QMessageBox::warning(this, "转账失败", "余额不足，无法完成转账操作");
           ui->withdrawalllineEdit->clear();
           return;
       }
       if (card_ID_index != -1) {
           // 更新账户余额
           accounts[card_ID_index].money -= deposit;

           // 保存更新后的账户信息到文件中
          // data::saveAccountsToFile();



           // 获取statements中最大的ID
                   int maxID = 0;
                   for(const Statement &stmt : statements)
                   {
                       if(stmt.ID > maxID)
                       {
                           maxID = stmt.ID;
                       }
                   }
                   // 新的交易ID为最大ID加一
                           int newTransactionID = maxID + 1;

                           // 获取当前时间作为交易时间
                           QString transactionTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

                           // 将交易记录添加到statements中
                           data::addStatement(newTransactionID, accountID, transactionTime, "取款", deposit, accountID);





            //QMessageBox::information(this, "ATM ", "取款成功！：）");
                           QString message = "取款成功！\n\n取款对象卡号: " + QString::number(accountID) + "\n取款金额: " + QString::number(deposit) +"\n余额"+QString::number(accounts[card_ID_index].money)+ "\n交易时间: " + transactionTime;
                           QMessageBox::information(this, "取款详情", message);
            this->hide();
            jiaoyi *j = new jiaoyi;
            j->show();
       }
       else {
           // 账户未找到，显示错误信息
           QMessageBox::warning(this, "ATM", "账户未找到");
       }
}

void out::on_withdrawalllineEdit_textEdited(const QString &arg1)
{
    bool transferAmountValid;
    double transferAmount = arg1.toDouble(&transferAmountValid);
    QRegExp re("^\\d*\\.?\\d+$"); // 创建一个正则表达式匹配浮点数
    int currentUser_index=login_with_lock::findAccountIndexByCardID(accountID);



    if (re.exactMatch(arg1)&& transferAmountValid && transferAmount > 0) // 如果输入是浮点数
    {
        ui->moneylineEditlabel->setText("<font color='green'>✓</font>"); // 在输入框后面显示绿色的勾
        if(accounts[currentUser_index].money < transferAmount)
        {
            ui->moneylineEditlabel->setText("<font color='red'>余额不足</font>");
        }
    }
    else
    {
        ui->moneylineEditlabel->setText("<font color='red'>转账金额必须为有效的浮点数</font>"); // 在输入框后面显示“转账金额必须为有效的浮点数”
    }
}
