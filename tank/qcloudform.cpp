
#include "qcloudform.h"
#include "ui_qcloudform.h"
#include "qtankpublic.h"
#include "qprogresswindow.h"
#include "qprogressdialog.h"
#include "hnmsgbox.h"
#include "hntextcodec.h"

QCloudForm::QCloudForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCloudForm)
{
    ui->setupUi(this);

    m_cli = HNSingleClient(this);

    m_prog = new QProgressWindow(this);
    m_progDown = new QProgressWindow(this);
    m_progDel = new QProgressWindow(this);

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

    pline() << "-----------------------";
    QByteArray in,out;
    in = "新建库 hnge 你好().db";
    HNTextCodec::ConvertBytes(in, out, EUTF82GBK);
    QByteArray out2;
    HNTextCodec::ConvertBytes(out, out2, EGBK2UTF8);
    pline() << in << out << out2;
}

QCloudForm::~QCloudForm()
{
    delete ui;
}

void QCloudForm::chageLanguage()
{
    ui->retranslateUi(this);
    //pline() << ui->widgetCloud->size();
}

void QCloudForm::slotConnect()
{
    ui->treeCloud->slotConnect();
}

void QCloudForm::slotDisConnect()
{
    ui->treeCloud->slotDisConnect();
}

void QCloudForm::slotUpdateLabReport()
{
}

void QCloudForm::slotOpenProgress()
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

void QCloudForm::slotOpenOK()
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

void QCloudForm::slotOpenDownProgress()
{
    connect(m_cli, SIGNAL(signalUpdateProgress(int)),
            m_progDown, SLOT(setValue(int)));

    connect(m_cli, SIGNAL(signalDownSucc()),
            m_progDown, SLOT(accept()));
    connect(m_progDown, SIGNAL(rejected()),
            m_cli, SLOT(sendCancelDown()));

    connect(m_progDown, SIGNAL(accepted()),
            this, SLOT(slotOpenDownOK()));
    connect(m_progDown, SIGNAL(rejected()),
            this, SLOT(slotOpenDownOK()));

    m_progDown->initAll();
    m_progDown->show();
}


void QCloudForm::slotOpenDownOK()
{
    disconnect(m_cli, SIGNAL(signalUpdateProgress(int)),
            m_progDown, SLOT(setValue(int)));

    disconnect(m_cli, SIGNAL(signalDownSucc()),
            m_progDown, SLOT(accept()));
    disconnect(m_progDown, SIGNAL(rejected()),
            m_cli, SLOT(sendCancelDown()));

    disconnect(m_progDown, SIGNAL(accepted()),
            this, SLOT(slotOpenDownOK()));
    disconnect(m_progDown, SIGNAL(rejected()),
            this, SLOT(slotOpenDownOK()));

    QString downedFile = ui->treeCloud->currentDownloadingFile();
    QString localname = ui->treeCloud->currentDownloadingFilelocalName();

    pline() << downedFile << localname;

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    system(QString("mv \"%1\" \"%2\"").arg(downedFile).arg(localname).toAscii().data());
#else
    system(QString("mv \"%1\" \"%2\"").arg(downedFile).arg(localname).toLocal8Bit().data());
#endif
    if(QDialog::Accepted == m_progDown->result() )
        HNMsgBox::warning(this, "Download Success");
    else
        HNMsgBox::warning(this, "Download Canceled");
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
    m_progDel->accept();
    disconnect(m_cli, SIGNAL(signalListFileOK()),
               this, SLOT(slotDelOK()));
    HNMsgBox::warning(this, tr("Del succ!"));
}
