
#include "hncloudform.h"
#include "ui_hncloudform.h"
#include "HNDefine.h"
#include "hnprogressdialog.h"
#include "hnmsgbox.h"

HNCloudForm::HNCloudForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNCloudForm)
{
    ui->setupUi(this);

    m_cli = HNSingleClient(this);

    m_prog = new HNProgressDialog(this);
    m_progDown = new HNProgressDialog(this);
    m_progDel = new HNProgressDialog(this);

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

HNCloudForm::~HNCloudForm()
{
    delete ui;
}

void HNCloudForm::chageLanguage()
{
    ui->retranslateUi(this);
}

void HNCloudForm::slotConnect()
{
    ui->treeCloud->slotConnect();
}

void HNCloudForm::slotDisConnect()
{
    ui->treeCloud->slotDisConnect();
}

void HNCloudForm::slotUpdateLabReport()
{
}

void HNCloudForm::slotOpenProgress()
{
    connect(m_cli, SIGNAL(signalUpdateProgress(int)),
            m_prog, SLOT(setValue(int)));

    connect(m_cli, SIGNAL(signalUploadSucc(QString)),
            m_prog, SLOT(accept()));
    connect(m_prog, SIGNAL(rejected()),
            m_cli, SLOT(sendCancelUpload()));

    connect(m_prog, SIGNAL(accepted()),
            this, SLOT(slotOpenOK()));
    connect(m_prog, SIGNAL(rejected()),
            this, SLOT(slotOpenOK()));

    m_prog->initAll();
    m_prog->show();
}

void HNCloudForm::slotOpenOK()
{
    disconnect(m_cli, SIGNAL(signalUpdateProgress(int)),
            m_prog, SLOT(setValue(int)));

    disconnect(m_cli, SIGNAL(signalUploadSucc(QString)),
            m_prog, SLOT(accept()));
    disconnect(m_prog, SIGNAL(rejected()),
            m_cli, SLOT(sendCancelUpload()));

    disconnect(m_prog, SIGNAL(accepted()),
            this, SLOT(slotOpenOK()));
    disconnect(m_prog, SIGNAL(rejected()),
            this, SLOT(slotOpenOK()));

    QString localfile = ui->treeLocal->currentUploadingFile();
    pline() << "remove " << localfile;
    QFile::remove(localfile);

    if(QDialog::Accepted == m_prog->result() )
        HNMsgBox::warning(this, "Upload Success");
    else
        HNMsgBox::warning(this, "Upload Canceled");
}

void HNCloudForm::slotOpenDownProgress()
{
    connect(m_cli, SIGNAL(signalUpdateProgress(int)),
            m_progDown, SLOT(setValue(int)));

    connect(m_cli, SIGNAL(signalUploadSucc(QString)),
            m_progDown, SLOT(accept()));
    connect(m_progDown, SIGNAL(rejected()),
            m_cli, SLOT(sendCancelUpload()));

    connect(m_progDown, SIGNAL(accepted()),
            this, SLOT(slotOpenOK()));
    connect(m_progDown, SIGNAL(rejected()),
            this, SLOT(slotOpenOK()));

    m_progDown->initAll();
    m_progDown->show();
}


void HNCloudForm::slotOpenDownOK()
{
    disconnect(m_cli, SIGNAL(signalUpdateProgress(int)),
            m_progDown, SLOT(setValue(int)));

    disconnect(m_cli, SIGNAL(signalUploadSucc(QString)),
            m_progDown, SLOT(accept()));
    disconnect(m_progDown, SIGNAL(rejected()),
            m_cli, SLOT(sendCancelUpload()));

    disconnect(m_progDown, SIGNAL(accepted()),
            this, SLOT(slotOpenOK()));
    disconnect(m_progDown, SIGNAL(rejected()),
            this, SLOT(slotOpenOK()));

    QString downedFile = ui->treeCloud->currentDownloadingFile();
    QString localname = ui->treeCloud->currentDownloadingFilelocalName();

    pline() << downedFile << localname;

    system(QString("mv %1 %2").arg(downedFile).arg(localname).toAscii().data());

    if(QDialog::Accepted == m_progDown->result() )
        HNMsgBox::warning(this, "Download Success");
    else
        HNMsgBox::warning(this, "Download Canceled");
}

void HNCloudForm::slotDelProgress()
{
    connect(m_cli, SIGNAL(signalListFileOK()),
            this, SLOT(slotDelOK()));
    m_progDel->initAll();
    m_progDel->show();
}

void HNCloudForm::slotDelOK()
{
    m_progDel->setValue(100);
    m_progDel->accept();
    disconnect(m_cli, SIGNAL(signalListFileOK()),
               this, SLOT(slotDelOK()));
}
