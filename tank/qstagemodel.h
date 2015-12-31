#ifndef QSTAGEMODEL_H
#define QSTAGEMODEL_H

#include "qcsqltablemodel.h"

class QStageModel : public QCSqlTableModel
{
    Q_OBJECT
public:
    explicit QStageModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());

signals:

public slots:

private:
};

#endif // QSTAGEMODEL_H
