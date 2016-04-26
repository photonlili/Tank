#include "hnsamplemodel.h"

HNSampleModel::HNSampleModel(QObject *parent, QSqlDatabase db) :
    HNSqlTableModel(parent, db)
{
}
