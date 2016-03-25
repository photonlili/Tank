#include "hncloudmodel.h"
#include "HNDefine.h"
#include "qdir.h"
#include "qfileinfo.h"

HNCloudModel::HNCloudModel(QObject *parent, QTankClient *clientHandle) :
    HNStandardItemModel(parent), m_client(clientHandle)
{
    setColumnCount(FILE_MAX);
    connect(m_client, SIGNAL(signalListDirOK()), this, SLOT(queryRootDirsResult()));
    connect(m_client, SIGNAL(signalListFileOK()), this, SLOT(queryFilesResult()));
    connect(m_client, SIGNAL(signalLogined()), this, SLOT(queryRootDirs()));
    connect(m_client, SIGNAL(signalUploadSucc(QString)), this, SLOT(queryFiles(QString)));
    connect(m_client, SIGNAL(signalDownSucc()), this, SIGNAL(sigDownSuccess()));
}

void HNCloudModel::queryRootDirs()
{
    m_client->sendListDirectory();
}

void HNCloudModel::queryFiles(QString code)
{
    m_client->sendListFiles(code);
}

void HNCloudModel::downFile(QString path, QString id, QString localname)
{
    m_client->sendDownDevFiles(path, id, localname);
}

void HNCloudModel::delFile(QString code, QString id)
{
    m_client->sendDelFile(code, id);
}

void HNCloudModel::queryRootDirsResult()
{
    QTCloudListDirResult r = m_client->GetDirList();
    _QTCloudListDirResult _r;
    removeRows(0, rowCount());
    int row = 0;
    foreach (_r, r.m_dir) {
        insertRows(row, 1);
        if("Method" == _r.m_name)
            setData(index(row, DIR_NAME), tr("Method"));
        else if("Data" == _r.m_name)
            setData(index(row, DIR_NAME), tr("Data"));
        setData(index(row, DIR_CODE), _r.m_code);
        if("001" == _r.m_code)
            setData(index(row, DIR_PATH), DB_METHOD);
        else if("002" == _r.m_code)
            setData(index(row, DIR_PATH), DB_DATA);
        row++;
    }
    submit();
    emit sigQueryRootDirSuccess();
}

void HNCloudModel::queryFilesResult()
{
    QTCloudListFileResult r = m_client->GetListedFiles();
    _QTCloudListFileResult _r;

    QStandardItem* dir = findDirByCode(r.m_code);
    if(NULL == dir)
        return;
    dir->removeRows(0, dir->rowCount());
    dir->setColumnCount(FILE_MAX);
    dir->setRowCount(0);
    int row = 0;
    foreach (_r, r.m_file) {
        dir->insertRows(row, 1);
        setData(dir->index().child(row, FILE_NAME), _r.m_name);
        setData(dir->index().child(row, FILE_ID), _r.m_id);
        setData(dir->index().child(row, FILE_SIZE), _r.m_size);
        setData(dir->index().child(row, FILE_DATE), _r.m_date);
        row++;
    }
    submit();
}

QStandardItem *HNCloudModel::findDirByCode(QString code)
{
    for(int i = 0; i < rowCount(); i++)
    {
        if(data(index(i, 1)).toString() == code)
            return item(i, 0);
    }
    return NULL;
}
