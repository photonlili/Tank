#ifndef QCSTANDARDITEMMODEL_H
#define QCSTANDARDITEMMODEL_H

#include <QStandardItemModel>

class QCStandardItemModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit QCStandardItemModel(QObject *parent = 0);

signals:

public slots:

};

#endif // QCSTANDARDITEMMODEL_H
