#ifndef SUCCES_H
#define SUCCES_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class succes;
}

class succes : public QWidget
{
    Q_OBJECT

public:
    explicit succes(QWidget *parent = nullptr);
    ~succes();

private slots:
    void on_pushButton_clicked();

private:
    Ui::succes *ui;
};

#endif // SUCCES_H
