#ifndef TRANSACTION_HISTORY_H
#define TRANSACTION_HISTORY_H

#include <QWidget>
#include <QFileDialog>
#include <QTextStream>





namespace Ui {
class transaction_history;
}



class transaction_history : public QWidget
{
    Q_OBJECT
//signals:
   // void searchTextChanged(const QString &text, bool choice1, bool choice2, bool choice3);



public:
    explicit transaction_history(QWidget *parent = nullptr);
    ~transaction_history();

   // void setupTableModel(const QStringList &headers, const QList<QStringList> &rowData);
    void setupTableModel(const QStringList &headers);

private slots:
    void on_fuzzylineEdit_textEdited(const QString &arg1);
    void initializeTableView();

    void on_backButton_clicked();
   // void searchTransactions(const QString &arg1, bool choice1, bool choice2, bool choice3);

   // void on_radioButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();
    void on_headerClicked(int logicalIndex);

    void on_checkBox_ID_clicked();

    void on_checkBox_accountID_clicked();

    void on_checkBox_time_clicked();

    void on_checkBox_type_clicked();

    void on_checkBox_money_clicked();

    void on_checkBox_toAccount_clicked();

    void on_saveButton_clicked();

private:
    Ui::transaction_history *ui;
};

#endif // TRANSACTION_HISTORY_H
