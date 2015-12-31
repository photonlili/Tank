#ifndef QUSERLIBRARYMODEL_H
#define QUSERLIBRARYMODEL_H

#include "qcsqltablemodel.h"

class QUserLibraryModel : public QCSqlTableModel
{
    Q_OBJECT
public:
    explicit QUserLibraryModel(QObject *parent = 0, QSqlDatabase db = QSqlDatabase());

signals:

public slots:

};

#endif // QUSERLIBRARYMODEL_H
