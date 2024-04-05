#ifndef BACKUP_H
#define BACKUP_H

#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>




namespace Ui {
class Backup;
}

class Backup : public QWidget
{
    Q_OBJECT

public:
    explicit Backup(QWidget *parent = nullptr);
    ~Backup();

private slots:
    void on_BuckupButton_clicked();

    void on_explorerButton_clicked();

    void on_ReadButton_clicked();

    void on_backButton_clicked();

private:
    Ui::Backup *ui;
};

#endif // BACKUP_H
