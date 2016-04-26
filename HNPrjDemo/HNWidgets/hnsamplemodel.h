#ifndef HNSAMPLEMODEL_H
#define HNSAMPLEMODEL_H

#include "hnsqltablemodel.h"

class HNSampleModel : public HNSqlTableModel
{
    Q_OBJECT
public:
    explicit HNSampleModel(QObject *parent, QSqlDatabase db);

signals:

public slots:

};

#endif // HNSAMPLEMODEL_H
