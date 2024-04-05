#ifndef TRANSFER_H
#define TRANSFER_H

#include <QWidget>


namespace Ui {
class transfer;
}

class transfer : public QWidget
{
    Q_OBJECT

public:
    explicit transfer(QWidget *parent = nullptr);
    ~transfer();

private slots:
    //void on_pushButton_2_clicked();

    void on_commitButton_clicked();

    void on_backButton_clicked();

    void on_toAccuntlineEdit_textEdited(const QString &arg1);

    void on_moneylineEdit_textEdited(const QString &arg1);

private:
    Ui::transfer *ui;
};

#endif // TRANSFER_H
