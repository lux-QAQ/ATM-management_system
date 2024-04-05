#include "jichu.h"
#include "ui_jichu.h"

jichu::jichu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::jichu)
{
    ui->setupUi(this);
}

jichu::~jichu()
{
    delete ui;
}

void jichu::on_pushButton_clicked()//返回信息界面
{
    this->hide();
    xinxi *x=new xinxi;
    x->show();
}
