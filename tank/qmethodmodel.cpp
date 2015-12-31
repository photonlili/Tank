#include "qmethodmodel.h"

QMethodModel::QMethodModel(QObject *parent, QSqlDatabase db) :
    QCSqlTableModel(parent, db)
{
}
