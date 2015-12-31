#include "qcsqltablemodel.h"

QCSqlTableModel::QCSqlTableModel(QObject *parent, QSqlDatabase db):
    QSqlRelationalTableModel(parent, db)
{
}

void QCSqlTableModel::refreshView(QString filter)
{
    setFilter(filter);
    select();
}

QVariant QCSqlTableModel::data(const QModelIndex &index, int role) const
{
    if( Qt::TextAlignmentRole == role )
        return Qt::AlignCenter;
    return QSqlTableModel::data(index, role);
}
