#include "data.h"
#include "ui_data.h"
#include "login_with_lock.h"
#include "accountmodel.h"

int num_UI=1;
int accountID=-1;

QList<Statement> statements;
QList<Account> accounts;

QStringList statement_data_headers ;
QList<QStringList> statement_data_rowData;
QStringList account_data_headers ;
QList<QStringList> account_data_rowData;

data::data(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::data)
{
    ui->setupUi(this);



    readDataFromFile();
    //addStatement(999999, 6666666, "9996/1/6", "const QStrin", 55, 66);
   // accountID=-1;
   // setupTableModel(statement_data_headers, statement_data_rowData);

     //QString appDirPath = QCoreApplication::applicationDirPath();
     //QString filename = appDirPath + "/data.csv";
     // qDebug() << "Application directory path: " << filename;
    // readDataFromFile(filename);

}

data::~data()
{
    delete ui;
}

void data::readDataFromFile()
{

    /*以下是单笔流水信息的文件信息读取*/
    // 获取路径

    QString appDirPath = QCoreApplication::applicationDirPath();
    QString statement_data_filename = appDirPath + "/statement_data.csv";
    qDebug() << "Application directory path: " << statement_data_filename;

    // 检查并创建单笔流水信息文件
    QFile statement_data_file(statement_data_filename);
    if (!statement_data_file.exists()) {
        if (statement_data_file.open(QIODevice::WriteOnly| QIODevice::Text)) {
            qDebug() << "Created statement_data_File.";
            QTextStream stream(&statement_data_file);
            //stream.setCodec("GBK");
            QString str_temp = QStringLiteral("交易编号,发起交易卡号,交易时间,交易类型,交易数额,对方卡号\n");
                     stream << str_temp;
            statement_data_file.close();
        } else {
            qDebug() << "Failed to create statement_data_file.";
            return;
        }
    }

    // 打开文件
    if (statement_data_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "statement_data_File opened successfully.";
        QTextStream stream(&statement_data_file);

        // 读取文件的第一行作为表头
        statement_data_headers = stream.readLine().split(",");
       // QList<QStringList> statement_data_rowData;

        // 读取剩余的内容作为数据行
        while (!stream.atEnd()) {
            QStringList data = stream.readLine().split(",");
            statement_data_rowData.append(data);
        }

        // 关闭文件
        statement_data_file.close();

        // 调用新的函数设置数据模型和视图

        data::statements_struct_initialization(statement_data_headers, statement_data_rowData);
    }
    else
    {
        qDebug() << "Failed to open statement_data_file.";
        return;
    }
    /*以上是单笔流水信息的文件信息读取*/

    /**********************************************************************************/

    /*以下是卡号信息的文件信息读取*/


    QString account_data_filename = appDirPath + "/account_data.csv";
    qDebug() << "Application directory path: " << account_data_filename;

    // 检查并创建卡号信息文件
    QFile account_data_file(account_data_filename);
    if (!account_data_file.exists()) {
        if (account_data_file.open(QIODevice::WriteOnly| QIODevice::Text)) {
            qDebug() << "Created account_data_File.";
            QTextStream stream(&account_data_file);
            //stream.setCodec("GBK");
            QString str_temp = QStringLiteral("卡号,姓名,密码,账户余额,登陆失败次数,手机号, 是否为管理员\n");
                       stream << str_temp;
            account_data_file.close();
        } else {
            qDebug() << "Failed to create account_data_file.";
            return;
        }
    }

    // 打开文件
    if (account_data_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "account_data_File opened successfully.";
        QTextStream stream(&account_data_file);

        // 读取文件的第一行作为表头
       account_data_headers = stream.readLine().split(",");
       // QList<QStringList> account_data_rowData;
       //qDebug()  <<"1";
        // 读取剩余的内容作为数据行
        while (!stream.atEnd()) {
            QStringList data = stream.readLine().split(",");
            account_data_rowData.append(data);
            qDebug()  <<"读取";
        }
        //qDebug()  <<"2";
        // 关闭文件
        account_data_file.close();
        // 调用
        //qDebug()  <<"3";
        accounts_struct_initialization(account_data_headers, account_data_rowData);
        //qDebug()  <<"4";


    }
    else
    {
        qDebug() << "Failed to open account_data_file.";
        return;
    }
    /*以上是卡号信息的文件信息读取*/
}


void data::accounts_struct_initialization(const QStringList &headers, const QList<QStringList> &rowData)
{
    // 读取数据并添加到结构体对象中
    //qDebug()  <<"5";
    for (const QStringList &data : rowData) {
        Account account;
        account.card_ID = data[0].toInt();
        account.username = data[1];
        account.passward = data[2];
        account.money = data[3].toDouble();
        account.login_failures = data[4].toInt();
        account.phone = data[5];
        account.isAdministrator = data[6].toInt();
       //qDebug()  <<"account";
        accounts.append(account);
    }

    // 现在，accounts 中包含了从文件中读取的数据，每个元素都是一个结构体对象，可以按照结构体的格式使用这些数据了。
    for (const Account &account : accounts) {
        qDebug() << "Card ID: " << account.card_ID;
        qDebug() << "Username: " << account.username;
        qDebug() << "Password: " << account.passward;
        qDebug() << "Money: " << account.money;
        qDebug() << "login_failures: " << account.login_failures;
        qDebug() << "phone: " << account.phone;
        qDebug() << "isAdministrator: " << account.isAdministrator;
        qDebug() << "---------------------";
    }
    // ...接下来可以根据需要对这些数据进行处理或者展示
}


void data::statements_struct_initialization(const QStringList &headers, const QList<QStringList> &rowData)
{


    // 读取数据并添加到结构体对象中
    for (const QStringList &data : rowData) {
        Statement statement;
        statement.ID = data[0].toInt();
        statement.accountID = data[1].toInt();
        statement.time = data[2];
        statement.type = data[3];
        statement.money = data[4].toDouble();
        statement.toAccunt = data[5].toInt();

        statements.append(statement);
    }

    // 现在，statements 中包含了从文件中读取的数据，每个元素都是一个结构体对象，可以按照结构体的格式使用这些数据了。
    for (const Statement &statement : statements) {
      //  qDebug() << "Statement ID: " << statement.ID;
       // qDebug() << "Account ID: " << statement.accountID;
      //  qDebug() << "Time: " << statement.time.toString("yyyy-MM-dd hh:mm:ss");
      //  qDebug() << "Type: " << statement.type;
       // qDebug() << "Money: " << statement.money;
      //  qDebug() << "To Account: " << statement.toAccunt;
       // qDebug() << "---------------------";
    }
    // ...接下来可以根据需要对这些数据进行处理或者展示
}




void data::saveAccountsToFile()
{
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString account_data_filename = appDirPath + "/account_data.csv";

    QFile account_data_file(account_data_filename);
    account_data_file.open(QFile::WriteOnly|QFile::Truncate);
        account_data_file.close();

    if (account_data_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&account_data_file);
        //stream.setCodec("UTF-8");

        // 检查是否存在表头
       QString firstLine = stream.readLine();
        bool hasHeader = (firstLine.trimmed() == "卡号,姓名,密码,账户余额,登陆失败次数,手机号,是否为管理员");

        // 如果没有表头，则添加表头
       if (!hasHeader) {
            QTextStream stream(&account_data_file);
            //stream.setCodec("GBK");
            QString str_temp = QStringLiteral("卡号,姓名,密码,账户余额,登陆失败次数,手机号,是否为管理员\n");
                       stream << str_temp;
    }

        // 写入数据行
        for (const Account &account : accounts) {
            stream << QString::number(account.card_ID) << ","
                   << account.username << ","
                   << account.passward << ","
                   << QString::number(account.money) << ","
                   << QString::number(account.login_failures) << ","
                   << account.phone << ","
                   << QString::number(account.isAdministrator) << "\n";
        }

        account_data_file.close();
        qDebug() << "Account data saved to file: " << account_data_filename;
    } else {
        qDebug() << "Failed to save account data to file.";
    }
}

void data::saveStatementsToFile()
{
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString statement_data_filename = appDirPath + "/statement_data.csv";

    QFile statement_data_file(statement_data_filename);
    statement_data_file.open(QFile::WriteOnly|QFile::Truncate);
        statement_data_file.close();
    if (statement_data_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&statement_data_file);
        //stream.setCodec("UTF-8");

        // 检查是否存在表头
        QString firstLine = stream.readLine();
        bool hasHeader = (firstLine.trimmed() == "交易编号,发起交易卡号,交易时间,交易类型,交易数额,对方卡号");

        // 如果没有表头，则添加表头
        if (!hasHeader) {
            QTextStream stream(&statement_data_file);
            //stream.setCodec("GBK");
            QString str_temp = QStringLiteral("交易编号,发起交易卡号,交易时间,交易类型,交易数额,对方卡号\n");
                     stream << str_temp;
        }

        // 写入数据行
        for (const Statement &statement : statements) {
            if (!statement.time.isNull()) {
                stream << QString::number(statement.ID) << ","
                       << QString::number(statement.accountID) << ","
                       << statement.time << ","
                       << statement.type << ","
                       << QString::number(statement.money) << ","
                       << QString::number(statement.toAccunt) << "\n";
            } else {
                qDebug() << "Invalid time value for statement: " << statement.ID;
            }
        }


        statement_data_file.close();
        qDebug() << "Statement data saved to file: " << statement_data_filename;
    } else {
        qDebug() << "Failed to save statement data to file.";
    }
}

//void data::setupTableModel(const QStringList &headers, const QList<QStringList> &rowData)
//{
    //int columnCount = headers.size();

    // 创建一个数据模型
    //QStandardItemModel *model = new QStandardItemModel(0, columnCount, this);

    // 将表头设置到数据模型中
    //model->setHorizontalHeaderLabels(headers);

    // 读取数据并添加到数据模型中
   // for (const QStringList &data : rowData) {
  //      QList<QStandardItem *> rowItems;
   //     for (const QString &value : data) {
    //        rowItems.append(new QStandardItem(value));
   //     }
  //      model->appendRow(rowItems);
  //  }

    // 将数据模型与视图关联
  //  ui->tableView->setModel(model);
  //  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   // ui->tableView->horizontalHeader()->setStretchLastSection(true);
  //  ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  //  ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
  //  ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->tableView->horizontalHeader()->setStretchLastSection(true);
//}

void data::addStatement(int ID, int accountID, const QString &time, const QString &type, double money, int toAccount)
{
    // 创建一个新的 Statement 结构体对象
    Statement newStatement;
    newStatement.ID = ID;
    newStatement.accountID = accountID;
    newStatement.time = time;
    newStatement.type = type;
    newStatement.money = money;
    newStatement.toAccunt = toAccount;

    // 将新的结构体对象添加到 statements 数组中
    statements.append(newStatement);
    saveStatementsToFile();
    saveAccountsToFile();
}

void data::addUser(QString newUsername, QString newPhone,int new_isAdministrator)
{



    Account newAccount;

    // 生成随机的6位数作为 card_ID
    newAccount.card_ID = QRandomGenerator::global()->bounded(100000, 999999);

    newAccount.username = newUsername;
    newAccount.passward = "123456";
    newAccount.money = 0.0;
    newAccount.login_failures = 0;
    newAccount.phone = newPhone;
    newAccount.isAdministrator = new_isAdministrator;

    accounts.append(newAccount);
    data::saveAccountsToFile();
}



void data::backup_readDataFromFile(const QString backupPath)
{

    //清空原有数据
    statements.clear();
    accounts.clear();
    /*以下是单笔流水信息的文件信息读取*/
    // 获取路径

    QString appDirPath = backupPath;
    QString statement_data_filename = appDirPath + "/statement_data.csv.bak";
    qDebug() << "Application directory path: " << statement_data_filename;

    // 检查并创建单笔流水信息文件
    QFile statement_data_file(statement_data_filename);
    if (!statement_data_file.exists()) {
        if (statement_data_file.open(QIODevice::WriteOnly| QIODevice::Text)) {
            qDebug() << "Created statement_data_File.";
            QTextStream stream(&statement_data_file);
            //stream.setCodec("GBK");
            QString str_temp = QStringLiteral("交易编号,发起交易卡号,交易时间,交易类型,交易数额,对方卡号\n");
            stream << str_temp;
            statement_data_file.close();
        } else {
            qDebug() << "Failed to create statement_data_file.";
            return;
        }
    }

    // 打开文件
    if (statement_data_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "statement_data_File opened successfully.";
        QTextStream stream(&statement_data_file);

        // 读取文件的第一行作为表头
        QStringList statement_data_headers ;
        statement_data_headers = stream.readLine().split(",");
        // QList<QStringList> statement_data_rowData;
        QList<QStringList> statement_data_rowData;

        // 读取剩余的内容作为数据行
        while (!stream.atEnd()) {
            QStringList data = stream.readLine().split(",");
            statement_data_rowData.append(data);
        }

        // 关闭文件
        statement_data_file.close();

        // 调用新的函数设置数据模型和视图

        data::statements_struct_initialization(statement_data_headers, statement_data_rowData);
    }
    else
    {
        qDebug() << "Failed to open statement_data_file.";
        return;
    }
    /*以上是单笔流水信息的文件信息读取*/

    /**********************************************************************************/

    /*以下是卡号信息的文件信息读取*/


    QString account_data_filename = appDirPath + "/account_data.csv.bak";
    qDebug() << "Application directory path: " << account_data_filename;

    // 检查并创建卡号信息文件
    QFile account_data_file(account_data_filename);
    if (!account_data_file.exists()) {
        if (account_data_file.open(QIODevice::WriteOnly| QIODevice::Text)) {
            qDebug() << "Created account_data_File.";
            QTextStream stream(&account_data_file);
            //stream.setCodec("GBK");
            QString str_temp = QStringLiteral("卡号,姓名,密码,账户余额,登陆失败次数,手机号,是否为管理员\n");
            stream << str_temp;
            account_data_file.close();
        } else {
            qDebug() << "Failed to create account_data_file.";
            return;
        }
    }

    // 打开文件
    if (account_data_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "account_data_File opened successfully.";
        QTextStream stream(&account_data_file);

        // 读取文件的第一行作为表头
        QStringList account_data_headers ;
        account_data_headers = stream.readLine().split(",");
        // QList<QStringList> account_data_rowData;
        QList<QStringList> account_data_rowData;

        // 读取剩余的内容作为数据行
        while (!stream.atEnd()) {
            QStringList data = stream.readLine().split(",");
            account_data_rowData.append(data);
        }

        // 关闭文件
        account_data_file.close();
        // 调用
        data::accounts_struct_initialization(account_data_headers, account_data_rowData);


    }
    else
    {
        qDebug() << "Failed to open account_data_file.";
        return;
    }
    /*以上是卡号信息的文件信息读取*/
}










