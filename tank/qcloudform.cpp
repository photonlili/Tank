
#include "qcloudform.h"
#include "ui_qcloudform.h"
#include "qtankpublic.h"
#include "qprogresswindow.h"
#include "qprogressdialog.h"
#include "hnmsgbox.h"

QCloudForm::QCloudForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCloudForm)
{
    ui->setupUi(this);

    m_cli = HNSingleClient(this);

    m_progDel = new QProgressWindow(this);
    m_prog = new QProgressWindow(this);
    m_progDown = new QProgressWindow(this);

    connect(ui->pushButton_down, SIGNAL(clicked()),
            this, SLOT(slotOpenDownProgress()), Qt::QueuedConnection);
    connect(ui->pushButton_upload, SIGNAL(clicked()),
            this, SLOT(slotOpenProgress()), Qt::QueuedConnection);
    connect(ui->pushButton_del, SIGNAL(clicked()),
            this, SLOT(slotDelProgress()), Qt::QueuedConnection);

    connect(ui->pushButton_upload, SIGNAL(clicked()), ui->treeLocal, SLOT(uploadFile()), Qt::QueuedConnection);
    connect(ui->pushButton_del, SIGNAL(clicked()), ui->treeCloud, SLOT(delFile()));
    connect(ui->pushButton_down, SIGNAL(clicked()), ui->treeCloud, SLOT(downFile()));
    connect(ui->btn_print, SIGNAL(clicked()), ui->treeLocal, SLOT(printFile()));
}

QCloudForm::~QCloudForm()
{
    delete ui;
}

void QCloudForm::chageLanguage()
{
    ui->retranslateUi(this);
}

void QCloudForm::slotUpdateLabReport()
{
}

void QCloudForm::slotOpenProgress()
{
    connect(m_cli, SIGNAL(signalUpdateProgress(int)),
            m_prog, SLOT(setValue(int)));
    connect(m_cli, SIGNAL(signalUploadSucc()),
            this, SLOT(slotOpenOK()));
    connect(m_cli, SIGNAL(signalUploadSucc(QString)),
            m_prog, SLOT(cancel()));
    connect(m_prog, SIGNAL(canceled()),
            m_cli, SLOT(sendCancelUpload()));
    connect(m_prog, SIGNAL(canceled()),
            this, SLOT(slotOpenOK()));
    m_prog->initAll();
    m_prog->show();
}

void QCloudForm::slotOpenDownProgress()
{
    connect(m_cli, SIGNAL(signalUpdateProgress(int)),
            m_progDown, SLOT(setValue(int)));
    connect(m_cli, SIGNAL(signalDownSucc()),
            m_progDown, SLOT(cancel()));
    connect(m_cli, SIGNAL(signalDownSucc()),
            this, SLOT(slotOpenDownOK()));
    connect(m_progDown, SIGNAL(canceled()),
            m_cli, SLOT(sendCancelDown()));
    connect(m_progDown, SIGNAL(canceled()),
            this, SLOT(slotOpenDownOK()));
    m_progDown->initAll();
    m_progDown->show();
}

void QCloudForm::slotOpenOK()
{
    disconnect(m_cli, SIGNAL(signalUpdateProgress(int)),
            m_prog, SLOT(setValue(int)));
    disconnect(m_cli, SIGNAL(signalUploadSucc()),
            this, SLOT(slotOpenOK()));
    disconnect(m_cli, SIGNAL(signalUploadSucc(QString)),
            m_prog, SLOT(cancel()));
    disconnect(m_prog, SIGNAL(canceled()),
            m_cli, SLOT(sendCancelUpload()));
    disconnect(m_prog, SIGNAL(canceled()),
            this, SLOT(slotOpenOK()));
}

void QCloudForm::slotOpenDownOK()
{
    disconnect(m_cli, SIGNAL(signalUpdateProgress(int)),
            m_progDown, SLOT(setValue(int)));
    disconnect(m_cli, SIGNAL(signalDownSucc()),
            m_progDown, SLOT(cancel()));
    disconnect(m_cli, SIGNAL(signalDownSucc()),
            this, SLOT(slotOpenDownOK()));
    disconnect(m_progDown, SIGNAL(canceled()),
            m_cli, SLOT(sendCancelDown()));
    disconnect(m_progDown, SIGNAL(canceled()),
            this, SLOT(slotOpenDownOK()));
}

void QCloudForm::slotDelProgress()
{
    connect(m_cli, SIGNAL(signalListFileOK()),
            this, SLOT(slotDelOK()));
    m_progDel->initAll();
    m_progDel->show();
}

void QCloudForm::slotDelOK()
{
    m_progDel->setValue(100);
    m_progDel->cancel();
    disconnect(m_cli, SIGNAL(signalListFileOK()),
               this, SLOT(slotDelOK()));
}
