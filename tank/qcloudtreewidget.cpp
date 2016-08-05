#include "qcloudtreewidget.h"
#include "ui_qcloudtreewidget.h"
#include <QFileInfo>
#include <QFile>
#include "qtankdefine.h"
#include "qcprinter.h"
#include "qtankclient.h"
#include "hnmsgbox.h"

QCloudTreeWidget::QCloudTreeWidget(QWidget *parent) :
    QCloudTreeView(parent),
    ui(new Ui::QCloudTreeWidget)
{
    ui->setupUi(this);
    m_client = HNSingleClient(this);
    connect(m_client, SIGNAL(connected()), this, SLOT(slotConnected()));
    model = new QCloudModel(this, m_client);
    setModel(model);

    setColumnHidden(FILE_ID, true);
    setColumnHidden(FILE_SIZE, true);
    setColumnHidden(FILE_DATE, true);

    header()->setResizeMode(QHeaderView::ResizeToContents);

    connect(model, SIGNAL(sigQueryDirSuccess()),
            this, SLOT(slotResize()));

    m_box = new HNMsgBox(this);

    QFont cloudFont = this->font();
    cloudFont.setPointSize(16);
    setFont(cloudFont);
    connect(this->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(currentRowChanged()));
}

QCloudTreeWidget::~QCloudTreeWidget()
{
    delete ui;
}

QString QCloudTreeWidget::currentDownloadingFile()
{
    return m_tmpfile;
}

QString QCloudTreeWidget::currentDownloadingFilelocalName()
{
    return m_localfile;
}

void QCloudTreeWidget::slotConnect(){
    m_box->warning(tr("Connecting..."));
    m_client->SendConnectMessage();
}

void QCloudTreeWidget::slotConnected()
{
    m_box->accept();
    m_client->sendLoginMessage();
}

void QCloudTreeWidget::slotDisConnect(){
    m_client->sendLogoutMessage();
    m_client->SendDisConnectFromHost();
}

void QCloudTreeWidget::slotResize()
{
    resizeColumnToContents(FILE_NAME);
}

void QCloudTreeWidget::downFile()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();
    if(!parIndex.isValid())
        return;
    QString path = model->index(parIndex.row(), DIR_PATH).data().toString();
    QString fileid = model->index(curIndex.row(), FILE_ID, parIndex).data().toString();
    QString filename = model->index(curIndex.row(), FILE_NAME, parIndex).data().toString();
    QString localname = filename.split("_").at(1);
    m_localfile = QString("%1/%2").arg(path).arg(localname);
    m_tmpfile = QString("%1/%2").arg(path).arg(filename);
    model->downFile(path, fileid, m_tmpfile);
}

void QCloudTreeWidget::delFile()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();
    if(!parIndex.isValid())
        return;
    QString code = model->index(parIndex.row(), DIR_CODE).data().toString();
    QString fileid = model->index(curIndex.row(), FILE_ID, parIndex).data().toString();
    pline() << code << fileid;
    model->delFile(code, fileid);
}

void QCloudTreeWidget::currentRowChanged()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();
    if(!parIndex.isValid())
        model->queryFiles(model->index(curIndex.row(), DIR_CODE).data().toString());
    expand(curIndex);
}
