#ifndef QEXCEPTIONMODEL_H
#define QEXCEPTIONMODEL_H

#include "qcsqltablemodel.h"

class QExceptionModel : public QCSqlTableModel
{
    Q_OBJECT
public:
    explicit QExceptionModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());
signals:

public slots:

};

#endif // QEXCEPTIONMODEL_H
