#ifndef QUSERSETMODEL_H
#define QUSERSETMODEL_H

#include "qcsqltablemodel.h"

class QUserSetModel : public QCSqlTableModel
{
    Q_OBJECT
public:
    explicit QUserSetModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());

signals:

public slots:

};

#endif // QUSERSETMODEL_H
