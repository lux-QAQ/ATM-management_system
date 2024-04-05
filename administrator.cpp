#include "administrator.h"
#include "ui_administrator.h"
#include "xiugai.h"
#include "login_with_lock.h"
#include "accountmanagementwidget.h"
#include "backup.h"
#include <QDir>

administrator::administrator(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::administrator)
{
    ui->setupUi(this);
    administrator::checkBackup();
}

administrator::~administrator()
{
    delete ui;
}

void administrator::on_pushButton_4_clicked()
{

    this->hide();
    xiugai *x=new xiugai;
    x->show();
}


void administrator::on_pushButton_5_clicked()
{
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


void administrator::on_pushButton_2_clicked()
{
    AccountManagementWidget *a= new AccountManagementWidget;
    this->hide();
    a->show();
}


void administrator::on_pushButton_clicked()
{
    Backup *b=new Backup;
    this->hide();
    b->show();
}

bool administrator::checkBackup()
{
    QString backupFolderPath = QCoreApplication::applicationDirPath() + "/backup";
    QDir backupFolder(backupFolderPath);

    bool flag = false;

    // 检查backup文件夹是否存在，如果不存在则创建
    if (!backupFolder.exists())
    {
        qDebug() << "已创建备份文件夹...";
        if (!backupFolder.mkdir(backupFolderPath)) {
            qDebug() << "创建备份文件夹失败！";
            flag = false;
        }
    }

    // 获取备份文件夹下所有文件夹
    QStringList backupFolders = backupFolder.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    if (backupFolders.isEmpty()) {
        qDebug() << "备份文件夹中没有子文件夹";
        flag = false;
    } else {
        qDebug() << "备份文件夹中存在子文件夹";
        // 遍历每个子文件夹查找.csv.bak结尾的文件
        foreach(const QString &folderName, backupFolders)
        {
            QDir subFolder(backupFolderPath + "/" + folderName);
            QStringList filters;
            filters << "*.csv.bak";
            subFolder.setNameFilters(filters);
            QStringList fileList = subFolder.entryList();

            if (fileList.isEmpty()) {
                qDebug() << folderName << "中不存在.csv.bak结尾的文件";
            } else {
                qDebug() << folderName << "中存在.csv.bak结尾的文件";
                foreach(const QString &file, fileList)
                {
                    qDebug() << file;
                }
                flag = true; // 找到了备份文件
            }
        }
    }

    if(!flag)
    {
        QString text = "您未曾备份过数据库！\n在这种情况下直接修改数据库有无法恢复的风险\n\n！！强烈建议！！\n前往“备份/恢复”选项，备份数据库后再操作";
        QMessageBox::information(this, "误操作预警", text);
    }

    return flag;
}
