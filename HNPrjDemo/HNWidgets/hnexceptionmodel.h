#ifndef QEXCEPTIONMODEL_H
#define QEXCEPTIONMODEL_H

#include "hnsqltablemodel.h"

class HNExceptionModel : public HNSqlTableModel
{
    Q_OBJECT
public:
    explicit HNExceptionModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
signals:

public slots:

};

#endif // QEXCEPTIONMODEL_H
