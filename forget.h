#ifndef FORGET_H
#define FORGET_H

#include <QWidget>

namespace Ui {
class Forget;
}

class Forget : public QWidget
{
    Q_OBJECT

public:
    explicit Forget(QWidget *parent = nullptr);
    ~Forget();

private slots:
    void on_commitButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::Forget *ui;
};

#endif // FORGET_H
