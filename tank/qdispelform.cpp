#include "qdispelform.h"
#include "ui_qdispelform.h"
#include "qtankpublic.h"
#include <QFileDialog>
#include "qcustomplot.h"
#include "qctabbar.h"
#include "QTime"

QDispelForm::QDispelForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDispelForm)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeNewData()));

    m_dlg = new QReportViewDialog(this);
    methodForm = new QMethodForm(this);

    connect(methodForm, SIGNAL(tellLibrary(QString)), ui->lb_libname, SLOT(setText(QString)));
    connect(methodForm, SIGNAL(tellMethod(QString)), ui->lb_method, SLOT(setText(QString)));
    connect(methodForm, SIGNAL(tellType(QString)), ui->lb_type, SLOT(setText(QString)));
    connect(methodForm, SIGNAL(selMethod(QString, int)), this, SLOT(prepareRunning(QString, int)));

    m_plotObjectHandler = new QCPDocumentObject(this);
    m_text = new QTextEdit(this);
    m_text->setHidden(true);
    m_text->document()->documentLayout()->registerHandler(QCPDocumentObject::PlotTextFormat, m_plotObjectHandler);

    com0 = HNPeerPort(this);
    s2 = HNSerialPort(this);
    excp = HNSingleException(this);
    connect(com0, SIGNAL(sigPeerException(int)), this, SLOT(slotException(int)));
    m_debug = new QDebugWidget(this);
    connect(com0, SIGNAL(sigRecvMsg(QByteArray)), m_debug, SLOT(slotRecvMsg(QByteArray)));
    m_debug->setGeometry(18, 260, 700, 70);
    m_debug->setShown(false);
    //com0->sendMsgConnectToC51();

    ui->lb_libbuddy->setFixedWidth(50);
    ui->lb_libname->setFixedWidth(100);
    ui->hs_0->setGeometry(QRect(150, 0, 40, 30));
    ui->lb_mbuddy->setFixedWidth(55);
    ui->lb_method->setFixedWidth(100);
    ui->hs_1->setGeometry(QRect(305, 0,  40, 30));

    ui->lb_libbuddy_2->setFixedWidth(50);
    ui->lb_libname_2->setFixedWidth(100);
    ui->hs_2->setGeometry(QRect(150, 0, 40, 30));
    ui->lb_mbuddy_2->setFixedWidth(55);
    ui->lb_method_2->setFixedWidth(100);
    ui->hs_3->setGeometry(QRect(305, 0,  40, 30));

    ui->widget_10->setFixedWidth(121);
    ui->widget_4->setFixedWidth(445);
}

QDispelForm::~QDispelForm()
{
    delete ui;
}

void QDispelForm::initAll()
{
    // 默认不运行
    bRunning = eStop;
    methodForm->initAll();
    prepareRunning(DB_HANON, 1);
}

void QDispelForm::timeNewData()
{
    int temp = qrand() % 300;
    int press = qrand() % 800;

    static double initPointKey = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;
    double currentPointKey = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    pline() << currentPointKey << temp << press << currentPointKey-initPointKey << currentPointKey-lastPointKey;
    if (currentPointKey-lastPointKey > 0.01) // at most add point every 10 ms
    {
        int key = currentPointKey-initPointKey;
        pline() << qSin(key*10) * 15;
        int temp = key * 14 + 10 + qSin(key) * 14;
        int press = key * 24 + 18 + qCos(key) * 15;
        ui->label_curtemp->setText(QString("%1").arg(temp));
        ui->label_stressure->setText(QString("%1").arg(press));
        ui->page_plot->addTempture(key, temp);
        ui->page_plot->addPressure(key, press);
        //if(key>20)
            //ui->page_plot->xAxis->setRange(key-20, 20, Qt::AlignLeft);
        if(key > 20)
        {
            ui->page_plot->xAxis->setTickStep(10);
            ui->page_plot->xAxis->setRange(0, key, Qt::AlignLeft);
        }
        ui->page_plot->replot();
        lastPointKey = currentPointKey;
    }
    //pline() << ui->tbv_stage->rect();
}

void QDispelForm::initLanguage()
{
    ui->retranslateUi(this);
}

void QDispelForm::showDebugWindow(int show)
{
    m_debug->setShown(show);
}

void QDispelForm::prepareRunning(QString db, int mid)
{
    pline() << db << mid;
    ui->tbv_stage->initdb(db);
    ui->tbv_stage->refresh(mid);
    ui->tbv_stage_2->initdb(DB_EXTRACT);
    ui->tbv_stage_2->refresh(mid);
}

void QDispelForm::on_btn_open_clicked()
{
    methodForm->initAll();
    methodForm->exec();
}

void QDispelForm::on_btn_play_clicked()
{
    //pause or play interface

    //reset flag
    if(bRunning == ePlay)
    {
        bRunning = ePause;
        pauseHeating();
    }
    else if(bRunning == ePause)
    {
        bRunning = ePlay;
        startHeating();
    }
    else if(bRunning == eStop)
    {
        bRunning = ePlay;
        startHeating();
        serialNo = m_dlg->newReport(methodForm->currentLibrary(),
                         methodForm->currentMethodName());
    }
}

void QDispelForm::startHeating()
{
    timer->start(1000);
    ui->btn_play->setText(tr("Pause"));
    ui->sw_main->setCurrentIndex(0);

    quint8 stage;
    quint8 vessel;
    quint16 ramp;
    quint16 press;
    quint16 tempture;
    quint16 hold;
    ui->tbv_stage->currentStageParam(stage, vessel, ramp, press, tempture, hold);

    int type = methodForm->currentMethodType();
    if(Type_Standard == type)
    {
        com0->sendMsgHeatStandard(stage, vessel, tempture, hold);
    }
    else if(Type_Stressure == type)
    {
        com0->sendMsgHeatPress(stage, vessel, press);
    }
    else if(Type_Temprature == type)
    {
        com0->sendMsgHeatRAMP(stage, vessel, ramp, press, tempture, hold);
    }
    else if(Type_Extract == type)
    {
        com0->sendMsgHeatExtract(stage, tempture, hold);
    }

    /*
    m_text->clear();
    QString company = QString(tr("Company:%1")).arg("Hanon");
    m_text->append(company);
    QString user = QString(tr("User:%1")).arg(gUserName);
    m_text->append(user);
    QString lib = QString(tr("Library:%1")).arg(methodForm->currentLibrary());
    m_text->append(lib);
    QString method = QString(tr("Method:%1")).arg(methodForm->currentMethodName());
    m_text->append(method);
    m_text->append(tr("SerialNo:1"));
    m_text->append(QString(tr("StartTime:%1")).arg(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")));
    */
}

void QDispelForm::pauseHeating()
{
    ui->btn_play->setText(tr("Play"));
    timer->stop();
    com0->sendMsgPause();
}

void QDispelForm::stopHeating()
{
    timer->stop();
    ui->btn_play->setText(tr("Play"));
    com0->sendMsgStop();

    QPixmap pix = ui->page_plot->toPixmap(600, 320);
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QBuffer::WriteOnly);
    pix.save(&buffer, "BMP");
    buffer.close();
    //m_dlg->endReport(serialNo, "None", "UserStop", ba);
    emit signalUpdateLabReport();

    /*
    m_text->append(tr("Plot:\n"));
    QTextCursor cursor = m_text->textCursor();
    int width = 600, height = 320;
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), QCPDocumentObject::generatePlotFormat(ui->page_plot, width, height));
    m_text->setTextCursor(cursor);
    m_text->append(tr("Exception:None"));
    m_text->append(tr("StopReasion:User Stop"));
    m_text->append(QString(tr("StopTime:%1")).arg(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")));
    saveLabReport();
    */
}

void QDispelForm::saveLabReport()
{
    QPrinter printerText;
    printerText.setOutputFormat(QPrinter::PdfFormat);
    QString fileName = QString("%1.pdf").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm"));
    printerText.setOutputFileName(fileName);

    QPrinter printer;
    printer.setFullPage(true);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    m_text->document()->print(&printer);
    emit signalUpdateLabReport();
}

void QDispelForm::on_btn_stop_clicked()
{
    bRunning = eStop;
    stopHeating();
}

void QDispelForm::on_btn_trans_clicked()
{
    int index = ui->sw_main->currentIndex();
    index = index == 0 ? 1 : 0;
    ui->sw_main->setCurrentIndex(index);
}

void QDispelForm::on_btn_open_2_clicked()
{
    methodForm->initAll();
    methodForm->exec();
}

void QDispelForm::on_btn_play_2_clicked()
{
    //pause or play interface

    //reset flag
    if(bRunning == ePlay)
    {
        bRunning = ePause;
        startHeatingExtract();
    }
    else if(bRunning == ePause)
    {
        bRunning = ePlay;
        startHeatingExtract();
    }
    else if(bRunning == eStop)
    {
        bRunning = ePlay;
        startHeatingExtract();
        serialNo = m_dlg->newReport(methodForm->currentLibrary(),
                         methodForm->currentMethodName());
    }
}

void QDispelForm::startHeatingExtract()
{
    timer->start(1000);
    ui->btn_play_2->setText(tr("Pause"));
    ui->sw_main_2->setCurrentIndex(0);

    quint8 stage;
    quint8 vessel;
    quint16 ramp;
    quint16 press;
    quint16 tempture;
    quint16 hold;
    ui->tbv_stage_2->currentStageParam(stage, vessel, ramp, press, tempture, hold);

    int type = methodForm->currentMethodType();
    if(Type_Standard == type)
    {
        com0->sendMsgHeatStandard(stage, vessel, tempture, hold);
    }
    else if(Type_Stressure == type)
    {
        com0->sendMsgHeatPress(stage, vessel, press);
    }
    else if(Type_Temprature == type)
    {
        com0->sendMsgHeatRAMP(stage, vessel, ramp, press, tempture, hold);
    }
    else if(Type_Extract == type)
    {
        com0->sendMsgHeatExtract(stage, tempture, hold);
    }

    /*
        m_text->clear();
        QString company = QString(tr("Company:%1")).arg("Hanon");
        m_text->append(company);
        QString user = QString(tr("User:%1")).arg(gUserName);
        m_text->append(user);
        QString lib = QString(tr("Library:%1")).arg(methodForm->currentLibrary());
        m_text->append(lib);
        QString method = QString(tr("Method:%1")).arg(methodForm->currentMethodName());
        m_text->append(method);
        m_text->append(tr("SerialNo:1"));
        m_text->append(QString(tr("StartTime:%1")).arg(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")));
        */
}

void QDispelForm::on_btn_stop_2_clicked()
{
    bRunning = eStop;
    stopHeatingExtract();
}

void QDispelForm::stopHeatingExtract()
{
    timer->stop();
    ui->btn_play_2->setText(tr("Play"));
    com0->sendMsgStop();

    QPixmap pix = ui->page_plot->toPixmap(600, 320);
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QBuffer::WriteOnly);
    pix.save(&buffer, "BMP");
    buffer.close();
    //m_dlg->endReport(serialNo, "None", "UserStop", ba);
    emit signalUpdateLabReport();

    /*
    m_text->append(tr("Plot:\n"));
    QTextCursor cursor = m_text->textCursor();
    int width = 600, height = 320;
    cursor.insertText(QString(QChar::ObjectReplacementCharacter), QCPDocumentObject::generatePlotFormat(ui->page_plot, width, height));
    m_text->setTextCursor(cursor);
    m_text->append(tr("Exception:None"));
    m_text->append(tr("StopReasion:User Stop"));
    m_text->append(QString(tr("StopTime:%1")).arg(QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss")));
    saveLabReport();
    */
}

void QDispelForm::on_btn_trans_2_clicked()
{
    int index = ui->sw_main_2->currentIndex();
    index = index == 0 ? 1 : 0;
    ui->sw_main_2->setCurrentIndex(index);
}

void QDispelForm::on_btnStir_clicked()
{

}

void QDispelForm::on_btn_turn_clicked()
{

}

void QDispelForm::on_pushButton_4_clicked()
{

}

void QDispelForm::slotException(int e)
{
    pline() << e;
    excp->newExcp("GFFFF");
    excp->exec();
}
