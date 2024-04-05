#include "backup.h"
#include "ui_backup.h"
#include "data.h"
#include "administrator.h"



Backup::Backup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Backup)
{
    ui->setupUi(this);
}

Backup::~Backup()
{
    delete ui;
}


void Backup::on_BuckupButton_clicked()
{
    // 获取当前时间
    QDateTime currentTime = QDateTime::currentDateTime();
    QString timeStr = currentTime.toString("yyyy-MM-dd_hh-mm-ss");

    // 打开文件管理器以供用户选择保存目录
    QString defaultDir = QApplication::applicationDirPath() + "/backup"; // 默认打开目录为.exe目录下的backup文件夹
    QString backupDir = QFileDialog::getExistingDirectory(this, tr("选择保存目录"), defaultDir, QFileDialog::ShowDirsOnly);

    if (!backupDir.isEmpty()) {
        // 创建以当前时间命名的文件夹
        QString folderName = backupDir + "/" + timeStr;
        QDir().mkpath(folderName);

        // 构建备份文件名
        QString backupFileNameAccount = "account_data.csv.bak";
        QString backupFileNameStatement = "statement_data.csv.bak";

        // 构建源文件和目标文件路径
        QString sourceAccount = QApplication::applicationDirPath() + "/account_data.csv";
        QString sourceStatement = QApplication::applicationDirPath() + "/statement_data.csv";
        QString targetAccount = folderName + "/" + backupFileNameAccount;
        QString targetStatement = folderName + "/" + backupFileNameStatement;

        // 复制文件
        if (QFile::copy(sourceAccount, targetAccount)) {
            qDebug() << "Account data backup successful!";
        } else {
            qDebug() << "Failed to backup account data!";
        }

        if (QFile::copy(sourceStatement, targetStatement)) {
            qDebug() << "Statement data backup successful!";
        } else {
            qDebug() << "Failed to backup statement data!";
        }
    } else {
        qDebug() << "Backup canceled by user!";
    }
}




void Backup::on_explorerButton_clicked()
{
    QString defaultDir = QApplication::applicationDirPath() + "/backup"; // 默认打开目录为.exe目录下的backup文件夹
    QString backupDir = QFileDialog::getExistingDirectory(this, tr("选择读取目录"), defaultDir, QFileDialog::ShowDirsOnly);
    ui->lineEdit->setText(backupDir);
    return;
}



void Backup::on_ReadButton_clicked()
{
    QString backupDir = ui->lineEdit->text(); // 获取lineEdit中的路径

    if (backupDir.isEmpty()) {
        // 如果路径为空，则打开文件管理器让用户选择路径
        QString defaultDir = QApplication::applicationDirPath() + "/backup"; // 默认打开目录为.exe目录下的backup文件夹
        backupDir = QFileDialog::getExistingDirectory(this, tr("选择备份目录"), defaultDir, QFileDialog::ShowDirsOnly);
        ui->lineEdit->setText(backupDir); // 更新lineEdit中的路径
    }

    if (!backupDir.isEmpty()) {
        // 检查路径下是否存在备份文件
        QString accountBackupPath = backupDir + "/account_data.csv.bak";
        QString statementBackupPath = backupDir + "/statement_data.csv.bak";

        if (QFile::exists(accountBackupPath) && QFile::exists(statementBackupPath)) {
            // 调用backup_readDataFromFile函数读取备份文件
            data::backup_readDataFromFile(backupDir);
            qDebug() << "Backup data read successful!";
        } else {
            qDebug() << "Invalid backup directory or backup files not found!";
            QMessageBox::critical(this, tr("Error"), tr("Invalid backup directory or backup files not found!"));
        }
    } else {
        qDebug() << "Backup directory is empty!";
        QMessageBox::critical(this, tr("Error"), tr("Backup directory is empty!"));
    }
}


void Backup::on_backButton_clicked()
{
    administrator *a=new administrator;
    this->hide();
    a->show();
}

