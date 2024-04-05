#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <QWidget>

namespace Ui {
class administrator;
}

class administrator : public QWidget
{
    Q_OBJECT

public:
    explicit administrator(QWidget *parent = nullptr);
    bool checkBackup();
    ~administrator();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::administrator *ui;
};

#endif // ADMINISTRATOR_H
