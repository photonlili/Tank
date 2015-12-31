#ifndef QTANKDATABASE_H
#define QTANKDATABASE_H

#include <QSqlDatabase>

class QTankDatabase : public QSqlDatabase
{
public:
    QTankDatabase() : QSqlDatabase() {}
    QTankDatabase(const QSqlDatabase &other) : QSqlDatabase(other) {}
    ~QTankDatabase() {}

};

#endif // QTANKDATABASE_H
