#include "quserlibrarymodel.h"

QUserLibraryModel::QUserLibraryModel(QObject *parent, QSqlDatabase db) :
    QCSqlTableModel(parent, db)
{
}
