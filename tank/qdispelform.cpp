#include "qdispelform.h"
#include "ui_qdispelform.h"
#include "qtankpublic.h"
#include <QFileDialog>
#include "qcustomplot.h"
#include "qctabbar.h"
#include "QTime"
#include "qprogresswindow.h"

QDispelForm::QDispelForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDispelForm)
{
    ui->setupUi(this);

    ui->tabWidget_dispel->tabBar()->installEventFilter(this);

    ui->btn_open->setFixedSize(80, 30);
    ui->btn_open_2->setFixedSize(80, 30);
    ui->btn_play->setFixedSize(80, 30);
    ui->btn_play_2->setFixedSize(80, 30);
    ui->btn_stop->setFixedSize(80, 30);
    ui->btn_stop_2->setFixedSize(80, 30);
    ui->btn_trans->setFixedSize(80, 30);
    ui->btn_trans_2->setFixedSize(80, 30);
    ui->btn_turn->setFixedSize(80, 30);
    ui->btn_turn_2->setFixedSize(80, 30);
    ui->btnStir->setFixedSize(80, 30);

    ui->btn_open->iconTable()[BTN_NORMAL] = "://theme/basic/bt_open.png";
    ui->btn_open->iconTable()[BTN_PRESS] = "://theme/basic/bt_open_press.png";
    ui->btn_open_2->iconTable()[BTN_NORMAL] = "://theme/basic/bt_open.png";
    ui->btn_open_2->iconTable()[BTN_PRESS] = "://theme/basic/bt_open_press.png";

    ui->btn_play->iconTable()[BTN_NORMAL] = "://theme/basic/bt_play.png";
    ui->btn_play->iconTable()[BTN_PRESS] = "://theme/basic/bt_play_press.png";
    ui->btn_play_2->iconTable()[BTN_NORMAL] = "://theme/basic/bt_play.png";
    ui->btn_play_2->iconTable()[BTN_PRESS] = "://theme/basic/bt_play_press.png";

    ui->btn_stop->iconTable()[BTN_NORMAL] = "://theme/basic/bt_stop.png";
    ui->btn_stop->iconTable()[BTN_PRESS] = "://theme/basic/bt_stop_press.png";
    ui->btn_stop_2->iconTable()[BTN_NORMAL] = "://theme/basic/bt_stop.png";
    ui->btn_stop_2->iconTable()[BTN_PRESS] = "://theme/basic/bt_stop_press.png";

    ui->btn_trans->iconTable()[BTN_NORMAL] = "://theme/basic/bt_view.png";
    ui->btn_trans->iconTable()[BTN_PRESS] = "://theme/basic/bt_view_press.png";
    ui->btn_trans_2->iconTable()[BTN_NORMAL] = "://theme/basic/bt_view.png";
    ui->btn_trans_2->iconTable()[BTN_PRESS] = "://theme/basic/bt_view_press.png";

    ui->btn_turn->iconTable()[BTN_NORMAL] = "://theme/basic/bt_turn.png";
    ui->btn_turn->iconTable()[BTN_PRESS] = "://theme/basic/bt_turn_press.png";
    ui->btn_turn_2->iconTable()[BTN_NORMAL] = "://theme/basic/bt_turn2.png";
    ui->btn_turn_2->iconTable()[BTN_PRESS] = "://theme/basic/bt_turn2_press.png";

    ui->btnStir->iconTable()[BTN_NORMAL] = "://theme/basic/bt_stir.png";
    ui->btnStir->iconTable()[BTN_PRESS] = "://theme/basic/bt_stir_press.png";

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeNewData()));
    timer2 = new QTimer(this);
    timer2->setSingleShot(false);
    connect(timer2, SIGNAL(timeout()), this, SLOT(timeNewData2()));

    m_dlg = new QReportViewDialog(this);

    methodForm = new QMethodForm(this);
    connect(methodForm, SIGNAL(tellLibraryDisplayed(QString)), ui->lb_libname, SLOT(setText(QString)));
    connect(methodForm, SIGNAL(tellMethod(QString)), ui->lb_method, SLOT(setText(QString)));
    connect(methodForm, SIGNAL(tellType(QString)), ui->lb_type, SLOT(setText(QString)));
    connect(methodForm, SIGNAL(selMethod(QString, int)), this, SLOT(prepareRunning(QString, int)));

    methodForm2 = new QMethodForm(this);
    connect(methodForm2, SIGNAL(tellLibraryDisplayed(QString)), ui->lb_libname_2, SLOT(setText(QString)));
    connect(methodForm2, SIGNAL(tellMethod(QString)), ui->lb_method_2, SLOT(setText(QString)));
    connect(methodForm2, SIGNAL(selMethod(QString, int)), this, SLOT(prepareExtractRunning(QString, int)));

    m_plotObjectHandler = new QCPDocumentObject(this);
    m_text = new QTextEdit(this);
    m_text->setHidden(true);
    m_text->document()->documentLayout()->registerHandler(QCPDocumentObject::PlotTextFormat, m_plotObjectHandler);

    com0 = HNPeerPort(this);
    s2 = HNSerialPort(this);
    excp = HNSingleException(this);
    connect(com0, SIGNAL(sigPeerException(quint16)), this, SLOT(slotException(quint16)));
    m_debug = new QDebugWidget(this);
    connect(com0, SIGNAL(sigDebug(QByteArray)), m_debug, SLOT(slotRecvMsg(QByteArray)));
    connect(com0, SIGNAL(sigStat(quint16,quint16,quint8)), this, SLOT(slotStat(quint16,quint16,quint8)));
    m_debug->setGeometry(18, 260, 700, 70);
    m_debug->setShown(false);
    com0->sendMsgConnectToC51();

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

    ui->widget_9->setFixedWidth(140);
    ui->widget_10->setFixedWidth(140);
    ui->widget_3->setFixedWidth(520);
    ui->widget_4->setFixedWidth(434);
}

QDispelForm::~QDispelForm()
{
    delete ui;
}

void QDispelForm::initAll()
{
    // 默认不运行
    bRunning = eStop;
    //读取上一次的选中库和选中方法
    methodForm->initAll("Library <> 'Extract'");
    methodForm2->initAll("Library = 'Extract'");
    ui->lb_libname->setText(tr("System"));
    prepareRunning(DB_HANON, 1);
    ui->lb_libname_2->setText(tr("Extract Lib"));
    prepareExtractRunning(DB_EXTRACT, 1);
}

void QDispelForm::timeNewData()
{
    quint8 stage;
    quint8 vessel;
    quint16 pressure;
    quint16 tempture;
    quint16 hold;
    static quint16 ramp = 0;
    static quint16 preRamp = 0;

    if(bRunning == ePause)
    {
        m_pauseTime++;
        return;
    }

    if(m_lastPointKey-m_initPointKey == 0)
    {
        ramp = 0;
        ui->tbv_stage->currentStageParam(stage, vessel, m_curRamp, pressure, tempture, hold);
        preRamp = ramp;
        ramp = m_curRamp;
    }
    else if(m_lastPointKey-m_initPointKey > m_totalStageRamp)
    {
        // stop
        on_btn_stop_clicked();
    }
    else if(m_lastPointKey-m_initPointKey == ramp)
    {
        ui->tbv_stage->next();
        ui->tbv_stage->currentStageParam(stage, vessel, m_curRamp, pressure, tempture, hold);
        preRamp = ramp;
        ramp += m_curRamp;
    }

    pline() << m_curRamp << ramp << m_totalStageRamp << pressure << m_lastPointKey-m_initPointKey;

    //table
    quint16 curRamp = ramp-(quint16)(m_lastPointKey-m_initPointKey-m_pauseTime);
    ui->tbv_stage->setRamp(curRamp-1);

    //stat
    com0->sendStat();

    if(!m_debug->isHidden())
        com0->sendDebug();
}

void QDispelForm::timeNewData2()
{
    quint8 stage;
    quint8 vessel;
    quint16 pressure;
    quint16 tempture;
    quint16 hold;
    static quint16 ramp = 0;
    static quint16 preRamp = 0;

    if(bRunning == ePause)
    {
        m_pauseTime2++;
        return;
    }

    if(m_lastPointKey2-m_initPointKey2 == 0)
    {
        m_curRamp2 = 0;
        ui->tbv_stage_2->currentStageParam(stage, vessel, m_curRamp2, pressure, tempture, hold);
        preRamp = 0;
        ramp = m_curRamp2;
    }
    else if(m_lastPointKey2-m_initPointKey2 > m_totalStageRamp2)
    {
        // stop
        on_btn_stop_2_clicked();
        return;
    }
    else if(m_lastPointKey2-m_initPointKey2 == ramp)
    {
        ui->tbv_stage_2->next();
        ui->tbv_stage_2->currentStageParam(stage, vessel, m_curRamp2, pressure, tempture, hold);
        preRamp = ramp;
        ramp += m_curRamp2;
    }

    //获取温度和压力
    //从单片机获取temp和press
    int temp = 230;
    int press = 124;

    pline() << m_curRamp2 << ramp << m_totalStageRamp2 <<
               temp << pressure << m_lastPointKey2-m_initPointKey2;

    //table
    quint16 curRamp = ramp-(quint16)(m_lastPointKey2-m_initPointKey2-m_pauseTime2);
    ui->tbv_stage_2->setRamp(curRamp-1);

    //stat
    ui->label_curtemp_2->setText(QString("%1").arg(temp));
    ui->label_stressure_2->setText(QString("%1").arg(press));

    //plot
    int key = m_lastPointKey2 - m_initPointKey2;
    ui->page_plot_2->addTempture(key, temp);
    ui->page_plot_2->addPressure(key, press);
    //if(key>20)
        //ui->page_plot->xAxis->setRange(key-20, 20, Qt::AlignLeft);
    if(key > 20)
    {
        ui->page_plot_2->xAxis->setTickStep(10);
        ui->page_plot_2->xAxis->setRange(0, key, Qt::AlignLeft);
    }
    ui->page_plot_2->replot();

    m_lastPointKey2 = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
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
    int type = methodForm->currentMethodType();
    QString name = methodForm->currentMethodName();        
    pline() << db << name << mid << type;
    ui->tbv_stage->initdb(db);
    ui->tbv_stage->refresh(mid, type);
    ui->lb_method->setText(name);
}

void QDispelForm::prepareExtractRunning(QString db, int mid)
{
    QString name = methodForm2->currentMethodName();
    ui->tbv_stage_2->initdb(DB_EXTRACT);
    ui->tbv_stage_2->refresh(mid);
    ui->lb_method_2->setText(name);
}

void QDispelForm::on_btn_open_clicked()
{
    methodForm->initAll("Library <> 'Extract'");
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
        continueHeating();
    }
    else if(bRunning == eStop)
    {
        emit signalLockPage(true);

        ui->tbv_stage->selectStage(0);
        m_initPointKey = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
        m_lastPointKey = m_initPointKey;
        bRunning = ePlay;
        m_pauseTime = 0;
        timer->start(1000);
        startHeating();
        //serialNo = m_dlg->newReport(methodForm->currentLibrary(),
        //                 methodForm->currentMethodName());
    }
}

void QDispelForm::startHeating()
{
    ui->btn_play->iconTable()[BTN_NORMAL] = "://theme/basic/bt_playing.png";
    ui->btn_play->iconTable()[BTN_PRESS] = "://theme/basic/bt_playing_press.png";
    ui->sw_main->setCurrentIndex(0);

    quint8 stage;
    quint8 vessel;
    quint16 ramp;
    quint16 press;
    quint16 tempture;
    quint16 hold;
    ui->tbv_stage->currentStageParam(stage, vessel, ramp, press, tempture, hold);
    m_totalStageRamp = ui->tbv_stage->totalStageTimeRamp();
    m_currentStage = ui->tbv_stage->currentStage();

    pline() << stage << vessel << ramp << press << tempture << hold;
    pline() << m_currentStage << m_totalStageRamp;

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
        //com0->sendMsgHeatExtract(stage, tempture, hold);
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
    ui->btn_play->iconTable()[BTN_NORMAL] = "://theme/basic/bt_pause.png";
    ui->btn_play->iconTable()[BTN_PRESS] = "://theme/basic/bt_pause_press.png";
    com0->sendMsgPause();
}

void QDispelForm::continueHeating()
{
    ui->btn_play->iconTable()[BTN_NORMAL] = "://theme/basic/bt_playing.png";
    ui->btn_play->iconTable()[BTN_PRESS] = "://theme/basic/bt_playing_press.png";
    ui->sw_main->setCurrentIndex(0);

    quint8 stage;
    quint8 vessel;
    quint16 ramp;
    quint16 press;
    quint16 tempture;
    quint16 hold;
    ui->tbv_stage->currentStageParam(stage, vessel, ramp, press, tempture, hold);


    pline() << stage << vessel << ramp << press << tempture << hold;
    pline() << m_currentStage << m_totalStageRamp;

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
        //com0->sendMsgHeatExtract(stage, tempture, hold);
    }

}

void QDispelForm::stopHeating()
{
    ui->btn_play->iconTable()[BTN_NORMAL] = "://theme/basic/bt_play.png";
    ui->btn_play->iconTable()[BTN_PRESS] = "://theme/basic/bt_play_press.png";
    ui->btn_play->update();
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
    emit signalLockPage(false);
    bRunning = eStop;
    if(timer->isActive())
    {
        ui->tbv_stage->setRamp(m_curRamp);
        ui->tbv_stage->selectStage(ui->tbv_stage->currentStage());
    }
    timer->stop();
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
    methodForm2->initAll("Library = 'Extract'");
    methodForm2->exec();
}

void QDispelForm::on_btn_play_2_clicked()
{
    //pause or play interface

    //reset flag
    if(bRunning == ePlay)
    {
        bRunning = ePause;
        pauseHeatingExtract();
    }
    else if(bRunning == ePause)
    {
        bRunning = ePlay;
        startHeatingExtract();
    }
    else if(bRunning == eStop)
    {
        emit signalLockPage(true);

        m_initPointKey2 = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
        m_lastPointKey2 = m_initPointKey2;

        bRunning = ePlay;
        m_pauseTime2 = 0;
        timer2->start(1000);
        ui->tbv_stage_2->selectStage(0);

        startHeatingExtract();
        //serialNo = m_dlg->newReport(methodForm->currentLibrary(),
        //                 methodForm->currentMethodName());
    }
}

void QDispelForm::startHeatingExtract()
{
    ui->btn_play_2->iconTable()[BTN_NORMAL] = "://theme/basic/bt_playing.png";
    ui->btn_play_2->iconTable()[BTN_PRESS] = "://theme/basic/bt_playing_press.png";
    ui->sw_main_2->setCurrentIndex(0);

    quint8 stage;
    quint8 vessel;
    quint16 ramp;
    quint16 press;
    quint16 tempture;
    quint16 hold;
    ui->tbv_stage_2->currentStageParam(stage, vessel, ramp, press, tempture, hold);
    m_totalStageRamp2 = ui->tbv_stage_2->totalStageTimeRamp();
    int currentStage2 = ui->tbv_stage_2->currentStage();

    pline() << currentStage2 << m_totalStageRamp2;

    int type = methodForm->currentMethodType();
    if(Type_Standard == type)
    {
        //com0->sendMsgHeatStandard(stage, vessel, tempture, hold);
    }
    else if(Type_Stressure == type)
    {
        //com0->sendMsgHeatPress(stage, vessel, press);
    }
    else if(Type_Temprature == type)
    {
        //com0->sendMsgHeatRAMP(stage, vessel, ramp, press, tempture, hold);
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

void QDispelForm::pauseHeatingExtract()
{
    ui->btn_play_2->iconTable()[BTN_NORMAL] = "://theme/basic/bt_pause.png";
    ui->btn_play_2->iconTable()[BTN_PRESS] = "://theme/basic/bt_pause_press.png";
    com0->sendMsgPause();
}

void QDispelForm::on_btn_stop_2_clicked()
{
    bRunning = eStop;
    if(timer2->isActive())
    {
        ui->tbv_stage_2->setRamp(m_curRamp2);
        ui->tbv_stage_2->selectStage(ui->tbv_stage_2->currentStage());
    }
    timer2->stop();
    emit signalLockPage(false);
    ui->btn_play_2->iconTable()[BTN_NORMAL] = "://theme/basic/bt_play.png";
    ui->btn_play_2->iconTable()[BTN_PRESS] = "://theme/basic/bt_play_press.png";
    ui->btn_play_2->update();
    stopHeatingExtract();
}

void QDispelForm::stopHeatingExtract()
{
    com0->sendMsgStop();

    QPixmap pix = ui->page_plot->toPixmap(600, 320);
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QBuffer::WriteOnly);
    pix.save(&buffer, "BMP");
    buffer.close();

    emit signalUpdateLabReport();
}

void QDispelForm::on_btn_trans_2_clicked()
{
    int index = ui->sw_main_2->currentIndex();
    index = index == 0 ? 1 : 0;
    ui->sw_main_2->setCurrentIndex(index);
}

void QDispelForm::on_btnStir_clicked()
{
    com0->sendStirSet(0x08);
}

void QDispelForm::slotException(quint16 e)
{
    pline() << e;

    excp->newExcp(e);

    if(e == 0x0000)
        excp->close();
    else
        excp->exec();
}

void QDispelForm::slotStat(quint16 temp, quint16 press, quint8 stat)
{
    ui->label_curtemp->setText(QString("%1").arg(temp));
    ui->label_stressure->setText(QString("%1").arg(press));

    pline() << stat;
    //plot
    int key = m_lastPointKey - m_initPointKey;
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

    m_lastPointKey = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

}


bool QDispelForm::eventFilter(QObject *o, QEvent *e)
{
    if(ui->tabWidget_dispel->tabBar() == o && e->type() == QEvent::MouseButtonPress)
        if(bRunning != eStop)
            return true;
    return QObject::eventFilter(o, e);
}
