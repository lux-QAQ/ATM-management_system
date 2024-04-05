#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H


#include <QAbstractTableModel>
#include "data.h"
class AccountModel : public QAbstractTableModel
{
    Q_OBJECT  // 在这里添加 Q_OBJECT 宏
signals:
    void accountDataChanged(const QList<Account> &newData);
public:
    AccountModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void updateData(const QList<Account> &newData);

private:
    QList<Account> m_accounts;
};

#endif // ACCOUNTMODEL_H
