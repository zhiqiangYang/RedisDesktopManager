#pragma once
#include "abstractkey.h"

class SortedSetKeyModel : public KeyModel<QPair<QByteArray, double>>
{    
public:
    SortedSetKeyModel(QSharedPointer<RedisClient::Connection> connection,
                      QByteArray fullPath, int dbIndex, long long ttl);

    QString getType() override;
    QStringList getColumnNames() override;
    QHash<int, QByteArray> getRoles() override;
    QVariant getData(int rowIndex, int dataRole) override;

    void addRow(const QVariantMap&) override;
    virtual void updateRow(int rowIndex, const QVariantMap &) override;
    void removeRow(int) override;

protected:
    void addLoadedRowsToCache(const QVariantList& list, int rowStart) override;

private:
    enum Roles { Value = Qt::UserRole + 1, Score, RowNumber};

    bool addSortedSetRow(const QByteArray &value, double score);
    void deleteSortedSetRow(const QByteArray& value);
};
