#ifndef HNSAMPLEMODEL_H
#define HNSAMPLEMODEL_H

#include "hnsqltablemodel.h"
#include <QMap>
#include <QStringList>
#include <QVector>

class HNSampleModel : public HNSqlTableModel
{
    Q_OBJECT
public:
    explicit HNSampleModel(QObject *parent, QSqlDatabase db);

signals:

public slots:


    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QMap<int, Qt::CheckState> check_state_map;
    QVector<QStringList> m_data;
};

#endif // HNSAMPLEMODEL_H
