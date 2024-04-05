#ifndef DATA_H
#define DATA_H

#include <QWidget>
#include <QFile>
#include <QApplication>
#include <QDebug>
#include <stdio.h>
#include <QDateTime>
#include <QTextStream>
#include <QStandardItemModel>
#include <QList>
#include <QRandomGenerator>




typedef struct statement
{
    int ID;
    int accountID;
    QString time;
    QString type;
    double money;
    int toAccunt;
    bool matchAccountID(int accountID) const {
        return this->accountID == accountID;
    }


} Statement;

typedef struct account
{
    int card_ID;
    QString username;
    QString passward;
    double money;
    int login_failures=0;
    QString phone;
    int isAdministrator=0;
    bool matchCardID(int cardID) const
    {
        return this->card_ID == cardID;
    }


} Account;
Q_DECLARE_METATYPE(Account)

extern int num_UI;
extern QList<Statement> statements;
extern QList<Account> accounts;
extern QStringList statement_data_headers ;
extern QList<QStringList> statement_data_rowData;
extern QStringList account_data_headers ;
extern QList<QStringList> account_data_rowData;
extern int accountID;
//extern int currentUser_index;


QT_BEGIN_NAMESPACE
namespace Ui { class data; }
QT_END_NAMESPACE

class data : public QWidget
{
    Q_OBJECT

public:
    static void backup_readDataFromFile(const QString backupPath);
    static void saveAccountsToFile();
    static void saveStatementsToFile();
    static void addUser(QString newUsername, QString newPhone,int new_isAdministrator);
    static void addStatement(int ID, int accountID, const QString &time, const QString &type, double money, int toAccount);
    static void statements_struct_initialization(const QStringList &headers, const QList<QStringList> &rowData);
    static void accounts_struct_initialization(const QStringList &headers, const QList<QStringList> &rowData);

    data(QWidget *parent = nullptr);
    ~data();
    //从指定的文件读取数据
    //void readDataFromFile(const QString& filename);
    void readDataFromFile();
    void tableView_styleset();
    // void setupTableModel(const QStringList &headers, const QList<QStringList> &rowData);







private:
    Ui::data *ui;
    QFile file;
};
#endif // DATA_H
