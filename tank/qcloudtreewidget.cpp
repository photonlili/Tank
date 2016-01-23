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
    QTankClient* client = HNSingleClient(this);
    model = new QCloudModel(this, client);
    setModel(model);

    setColumnHidden(FILE_ID, true);
    setColumnHidden(FILE_SIZE, true);
    setColumnHidden(FILE_DATE, true);

    QFont cloudFont = this->font();
    cloudFont.setPointSize(16);
    setFont(cloudFont);
    connect(this->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(currentRowChanged()));
    connect(model, SIGNAL(sigDownSuccess()), this, SLOT(downSuccess()));
}

QCloudTreeWidget::~QCloudTreeWidget()
{
    delete ui;
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
    model->downFile(path, fileid, localname);
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

void QCloudTreeWidget::downSuccess()
{
    pline() << m_tmpfile << m_localfile;
    QFile::rename(m_tmpfile, m_localfile);
    system(QString("mv %1 %2").arg(m_tmpfile).arg(m_localfile).toAscii().data());
    HNMsgBox::warning(this, "DownLoad Success");
}

void QCloudTreeWidget::currentRowChanged()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();
    if(!parIndex.isValid())
        model->queryFiles(model->index(curIndex.row(), DIR_CODE).data().toString());
    expand(curIndex);
}
