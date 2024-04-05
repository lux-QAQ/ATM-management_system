#ifndef JIAOYI_H
#define JIAOYI_H

#include <QWidget>


namespace Ui {
class jiaoyi;
}

class jiaoyi : public QWidget
{
    Q_OBJECT

public:
    explicit jiaoyi(QWidget *parent = nullptr);
    ~jiaoyi();

private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::jiaoyi *ui;
};

#endif // JIAOYI_H
