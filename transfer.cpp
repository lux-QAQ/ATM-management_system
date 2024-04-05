#include "transfer.h"
#include "ui_transfer.h"
#include "data.h"
#include "login_with_lock.h"
#include <QDebug>
#include "jiaoyi.h"




transfer::transfer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::transfer)
{
    ui->setupUi(this);
}

transfer::~transfer()
{
    delete ui;
}

/*void transfer::on_pushButton_2_clicked()//返回交易界面
{
    this->hide();
    jiaoyi *j=new jiaoyi;
    j->show();
}*/

void transfer::on_commitButton_clicked()
{

     bool toAccountIDValid, transferAmountValid;
        // 从toAccuntlineEdit获取转账对象的卡号
        int toAccountID = ui->toAccuntlineEdit->text().toInt(&toAccountIDValid);
        int currentUser_index=login_with_lock::findAccountIndexByCardID(accountID);

        // 检查转账对象的卡号是否为整数


        if (!toAccountIDValid)
           {
               QMessageBox::warning(this, "输入错误", "请输入有效的转账对象卡号（整数）");
               ui->toAccuntlineEdit->clear();
               return;
           }

        // 从moneylineEdit获取转账的金额
        double transferAmount = ui->moneylineEdit->text().toDouble(&transferAmountValid);
         // 检查转账金额是否为浮点数
        if (!transferAmountValid||transferAmount<=0)
           {
               QMessageBox::warning(this, "输入错误", "请输入有效的转账金额（浮点数）");
               ui->moneylineEdit->clear();
               return;
           }
       //qDebug() << "P1";
        // 获取当前用户的账户信息（假设当前用户已登录且账号信息存在）

        int toAccountID_index=login_with_lock::findAccountIndexByCardID(toAccountID);
        Account currentUser = accounts[currentUser_index]; // 自行实现获取当前用户账户信息的函数


        if(toAccountID==accountID)
        {
            QMessageBox::warning(this, "输入错误", "不能给自己转账！");
            ui->toAccuntlineEdit->clear();
            return;
        }

        if(toAccountID_index==-1)
        {
            QMessageBox::warning(this, "输入错误", "转账对象账户不存在！");
            ui->toAccuntlineEdit->clear();
            return;
        }
//qDebug() << "P2";
        // 检查余额是否足够进行转账
        if(currentUser.money < transferAmount)
        {
            QMessageBox::warning(this, "转账失败", "余额不足，无法完成转账操作");
            ui->moneylineEdit->clear();
            return;
        }

        // 扣除当前用户的余额
        accounts[currentUser_index].money -= transferAmount;

//qDebug() << "P3";



        // 增加转账对象的余额
        for(Account &acc : accounts)
        {
            if(acc.card_ID == toAccountID)
            {
                acc.money += transferAmount;
                break;
            }
        }

        // 获取statements中最大的ID
        int maxID = 0;
        for(const Statement &stmt : statements)
        {
            if(stmt.ID > maxID)
            {
                maxID = stmt.ID;
            }
        }
        //qDebug() << "P4";

        // 新的交易ID为最大ID加一
        int newTransactionID = maxID + 1;

        // 获取当前时间作为交易时间
        QString transactionTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // 将交易记录添加到statements中
        data::addStatement(newTransactionID, currentUser.card_ID, transactionTime, "转账", transferAmount, toAccountID);

        // 更新用户余额
        //updateAccount(currentUser);

        QString message = "转账成功！\n\n转账对象卡号: " + QString::number(toAccountID) + "\n转账金额: " + QString::number(transferAmount) +"\n余额"+QString::number(accounts[currentUser_index].money)+ "\n交易时间: " + transactionTime;
        QMessageBox::information(this, "转账详情", message);
        on_backButton_clicked();

        // 可以在此处刷新界面显示或进行其他操作


}

void transfer::on_backButton_clicked()
{
    this->hide();
    jiaoyi *j=new jiaoyi;
    j->show();
}

void transfer::on_toAccuntlineEdit_textEdited(const QString &arg1)
{
    bool toAccountIDValid;
    int toAccountID = arg1.toInt(&toAccountIDValid);
    QRegExp re("\\d+"); // 创建一个正则表达式匹配纯数字






    if (re.exactMatch(arg1)&&toAccountIDValid) // 如果输入是纯数字
    {
        ui->toAccuntlineEditLabel->setText("<font color='green'>✓</font>"); // 在输入框后面显示绿色的勾
        if(toAccountID==accountID)
        {
            ui->toAccuntlineEditLabel->setText("<font color='red'>不能给自己转账！</font>");
        }

        if(login_with_lock::findAccountIndexByCardID(toAccountID)==-1)
        {
            ui->toAccuntlineEditLabel->setText("<font color='red'>转账对象不存在</font>"); // 在输入框后面显示“转账对象卡号必须为纯数字”
        }
    }
    else
    {
        ui->toAccuntlineEditLabel->setText("<font color='red'>转账对象卡号必须为纯数字</font>"); // 在输入框后面显示“转账对象卡号必须为纯数字”
    }
}

void transfer::on_moneylineEdit_textEdited(const QString &arg1)
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
