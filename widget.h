#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    Ui::Widget *ui;
    void comein();

    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_ExitButton_clicked();




private:

};
#endif // WIDGET_H
