#ifndef OUT_H
#define OUT_H

#include <QWidget>
#include "jiaoyi.h"

namespace Ui {
class out;
}

class out : public QWidget
{
    Q_OBJECT

public:
    explicit out(QWidget *parent = nullptr);
    ~out();

private slots:
    void on_pushButton_2_clicked();



    void on_withdrawallButton_clicked();

    void on_withdrawalllineEdit_textEdited(const QString &arg1);

private:
    Ui::out *ui;
     int findAccountIndexByCardID(int cardID);
};

#endif // OUT_H
