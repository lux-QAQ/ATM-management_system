#include "data.h"
#include "transaction_history.h"
#include "login_with_lock.h"
#include "widget.h"
#include "DynamicUnderlineLineEdit.h"

#include <QWidget>
#include <QRandomGenerator>

#include <QApplication>

//data w;







int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    data w;
    //w.show();

    //transaction_history t;
     //t.show();



    //随机UI
    num_UI = QRandomGenerator::global()->bounded(1, 4);
    QString num = ":/res/qss/style-" + QString::number(num_UI) + ".qss";

    QFile file(num);/*QSS文件所在的路径*/

    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    a.setStyleSheet(stylesheet);
    file.close();
    //随机UI




login_with_lock l;





    l.show();



    //saveAccountsToFile();
    //w.saveStatementsToFile();
    return a.exec();
}
