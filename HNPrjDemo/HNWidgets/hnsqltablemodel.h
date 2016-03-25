#ifndef QFORMATSQLTABLEMODEL_H
#define QFORMATSQLTABLEMODEL_H

#include <QSqlRelationalTableModel>

class HNSqlTableModel :  public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit HNSqlTableModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
    virtual void refreshView(QString filter);

signals:

public slots:

private:

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &index, int role) const;
};
#endif // QFORMATSQLTABLEMODEL_H
