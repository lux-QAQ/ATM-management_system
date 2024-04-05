#include "accountmodel.h"
//#include "data.h"
#include <QDebug>
#include "login_with_lock.h"

AccountModel::AccountModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int AccountModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_accounts.size();
}

int AccountModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 7; // 有7个字段
}

QVariant AccountModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        const Account &account = m_accounts[index.row()];

        switch (index.column()) {
        case 0:
            return account.card_ID;
        case 1:
            return account.username;
        case 2:
            return account.passward;
        case 3:
            return account.money;
        case 4:
            return account.login_failures;
        case 5:
            return account.phone;
        case 6:
            return account.isAdministrator;
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QVariant AccountModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("卡号");
        case 1:
            return tr("用户名");
        case 2:
            return tr("密码");
        case 3:
            return tr("余额");
        case 4:
            return tr("登录失败次数");
        case 5:
            return tr("手机号");
        case 6:
            return tr("是否为管理员");
        default:
            return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags AccountModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

    if (index.isValid()) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

bool AccountModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    Account &account = m_accounts[index.row()];

    switch (index.column()) {
    case 0:
        account.card_ID = value.toInt();
        break;
    case 1:
        account.username = value.toString();
        break;
    case 2:
        account.passward = value.toString();
        break;
    case 3:
        account.money = value.toDouble();
        break;
    case 4:
        account.login_failures = value.toInt();
        break;
    case 5:
        account.phone = value.toString();
        break;
    case 6:
        account.isAdministrator = value.toInt();
        break;
    default:
        return false;
    }

    //emit dataChanged(index, index);
    emit layoutChanged();
    emit accountDataChanged(m_accounts);
    return true;
}

void AccountModel::updateData(const QList<Account> &newData)
{
    beginResetModel();
    m_accounts = newData;
    endResetModel();
}
