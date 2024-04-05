#ifndef ACCOUNTMANAGEMENTWIDGET_H
#define ACCOUNTMANAGEMENTWIDGET_H

#include <QWidget>
#include<qmessagebox.h>
#include "data.h"
#include "accountmodel.h"

namespace Ui {
class AccountManagementWidget;
}

class AccountManagementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AccountManagementWidget(QWidget *parent = nullptr);
    void setupTableView();
    void UnfreezeAccount(int card_ID);
    void freezeAccount(int card_ID);
    void PromotedAccount(int card_ID);
    ~AccountManagementWidget();

private slots:
    void on_backButton_clicked();
    void onAccountDataChanged(const QList<Account> &newData);


    void on_delButton_clicked();

    void on_addButton_clicked();

    void on_UnfreezeButton_clicked();

    //void on_UnfreezeButton_2_clicked();

    void on_freezeButton_clicked();





private:
     void connectModelSignals();
    void deleteAccount(int card_ID);
     AccountModel *model;
    Ui::AccountManagementWidget *ui;
};



#endif // ACCOUNTMANAGEMENTWIDGET_H
