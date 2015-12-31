#include "qexceptionmodel.h"

QExceptionModel::QExceptionModel(QObject *parent, QSqlDatabase db) :
    QCSqlTableModel(parent, db)
{

}
