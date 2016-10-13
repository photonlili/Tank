#include "hnmsgbox.h"
#include "ui_hnmsgbox.h"
#include "QElapsedTimer"

void HNSleep(int millsecond)
{
    QElapsedTimer timer;
    timer.start();
    while(timer.elapsed() < millsecond)
    {
         QApplication::processEvents();
    }
}

HNMsgBox::HNMsgBox(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::HNMsgBox)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    connect(ui->btn_yes, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->btn_yes2, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->btn_no, SIGNAL(clicked()), this, SLOT(reject()));
}

HNMsgBox::~HNMsgBox()
{
    delete ui;
}



int HNMsgBox::warning(QWidget *parent, QString content )
{
    HNMsgBox* msgBox = new HNMsgBox(parent);
    return msgBox->_warning(content);
}

int HNMsgBox::question(QWidget *parent, QString content)
{
    HNMsgBox* msgBox = new HNMsgBox(parent);
    return msgBox->_question(content);
}

int HNMsgBox::_warning(QString content)
{
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(1);
    return exec();
}

int HNMsgBox::_question(QString content)
{
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(0);
    return exec();
}






void HNMsgBox::warning(QString content)
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(1);
    m_time = 0;
    //startTimer(1000);
    show();
    HNSleep(100);
}

void HNMsgBox::question(QString content)
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(0);
    m_time = 0;
    //startTimer(1000);
    show();
    HNSleep(100);
}

void HNMsgBox::information(QString content)
{
    setAttribute(Qt::WA_DeleteOnClose, false);
    ui->lb_content->setText(content);
    ui->stwBtn->setCurrentIndex(2);
    m_time = 0;
    //startTimer(1000);
    show();
    HNSleep(100);
}

void HNMsgBox::timerEvent(QTimerEvent *e)
{
    return;
    if(m_time > 5)
    {
        killTimer(e->timerId());
        reject();
        return;
    }
    m_time ++ ;
}




