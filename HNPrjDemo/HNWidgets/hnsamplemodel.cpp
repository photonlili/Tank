#include "hnsamplemodel.h"
#include "HNDefine.h"


HNSampleModel::HNSampleModel(QObject *parent, QSqlDatabase db) :
    HNSqlTableModel(parent, db)
{
}


QVariant HNSampleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(role)
    {
    //case Qt::TextAlignmentRole:
    //              return Qt::AlignLeft | Qt::AlignVCenter;

    case Qt::DisplayRole:
        return HNSqlTableModel::data(index, role);

    case Qt::CheckStateRole:
        if(index.column() == 0)
        {
            if (check_state_map.contains(index.row()))
                return check_state_map[index.row()] == Qt::Checked ? Qt::Checked : Qt::Unchecked;

            return Qt::Unchecked;
        }
        break;
    default:
        break;
    }

    return HNSqlTableModel::data(index, role);
}

bool HNSampleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
        return false;

    if (role == Qt::CheckStateRole && index.column() == 0)
    {
        check_state_map[index.row()] = (value == Qt::Checked ? Qt::Checked : Qt::Unchecked);
    }

    return true;
}

Qt::ItemFlags HNSampleModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    if (index.column() == 0)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
