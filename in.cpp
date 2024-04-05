#include "in.h"
#include "ui_in.h"
#include "login_with_lock.h"
#include "data.h"
#include "change.h"
#include <QMessageBox>

in::in(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::in)
{
    ui->setupUi(this);
}

in::~in()
{
    delete ui;
}

void in::on_pushButton_2_clicked()
{
    this->hide();
    jiaoyi *j = new jiaoyi;
    j->show();
}

void in::on_confirmButton_clicked()
{

    bool transferdepositValid;
    double deposit = ui->depositlineEdit->text().toDouble(&transferdepositValid);
    int card_ID_index = findAccountIndexByCardID(accountID);
    if (!transferdepositValid||deposit<=0)
       {
           QMessageBox::warning(this, "输入错误", "请输入有效的存款金额（浮点数）");
           ui->depositlineEdit->clear();
           return;
       }
    if (card_ID_index != -1)
    {
        // 更新账户余额
        accounts[card_ID_index].money += deposit;

        // 保存更新后的账户信息到文件中
        //data::saveAccountsToFile();
         //QMessageBox::information(this, "ATM ", "存款成功！：）");
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
QString message = "存款成功！\n\n存款对象卡号: " + QString::number(accountID) + "\n存款金额: " + QString::number(deposit) +"\n余额"+QString::number(accounts[card_ID_index].money)+ "\n交易时间: " + transactionTime;
QMessageBox::information(this, "存款详情", message);
                 // 将交易记录添加到statements中
                 data::addStatement(newTransactionID, accountID, transactionTime, "存款", deposit, accountID);
         this->hide();
         jiaoyi *j = new jiaoyi;
         j->show();
    }
    else {
        // 账户未找到，显示错误信息
        QMessageBox::warning(this, "ATM", "账户未找到");
    }
}
int in::findAccountIndexByCardID(int cardID)
{
    // 在当前类中查找账户索引
    for (int i = 0; i < accounts.size(); ++i) {
        if (accounts[i].matchCardID(cardID)) {
            return i; // 找到对应的索引
        }
    }
    return -1; // 没有找到
}

void in::on_depositlineEdit_textEdited(const QString &arg1)
{
    bool transferAmountValid;
    double transferAmount = arg1.toDouble(&transferAmountValid);
    QRegExp re("^\\d*\\.?\\d+$"); // 创建一个正则表达式匹配浮点数
    //int currentUser_index=login_with_lock::findAccountIndexByCardID(accountID);



    if (re.exactMatch(arg1)&& transferAmountValid && transferAmount > 0) // 如果输入是浮点数
    {
        ui->moneylineEditlabel->setText("<font color='green'>✓</font>"); // 在输入框后面显示绿色的勾

    }
    else
    {
        ui->moneylineEditlabel->setText("<font color='red'>存款金额必须为有效的浮点数</font>"); // 在输入框后面显示“存款金额必须为有效的浮点数”
    }
}
