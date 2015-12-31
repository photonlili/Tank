#include "qusersetmodel.h"
#include "qtankdefine.h"

QUserSetModel::QUserSetModel(QObject *parent, QSqlDatabase db) :
      QCSqlTableModel(parent, db)
{
}
