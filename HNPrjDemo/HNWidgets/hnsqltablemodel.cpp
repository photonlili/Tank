#include "hnsqltablemodel.h"

HNSqlTableModel::HNSqlTableModel(QObject *parent, QSqlDatabase db):
    QSqlRelationalTableModel(parent, db)
{
}

void HNSqlTableModel::refreshView(QString filter)
{
    setFilter(filter);
    select();
}

QVariant HNSqlTableModel::data(const QModelIndex &index, int role) const
{
    if( Qt::TextAlignmentRole == role )
        return Qt::AlignCenter;
    return QSqlTableModel::data(index, role);
}
