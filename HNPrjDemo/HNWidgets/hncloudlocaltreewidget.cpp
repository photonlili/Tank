#include "hncloudlocaltreewidget.h"
#include "ui_hncloudlocaltreewidget.h"
#include "HNDefine.h"
#include "hnprintpreviewdialog.h"
#include "hnmsgbox.h"

HNCloudLocalTreeWidget::HNCloudLocalTreeWidget(QWidget *parent) :
    HNCloudTreeView(parent),
    ui(new Ui::HNCloudLocalTreeWidget)
{
    ui->setupUi(this);
    m_model = new HNCloudLocalModel(this);
    setModel(m_model);
    setColumnHidden(DIR_CODE, true);
    setColumnHidden(DIR_PATH, true);

    QFont cloudFont = this->font();
    cloudFont.setPointSize(16);
    setFont(cloudFont);
    connect(this->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(currentRowChanged()));
}

HNCloudLocalTreeWidget::~HNCloudLocalTreeWidget()
{
    delete ui;
}

QString HNCloudLocalTreeWidget::currentUploadingFile()
{
    return QString("%1/%2").arg(m_localPath).arg(m_uploadFileName);
}

void HNCloudLocalTreeWidget::printFile()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();

    if(!parIndex.isValid())
        return;

    pline() << rootIndex().data().toString();
    pline() << currentIndex().parent().data().toString();

    if(m_model->index(parIndex.row(), DIR_CODE).data().toString() == "001")
        return;

    static QReportViewDialog* dlg = new QReportViewDialog(this);
    dlg->initAll("恒功率1600W_2015-12-01-16-25-52");
    if(QDialog::Accepted != dlg->exec())
        return;

    dlg->printToPdf();
    dlg->print();
}

void HNCloudLocalTreeWidget::uploadFile()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();
    if(!parIndex.isValid())
        return;

    QString code = m_model->index(parIndex.row(), DIR_CODE).data().toString();
    QString path = m_model->index(parIndex.row(), DIR_PATH).data().toString();
    QString fileName = m_model->index(curIndex.row(), FILE_NAME, parIndex).data().toString();
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss");
    m_uploadFileName = QString("%1_%2").arg(time).arg(fileName);
    m_localPath = path;

    QFile::copy(QString("%1/%2").arg(m_localPath).arg(fileName),
                QString("%1/%2").arg(m_localPath).arg(m_uploadFileName));

    QFileInfo file(QString("%1/%2").arg(m_localPath).arg(m_uploadFileName));
    int len = file.size();
    m_model->uploadFile(code, m_localPath, m_uploadFileName, len);
}

void HNCloudLocalTreeWidget::currentRowChanged()
{
    QModelIndex curIndex = currentIndex();
    QModelIndex parIndex = curIndex.parent();
    if(parIndex.isValid())
        return;
    m_model->queryFiles(m_model->index(curIndex.row(), DIR_CODE).data().toString());
    expand(curIndex);
}
