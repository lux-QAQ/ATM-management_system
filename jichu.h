#ifndef JICHU_H
#define JICHU_H

#include <QWidget>
#include  "xinxi.h"

namespace Ui {
class jichu;
}

class jichu : public QWidget
{
    Q_OBJECT

public:
    explicit jichu(QWidget *parent = nullptr);
    ~jichu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::jichu *ui;
};

#endif // JICHU_H
