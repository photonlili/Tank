#ifndef QCLOUDLOCALMODEL_H
#define QCLOUDLOCALMODEL_H

#include "qcstandarditemmodel.h"
#include "qtankclient.h"

class QCloudLocalModel : public QCStandardItemModel
{
    Q_OBJECT
public:
    explicit QCloudLocalModel(QObject *parent = 0);

    void queryRootDirs();
    void queryFiles(QString code);
    void uploadFile(QString code, QString path, QString filename, int len);

protected:
    QStandardItem *findDirByCode(QString code);

signals:
    void sigQueryRootDirSuccess();
    void sigUploadSuccess();
public slots:
private:
    QTankClient* m_client;
};

#endif // QCLOUDLOCALMODEL_H
