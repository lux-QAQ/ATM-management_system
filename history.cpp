#include "history.h"
#include "ui_history.h"

history::history(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
}

history::~history()
{
    delete ui;
}

void history::on_pushButton_clicked()//返回主界面
{
    this->hide();
    xinxi *x=new xinxi;
    x->show();
}
