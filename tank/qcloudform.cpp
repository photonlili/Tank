
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

    QTankClient* client = HNSingleClient(this);

#if 0
    m_prog = new QProgressWindow(this);
    connect(client, SIGNAL(signalUpdateProgress(int)),
            m_prog, SLOT(setValue(int)));
    connect(client, SIGNAL(signalUploadSucc(QString)),
            m_prog, SLOT(cancel()));
    connect(m_prog, SIGNAL(canceled()),
            client, SLOT(sendCancelUpload()));
    connect(ui->pushButton_upload, SIGNAL(clicked()),
            this, SLOT(slotOpenProgress()), Qt::QueuedConnection);

    m_progDown = new QProgressWindow(this);
    connect(client, SIGNAL(signalUpdateProgress(int)),
            m_progDown, SLOT(setValue(int)));
    connect(client, SIGNAL(signalDownSucc()),
            m_progDown, SLOT(cancel()));
    connect(m_progDown, SIGNAL(canceled()),
            client, SLOT(sendCancelDown()));
    connect(ui->pushButton_down, SIGNAL(clicked()),
            this, SLOT(slotOpenDownProgress()), Qt::QueuedConnection);
#endif

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
    m_prog->initAll();
    m_prog->show();
}

void QCloudForm::slotOpenDownProgress()
{
    m_progDown->initAll();
    m_progDown->show();
}
