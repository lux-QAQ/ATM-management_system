#ifndef LOGIN_WITH_LOCK_H
#define LOGIN_WITH_LOCK_H

#include <QWidget>
#include <QProcess>
#include<QMessageBox>
#include<QApplication>
#include<QString>
#include <QLineEdit>
#include <QMessageBox>
#include "administrator.h"





QT_BEGIN_NAMESPACE
namespace Ui { class login_with_lock; }
QT_END_NAMESPACE

class login_with_lock : public QWidget
{
    Q_OBJECT

public:
    login_with_lock(QWidget *parent = nullptr);
    ~login_with_lock();
    static  int findStatementIndexByAccountID(int accountID);
    static int findAccountIndexByCardID(int cardID);
    static bool password_check();
    //extern Widget *main_menu;
   // Widget *main_menu=new Widget;

private slots:
   // void on_loginButton_clicked();

    void on_radioButton_clicked();



   // void on_card_IDLineEdit_textEdited(const QString &arg1);

  //  void on_LineE_pwd_textEdited(const QString &arg1);

    void on_btn_login_clicked();

    //void on_LineE_username_textEdited(const QString &arg1);

    void on_lineE_user_name_textEdited(const QString &arg1);

    //void on_btn_1_clicked();

  // void on_btn_2_clicked();

   // void on_btn_3_clicked();

   // void on_btn_4_clicked();

   // void on_btn_1_clicked();

    //void on_btn_2_clicked();

    //void on_btn_3_clicked();

    //void on_btn_4_clicked();

    void on_btn_forget_clicked();

private:
    Ui::login_with_lock *ui;
    int wrongPasswordCount;
    const int maxAttempts = 3;
};

#endif // LOGIN_WITH_LOCK_H
