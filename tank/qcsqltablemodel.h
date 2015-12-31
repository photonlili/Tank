#ifndef QFORMATSQLTABLEMODEL_H
#define QFORMATSQLTABLEMODEL_H

#include <QSqlRelationalTableModel>
#include "qheaders.h"

class QCSqlTableModel :  public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit QCSqlTableModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
    virtual void refreshView(QString filter);

signals:

public slots:

private:

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const;
};
#endif // QFORMATSQLTABLEMODEL_H
