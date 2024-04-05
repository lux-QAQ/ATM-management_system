#ifndef IN_H
#define IN_H

#include <QWidget>
#include "jiaoyi.h"

namespace Ui {
class in;
}

class in : public QWidget
{
    Q_OBJECT

public:
    explicit in(QWidget *parent = nullptr);
    ~in();
     int findAccountIndexByCardID(int cardID);

private slots:
    void on_pushButton_2_clicked();


    void on_confirmButton_clicked();

    void on_depositlineEdit_textEdited(const QString &arg1);

private:
    Ui::in *ui;

};

#endif // IN_H
