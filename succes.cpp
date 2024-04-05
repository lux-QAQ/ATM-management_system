#include "succes.h"
#include "ui_succes.h"

succes::succes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::succes)
{
    ui->setupUi(this);
}

succes::~succes()
{
    delete ui;
}

void succes::on_pushButton_clicked()
{
    this->hide();
    Widget *m=new Widget;
    m->show();
}
