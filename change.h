#ifndef CHANGE_H
#define CHANGE_H

#include <QWidget>
#include "jiaoyi.h"

namespace Ui {
class change;
}

class change : public QWidget
{
    Q_OBJECT

public:
     change(QWidget *parent = nullptr);
     ~change();


private slots:
    void on_pushButton_clicked();
    int findAccountIndexByCardID(int cardID);



private:
    Ui::change *ui;
};

#endif // CHANGE_H
