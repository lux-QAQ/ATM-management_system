    #include "transaction_history.h"
    #include "ui_transaction_history.h"
    #include "data.h"
    #include <qdebug.h>
    #include "xinxi.h"


    //int accountID=123456;


    transaction_history::transaction_history(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::transaction_history)
    {
        ui->setupUi(this);

        ui->tableView->setSortingEnabled(true);
        ui->tableView->horizontalHeader()->logicalIndex(0);
        initializeTableView();

        //qDebug() << accountID << "debug_his";
       // setupTableModel(statement_data_headers, 123456);

    }

    transaction_history::~transaction_history()
    {
        delete ui;
    }


    void transaction_history::setupTableModel(const QStringList &headers)
    {
        int columnCount = headers.size();

        // 创建一个数据模型
        QStandardItemModel *model = new QStandardItemModel(0, columnCount, this);

        // 将表头设置到数据模型中
        model->setHorizontalHeaderLabels(headers);

        // 读取数据并添加到数据模型中
        for (const Statement &stmt : statements)
        {
            if (stmt.matchAccountID(accountID))
            {
                QList<QStandardItem *> rowItems;
                rowItems.append(new QStandardItem(QString::number(stmt.ID)));
                rowItems.append(new QStandardItem(QString::number(stmt.accountID)));
                rowItems.append(new QStandardItem(stmt.time));
                rowItems.append(new QStandardItem(stmt.type));
                rowItems.append(new QStandardItem(QString::number(stmt.money)));
                rowItems.append(new QStandardItem(QString::number(stmt.toAccunt)));

                model->appendRow(rowItems);
            }
        }

        // 将数据模型与视图关联
        //ui->tableView->setModel(model);
       // ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //ui->tableView->horizontalHeader()->setStretchLastSection(true);
       // ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }

    void transaction_history::on_fuzzylineEdit_textEdited(const QString &arg1)
    {
        // 清空表格视图
        ui->tableView->setModel(nullptr);
        bool choice1 = ui->radioButton->isChecked();
        bool choice2 = ui->radioButton_2->isChecked();
        bool choice3 = ui->radioButton_3->isChecked();

        if(choice1)
        {
            // 清空表格视图
            //connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(on_headerClicked(int)));
            ui->tableView->setModel(nullptr);

            // 创建一个哈希表来存储已经添加过的交易编号，避免重复添加数据
            QSet<int> addedTransactions;

            // 创建一个数据模型
            QStandardItemModel *model = new QStandardItemModel(0, 6, this); // 假设有6列数据

            // 将表头设置到数据模型中
            QStringList headers = {"交易编号", "发起交易卡号", "交易时间", "交易类型", "交易数额", "对方卡号"};
            model->setHorizontalHeaderLabels(headers);

            // 读取数据并添加到数据模型中
            for (const Statement &stmt : statements)
            {
                if (arg1.isEmpty() ||
                    (ui->checkBox_ID->isChecked() && QString::number(stmt.ID).contains(arg1, Qt::CaseInsensitive)) ||
                    (ui->checkBox_accountID->isChecked() && QString::number(stmt.accountID).contains(arg1, Qt::CaseInsensitive)) ||
                    (ui->checkBox_time->isChecked() && stmt.time.contains(arg1, Qt::CaseInsensitive)) ||
                    (ui->checkBox_type->isChecked() && stmt.type.contains(arg1, Qt::CaseInsensitive)) ||
                    (ui->checkBox_money->isChecked() && QString::number(stmt.money).contains(arg1, Qt::CaseInsensitive)) ||
                    (ui->checkBox_toAccount->isChecked() && QString::number(stmt.toAccunt).contains(arg1, Qt::CaseInsensitive)))
                {
                    if (accountID == -1 || stmt.accountID == accountID || stmt.toAccunt == accountID)
                    {
                        // 检查交易编号是否已经添加过，如果没有则添加到数据模型中
                        if (!addedTransactions.contains(stmt.ID))
                        {
                            QList<QStandardItem *> rowItems;
                            rowItems.append(new QStandardItem(QString::number(stmt.ID)));
                            rowItems.append(new QStandardItem(QString::number(stmt.accountID)));
                            rowItems.append(new QStandardItem(stmt.time));
                            rowItems.append(new QStandardItem(stmt.type));
                            rowItems.append(new QStandardItem(QString::number(stmt.money)));
                            rowItems.append(new QStandardItem(QString::number(stmt.toAccunt)));

                            model->appendRow(rowItems);
                            addedTransactions.insert(stmt.ID); // 将交易编号添加到哈希表中
                        }
                    }
                }
            }

            // 将数据模型与视图关联
            ui->tableView->setModel(model);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableView->horizontalHeader()->setStretchLastSection(true);
            ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        else if(choice2)
        {
            // 创建一个数据模型
            QStandardItemModel *model = new QStandardItemModel(0, 6, this); // 假设有6列数据

            // 创建一个哈希表来存储已经添加过的交易编号，避免重复添加数据
            QSet<int> addedTransactions;

            // 将表头设置到数据模型中
            QStringList headers = {"交易编号", "发起交易卡号", "交易时间", "交易类型", "交易数额", "对方卡号"};
            model->setHorizontalHeaderLabels(headers);

            // 读取数据并添加到数据模型中
            for (const Statement &stmt : statements)
            {
                if (arg1.isEmpty() ||
                    (ui->checkBox_ID->isChecked()&& QString::number(stmt.ID) == arg1) ||
                    (ui->checkBox_accountID->isChecked() && QString::number(stmt.accountID) == arg1) ||
                    (ui->checkBox_time->isChecked() &&stmt.time == arg1 )||
                    (ui->checkBox_type->isChecked() && stmt.type == arg1) ||
                    (ui->checkBox_money->isChecked() &&QString::number(stmt.money) == arg1) ||
                    (ui->checkBox_toAccount->isChecked() && QString::number(stmt.toAccunt) == arg1))
                {
                    if (!addedTransactions.contains(stmt.ID))
                    {
                        QList<QStandardItem *> rowItems;
                        rowItems.append(new QStandardItem(QString::number(stmt.ID)));
                        rowItems.append(new QStandardItem(QString::number(stmt.accountID)));
                        rowItems.append(new QStandardItem(stmt.time));
                        rowItems.append(new QStandardItem(stmt.type));
                        rowItems.append(new QStandardItem(QString::number(stmt.money)));
                        rowItems.append(new QStandardItem(QString::number(stmt.toAccunt)));

                        model->appendRow(rowItems);
                        addedTransactions.insert(stmt.ID); // 将交易编号添加到哈希表中
                    }
                }
            }

            // 将数据模型与视图关联
            ui->tableView->setModel(model);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableView->horizontalHeader()->setStretchLastSection(true);
            ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        else if(choice3)
        {
            QStandardItemModel *model = new QStandardItemModel(0, 6, this); // 假设有6列数据

            QSet<int> addedTransactions;


            // 将表头设置到数据模型中
            QStringList headers = {"交易编号", "发起交易卡号", "交易时间", "交易类型", "交易数额", "对方卡号"};
            model->setHorizontalHeaderLabels(headers);

            // 构建正则表达式
            QRegExp regex(arg1, Qt::CaseInsensitive);

            // 读取数据并添加到数据模型中
            for (const Statement &stmt : statements)
            {
                if (arg1.isEmpty() ||
                    (ui->checkBox_ID->isChecked() && QString::number(stmt.ID).contains(regex)) ||
                    (ui->checkBox_accountID->isChecked() && QString::number(stmt.accountID).contains(regex)) ||
                    (ui->checkBox_time->isChecked() && stmt.time.contains(regex)) ||
                    (ui->checkBox_type->isChecked() && stmt.type.contains(regex)) ||
                    (ui->checkBox_money->isChecked() && QString::number(stmt.money).contains(regex)) ||
                    (ui->checkBox_toAccount->isChecked() && QString::number(stmt.toAccunt).contains(regex)))
                {
                    if (!addedTransactions.contains(stmt.ID))
                    {
                        QList<QStandardItem *> rowItems;
                        rowItems.append(new QStandardItem(QString::number(stmt.ID)));
                        rowItems.append(new QStandardItem(QString::number(stmt.accountID)));
                        rowItems.append(new QStandardItem(stmt.time));
                        rowItems.append(new QStandardItem(stmt.type));
                        rowItems.append(new QStandardItem(QString::number(stmt.money)));
                        rowItems.append(new QStandardItem(QString::number(stmt.toAccunt)));

                        model->appendRow(rowItems);
                        addedTransactions.insert(stmt.ID); // 将交易编号添加到哈希表中
                    }
                }
            }

            // 将数据模型与视图关联
            ui->tableView->setModel(model);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableView->horizontalHeader()->setStretchLastSection(true);
            ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
    }



    void transaction_history::initializeTableView()
    {
        //int accountID = -1; // 显示所有数据
        on_fuzzylineEdit_textEdited("");

    }

    void transaction_history::on_backButton_clicked()
    {
        this->hide();
        xinxi *x=new xinxi;
        x->show();
    }





    void transaction_history::on_radioButton_clicked()
    {
         transaction_history::on_fuzzylineEdit_textEdited(ui->fuzzylineEdit->text());

    }


    void transaction_history::on_radioButton_2_clicked()
    {
        transaction_history::on_fuzzylineEdit_textEdited(ui->fuzzylineEdit->text());

    }



    void transaction_history::on_radioButton_3_clicked()
    {
        transaction_history::on_fuzzylineEdit_textEdited(ui->fuzzylineEdit->text());
    }

    void transaction_history::on_headerClicked(int logicalIndex)
    {
        QStandardItemModel *model = qobject_cast<QStandardItemModel*>(ui->tableView->model());
        if (model)
        {
            model->sort(logicalIndex, Qt::  AscendingOrder);
            ui->tableView->setModel(nullptr);
            ui->tableView->setModel(model);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->tableView->horizontalHeader()->setStretchLastSection(true);
            ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
    }

void transaction_history::on_checkBox_ID_clicked()
{
    transaction_history::on_fuzzylineEdit_textEdited(ui->fuzzylineEdit->text());
}


void transaction_history::on_checkBox_accountID_clicked()
{
    transaction_history::on_fuzzylineEdit_textEdited(ui->fuzzylineEdit->text());
}


void transaction_history::on_checkBox_time_clicked()
{
    transaction_history::on_fuzzylineEdit_textEdited(ui->fuzzylineEdit->text());
}


void transaction_history::on_checkBox_type_clicked()
{
    transaction_history::on_fuzzylineEdit_textEdited(ui->fuzzylineEdit->text());
}



void transaction_history::on_checkBox_money_clicked()
{
    transaction_history::on_fuzzylineEdit_textEdited(ui->fuzzylineEdit->text());
}



void transaction_history::on_checkBox_toAccount_clicked()
{
    transaction_history::on_fuzzylineEdit_textEdited(ui->fuzzylineEdit->text());
}




void transaction_history::on_saveButton_clicked()
{
    // 获取用户自定义的保存路径
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), "历史交易记录", tr("CSV Files (*.csv)"));

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);

            // 写入表头
            QStringList headerData;
            for (int col = 0; col < ui->tableView->model()->columnCount(); ++col) {
                headerData << ui->tableView->model()->headerData(col, Qt::Horizontal).toString();
            }
            stream << headerData.join(",") << "\n";

            // 写入数据
            for (int row = 0; row < ui->tableView->model()->rowCount(); ++row) {
                QStringList rowData;
                for (int col = 0; col < ui->tableView->model()->columnCount(); ++col) {
                    QModelIndex index = ui->tableView->model()->index(row, col);
                    rowData << ui->tableView->model()->data(index, Qt::DisplayRole).toString();
                }
                stream << rowData.join(",") << "\n";
            }

            file.close();
            qDebug() << "CSV file saved to: " << filePath;
        } else {
            qDebug() << "Failed to open file for writing: " << filePath;
        }
    } else {
        qDebug() << "No file selected for saving.";
    }
}


