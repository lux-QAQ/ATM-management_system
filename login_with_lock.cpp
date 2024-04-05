#include "login_with_lock.h"
#include "widget.h"
#include "ui_widget.h"


#include "ui_login_with_lock.h"
#include "data.h"
#include "widget.h"
#include "ui_widget.h"
#include "xiugai.h"
#include "forget.h"
//Widget *main_menu=new Widget;
//template int findStructIdByMember(const QList<Account> &structList, int Account::*member, const int &value);


login_with_lock::login_with_lock(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login_with_lock)
{
    ui->setupUi(this);


   // data dataInstance;
    //int accountID = findStructIdByMember(accounts, &Account::card_ID, 67890);

    //wrongPasswordCount = 0;
    connect(ui->lineE_pwd,SIGNAL(returnPressed()),this,SLOT(on_btn_login_clicked()));//谁发出，发出什么，谁处理信号，怎么处理信号
    ui->lineE_pwd->setEchoMode(QLineEdit::Password);
    connect(ui->radioButton, &QRadioButton::clicked, this, &login_with_lock::on_radioButton_clicked);

}

login_with_lock::~login_with_lock()
{
    delete ui;
}



void login_with_lock::on_radioButton_clicked()
{
    if (ui->radioButton->isChecked()) {
        ui->lineE_pwd->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineE_pwd->setEchoMode(QLineEdit::Password);
    }
}

int login_with_lock::findStatementIndexByAccountID(int accountID)
{
    for (int i = 0; i < statements.size(); ++i) {
        if (statements[i].matchAccountID(accountID)) {
            return i; // 找到对应的索引
        }
    }
    return -1; // 没有找到
}

int login_with_lock::findAccountIndexByCardID(int cardID)
{
    for (int i = 0; i < accounts.size(); ++i) {
        if (accounts[i].matchCardID(cardID)) {
            return i; // 找到对应的索引
        }
    }
    return -1; // 没有找到
}








void login_with_lock::on_btn_login_clicked()
{
    QString inputPassword = ui->lineE_pwd->text();
        QString card_ID_qstring = ui->lineE_user_name->text();

        bool toint_ok;


        int card_ID = card_ID_qstring.toInt(&toint_ok);
        if (!toint_ok) {
            // 转换失败，弹出消息框提示用户
            QMessageBox::critical(this, "Error", "Card ID 必须是纯数字!");
            ui->lineE_user_name->clear();
        } else {
            // 转换成功，继续处理逻辑
            // 可以将 card_ID 添加到结构体中或者进行其他操作

            int card_ID_index=findAccountIndexByCardID(card_ID);//通过card_ID查找对应结构体的数组下标
            if(inputPassword.isEmpty()||card_ID_qstring.isEmpty())
            {
                QMessageBox::warning(this, "ATM ", "卡号或者密码不能为空");
                return;
            }

            if(card_ID_index==-1)
            {
                 QMessageBox::warning(this, "ATM ", QString::number(card_ID) + "不存在");
                 return;
            }

            // 设置QLineEdit的EchoMode为Password
           //ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

            if (inputPassword == accounts[card_ID_index].passward) {
                if(accounts[card_ID_index].isAdministrator==1)
                {
                    //这里写管理员登录逻辑
                    accountID=card_ID;
                    accounts[card_ID_index].login_failures=0;
                    //密码是否为初始密码检查
                    if(accounts[login_with_lock::findAccountIndexByCardID(accountID)].passward=="123456")
                    {
                        QMessageBox::information(this, "ATM ", "您的密码为默认密码，为了保护资产安全，请立即修改密码！");
                        this -> hide();
                        xiugai *x_temp = new xiugai;
                        //this -> hide();
                        x_temp -> show();
                        return ;
                    }
                    administrator *a= new administrator;
                    this->hide();
                    a->show();

                    //QMessageBox::information(this, "ATM ", "管理员登陆成功！：）");





                    data::saveAccountsToFile();
                    data::saveStatementsToFile();
                    return ;
                }




                // 密码正确，执行登录操作

                if(accounts[card_ID_index].passward!="123456")
                {QMessageBox::information(this, "ATM ", "登陆成功！：）");}
               accounts[card_ID_index].login_failures=0;
               data::saveAccountsToFile();
               //data::saveStatementsToFile();
               accountID=card_ID;
                 //密码是否为初始密码检查
               if(accounts[login_with_lock::findAccountIndexByCardID(accountID)].passward=="123456")
               {
                   QMessageBox::information(this, "ATM ", "您的密码为默认密码，为了保护资产安全，请立即修改管理员密码！");
                   this -> hide();
                   xiugai *x_temp = new xiugai;
                   //this -> hide();
                   x_temp -> show();
                   return ;
               }
               //qDebug() << accountID<<"在login中查询";
               Widget *main_menu=new Widget;
               this->hide();
               main_menu->show();



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

                   main_menu->ui->numberLabel->setText(maskedNumber);

                   // 处理用户名显示逻辑
                   QString username = accounts[card_ID_index].username;
                   QString firstName = username.left(1);
                   QString maskedUsername = firstName + QString(username.length() - 1, '*');

                   main_menu->ui->usernameLabal->setText(maskedUsername);
               }
               else {
                   // 账户未找到，显示错误信息
                   QMessageBox::warning(this, "ATM", "账户未找到");
               }




                // 在这里执行登录成功后的操作，如跳转到主界面等
            } else {
                // 密码错误
                accounts[card_ID_index].login_failures++;
                if (accounts[card_ID_index].login_failures >= maxAttempts) {
                    // 锁卡操作
                    QMessageBox::warning(this, "ATM ", QString::number(card_ID) + "已锁卡，请联系管理员.");
                    //qApp->quit(); // 锁卡后直接退出应用
                    //ui->loginButton->setEnabled(false);
                    //ui->passwordLineEdit->setEnabled(false);
                    //wrongPasswordCount = 0; // 清零计数器
                } else {
                    QMessageBox::warning(this, "ATM ", " 密码错误 你还有 " + QString::number(maxAttempts - accounts[card_ID_index].login_failures) + " 尝试机会.");
                }
            }
        }

        data::saveAccountsToFile();
        data::saveStatementsToFile();
}



void login_with_lock::on_lineE_user_name_textEdited(const QString &arg1)
{
    QRegExp re("\\d+"); // 创建一个正则表达式匹配纯数字
        if (re.exactMatch(arg1)) // 如果输入是纯数字
        {
            ui->card_IDLabel->setText("<font color='green'>✓</font>"); // 在输入框后面显示绿色的勾
        }
        else
        {
            ui->card_IDLabel->setText("<font color='red'>卡号必须为纯数字</font>"); // 在输入框后面显示“卡号必须为纯数字”
        }
}

bool login_with_lock::password_check()
{
    if(accounts[login_with_lock::findAccountIndexByCardID(accountID)].passward=="123456")
    {


        //xiugai *x_temp = new xiugai;
        //this -> hide();
        //x_temp -> show();
        return false;
    }
    else
    {
        return true;
    }



}



void login_with_lock::on_btn_forget_clicked()
{
    Forget *f= new Forget;
    this->hide();
    f->show();
}

