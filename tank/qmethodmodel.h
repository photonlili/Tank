#ifndef QMETHODMODEL_H
#define QMETHODMODEL_H

#include "qcsqltablemodel.h"

class QMethodModel : public QCSqlTableModel
{
    Q_OBJECT
public:
    explicit QMethodModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());

signals:

public slots:

private:
};

#endif // QMETHODMODEL_H
