#include "widget.h"
#include "ui_widget.h"
#include "xiugai.h"
#include "jiaoyi.h"
#include "xinxi.h"
#include "login_with_lock.h"
#include "data.h"
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    //comein();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()//进入修改密码
{
    this->hide();
    xiugai *x=new xiugai;
    x->show();
}

void Widget::on_pushButton_2_clicked()//进入交易界面
{
    this->hide();
    jiaoyi *j=new jiaoyi;
    j->show();
}

void Widget::on_pushButton_3_clicked()//进入信息界面
{
    this->hide();
    xinxi *x=new xinxi;
    x->show();
}



void Widget::on_ExitButton_clicked()
{
    QMessageBox::warning(this, "温馨提示", "请牢记卡号和密码");
    this->hide();
    login_with_lock *l2=new login_with_lock;
    QApplication* l = qApp;
    int temp=1;
    do
    {
     temp = QRandomGenerator::global()->bounded(1, 4);
    }while(temp==num_UI);
    num_UI=temp;
    QString num = ":/res/qss/style-" + QString::number(num_UI) + ".qss";

    QFile file(num);/*QSS文件所在的路径*/

    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    l->setStyleSheet(stylesheet);
    file.close();




    l2->show();
}

void Widget::comein()
{
    //qDebug()<<accountID << "在widget中查询";
   // qDebug()<<num_UI << "在widget中查询";
    if(accounts[login_with_lock::findAccountIndexByCardID(accountID)].passward=="123456")
    {
        this -> hide();
        QMessageBox::information(this, "ATM ", "您的密码为默认密码，为了保护资产安全，请立即修改密码！");
       // this -> hide();
        xiugai *x_temp = new xiugai;
        //this -> hide();
        x_temp -> show();
        return ;
    }


}





