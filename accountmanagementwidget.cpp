#include "accountmanagementwidget.h"
#include "ui_accountmanagementwidget.h"
#include "accountmodel.h"
#include "administrator.h"
#include <QInputDialog>

AccountManagementWidget::AccountManagementWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountManagementWidget),
     model(new AccountModel(this)) // 初始化数据模型对象
{
    ui->setupUi(this);
   //ui-> tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    AccountManagementWidget::setupTableView();
     connectModelSignals();
}

AccountManagementWidget::~AccountManagementWidget()
{
    delete ui;
}


void AccountManagementWidget::setupTableView()
{
    // 创建 TableView
 // QTableView *tableView = new QTableView(this);
   // setCentralWidget(tableView);

    // 创建并设置模型
    //AccountModel *model = new AccountModel(this);
    ui->tableView->setModel(model);

    // 更新模型数据
    model->updateData(accounts);

    // 允许用户编辑单元格内容
   ui-> tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
}

void AccountManagementWidget::on_backButton_clicked()
{
    // 使用哈希表来检查是否存在相同的 card_ID
    QSet<int> cardIDs;
    bool duplicateCardID = false;
    for (const Account &acc : accounts) {
        if (cardIDs.contains(acc.card_ID)) {
            duplicateCardID = true;
            break;
        }
        cardIDs.insert(acc.card_ID);
    }

    if (duplicateCardID) {
        QMessageBox::warning(this, tr("card_ID重复"),
                             tr("数据库中发现相同的card_ID，请检查数据以保证每个card_ID仅出现一次"));
        return; // 不执行原本的逻辑
    }

    // 执行保存账户到文件的逻辑
    data::saveAccountsToFile();

    // 创建管理员窗口
    administrator *a = new administrator;
    // 隐藏当前窗口
    this->hide();
    // 显示管理员窗口
    a->show();
}

void AccountManagementWidget::onAccountDataChanged(const QList<Account> &newData)
{
    // 更新 accounts 数组
    accounts = newData;
    data::saveAccountsToFile();
}

void AccountManagementWidget::connectModelSignals()
{
    AccountModel *model = qobject_cast<AccountModel*>(ui->tableView->model());
    if (model)
    {
        connect(model, &AccountModel::accountDataChanged, this, &AccountManagementWidget::onAccountDataChanged);
    }
}

void AccountManagementWidget::on_delButton_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

    // 如果有选中的单元格
    if (!selectedIndexes.isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认删除",
                                      "你确认删除选中单元格对应的账户吗？",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // 获取选中单元格所在的行号
            QModelIndex index = selectedIndexes.first();
            // 从模型中获取对应行的数据
            int row = index.row();
            // 从模型中获取对应行的数据
            QModelIndex idIndex = model->index(row, 0); // 第一列是 card_ID
            int card_ID = model->data(idIndex).toInt();
            // 执行删除操作
            deleteAccount(card_ID);
        }
    } else {
        bool ok;
        int card_ID = QInputDialog::getInt(this, tr("请输入待删除的账户卡号"),
                                           tr("Card ID:"), 0, 0, INT_MAX, 1, &ok);
        if (ok) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "确认删除",
                                          "你确认删除以下卡号对应账户：" + QString::number(card_ID) + "?",
                                          QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                // 执行删除操作
                deleteAccount(card_ID);
            }
        }
    }
}


void AccountManagementWidget::on_addButton_clicked()
{
    bool ok;
    QString newUsername = QInputDialog::getText(this, tr("输入用户名"),
                                                tr("用户名:"), QLineEdit::Normal, "", &ok);
    if (!ok || newUsername.isEmpty()) {
        // 用户取消输入或者未输入用户名
        return;
    }

    QString phoneStr = QInputDialog::getText(this, tr("输入手机号"),
                                             tr("手机号:"), QLineEdit::Normal, "", &ok);
    if (!ok || phoneStr.isEmpty()) {
        // 用户取消输入或者未输入手机号
        return;
    }

    bool isAdministrator = QInputDialog::getInt(this, tr("是否为管理员"),
                                                tr("是否为管理员? (1 for Yes, 0 for No)"), 0, 0, 1, 1, &ok);
    if (!ok) {
        // 用户取消输入
        return;
    }

    // 调用数据类的函数完成新增用户
    data::addUser(newUsername, phoneStr, isAdministrator);
    AccountManagementWidget::setupTableView();

}


void AccountManagementWidget::deleteAccount(int card_ID)
{
    // 遍历账户列表，查找要删除的账户
    for (int i = 0; i < accounts.size(); ++i) {
        if (accounts[i].card_ID == card_ID) {
            // 找到要删除的账户，从列表中移除
            accounts.removeAt(i);
            // 在这里可以执行其他删除操作，例如更新数据库等
            AccountManagementWidget::setupTableView();
            data::saveAccountsToFile();
            // 退出循环
            return;
        }
    }

    // 如果未找到要删除的账户，显示一条提示信息
    QMessageBox::warning(this, "账户未找到", "以下卡号：" + QString::number(card_ID) + "对应账号不存在，删除失败");
}



void AccountManagementWidget::on_UnfreezeButton_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

    // 如果有选中的单元格
    if (!selectedIndexes.isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认清零登录失败次数",
                                      "你确认清零选中单元格对应的账户的登录失败次数吗？",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // 获取选中单元格所在的行号
            QModelIndex index = selectedIndexes.first();
            // 从模型中获取对应行的数据
            int row = index.row();
            // 从模型中获取对应行的数据
            QModelIndex idIndex = model->index(row, 0); // 第一列是 card_ID
            int card_ID = model->data(idIndex).toInt();
            // 执行清零操作
            UnfreezeAccount(card_ID);
        }
    } else {
        bool ok;
        int card_ID = QInputDialog::getInt(this, tr("请输入待清零的账户卡号"),
                                           tr("Card ID:"), 0, 0, INT_MAX, 1, &ok);
        if (ok) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "确认清零登录失败次数",
                                          "你确认清零以下卡号对应账户：" + QString::number(card_ID) + "的登录失败次数吗?",
                                          QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                // 执行清零操作
                UnfreezeAccount(card_ID);
            }
        }
    }
}

void AccountManagementWidget::UnfreezeAccount(int card_ID)
{
    // 遍历 accounts 数组
    for (int i = 0; i < accounts.size(); ++i)
    {
        // 找到与给定卡号匹配的账户
        if (accounts[i].matchCardID(card_ID))
        {
            // 将该账户的 login_failures 属性设置为零
            accounts[i].login_failures = 0;
            // 找到一个匹配就可以退出循环了
            AccountManagementWidget::setupTableView();
            data::saveAccountsToFile();
            return;
        }
    }
    // 如果未找到要清零的账户，显示一条提示信息
    QMessageBox::warning(this, "账户未找到", "以下卡号：" + QString::number(card_ID) + "对应账号不存在，登陆失败次数清零失败");

}
void AccountManagementWidget::on_freezeButton_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedIndexes();

    // 如果有选中的单元格
    if (!selectedIndexes.isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "确认冻结账户",
                                      "你确认冻结选中单元格对应的账户吗？",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            // 获取选中单元格所在的行号
            QModelIndex index = selectedIndexes.first();
            // 从模型中获取对应行的数据
            int row = index.row();
            // 从模型中获取对应行的数据
            QModelIndex idIndex = model->index(row, 0); // 第一列是 card_ID
            int card_ID = model->data(idIndex).toInt();
            // 执行清零操作
            freezeAccount(card_ID);
        }
    } else {
        bool ok;
        int card_ID = QInputDialog::getInt(this, tr("请输入要冻结的账户卡号"),
                                           tr("Card ID:"), 0, 0, INT_MAX, 1, &ok);
        if (ok) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "确认冻结账户卡号",
                                          "你确认冻结以下卡号对应账户：" + QString::number(card_ID) + "?",
                                          QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                // 执行清零操作
                freezeAccount(card_ID);
            }
        }
    }
}
void AccountManagementWidget::freezeAccount(int card_ID)
{
    // 遍历 accounts 数组
    for (int i = 0; i < accounts.size(); ++i)
    {
        // 找到与给定卡号匹配的账户
        if (accounts[i].matchCardID(card_ID))
        {
            // 将该账户的 login_failures 属性设置为零
            accounts[i].login_failures = 999;
            // 找到一个匹配就可以退出循环了
            AccountManagementWidget::setupTableView();
            data::saveAccountsToFile();
            return;
        }
    }
    // 如果未找到要清零的账户，显示一条提示信息
    QMessageBox::warning(this, "账户未找到", "以下卡号：" + QString::number(card_ID) + "对应账号不存在，冻结用户失败");

}







void AccountManagementWidget::PromotedAccount(int card_ID)
{
    // 遍历 accounts 数组
    for (int i = 0; i < accounts.size(); ++i)
    {
        // 找到与给定卡号匹配的账户
        if (accounts[i].matchCardID(card_ID))
        {
            // 将该账户的 isAdministrator 属性设置为1
            accounts[i].isAdministrator = 1;
            // 找到一个匹配就可以退出循环了
            AccountManagementWidget::setupTableView();
            data::saveAccountsToFile();
            return;
        }
    }
    // 如果未找到要清零的账户，显示一条提示信息
    QMessageBox::warning(this, "账户未找到", "以下卡号：" + QString::number(card_ID) + "对应账号不存在，提升用户失败");

}

