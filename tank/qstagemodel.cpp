#include "qstagemodel.h"

QStageModel::QStageModel(QObject *parent, QSqlDatabase db) :
    QCSqlTableModel(parent, db)
{
}
