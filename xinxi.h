#ifndef XINXI_H
#define XINXI_H

#include <QWidget>

#include "widget.h"
#include "ui_widget.h"

namespace Ui {
class xinxi;
}

class xinxi : public QWidget
{
    Q_OBJECT

public:
    explicit xinxi(QWidget *parent = nullptr);
    ~xinxi();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_forecastButton_clicked();

private:
    Ui::xinxi *ui;
};

#endif // XINXI_H
