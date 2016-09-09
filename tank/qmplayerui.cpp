#include "qmplayerui.h"
#include "ui_qmplayerui.h"
#include "qtanklinux.h"
#include "qtankpublic.h"
#include "qtankdefine.h"

QMPlayerUI::QMPlayerUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMPlayerUI)
{
    ui->setupUi(this);

    m_bplayed = 0;
    app = new QMPlayerModel(this);
    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(posChanged()));

    int min = 1331/60;
    int sec = 1331%60;
    ui->label_timelength->setText(QString("%1:%2")
                                  .arg(min, 2, 10, QLatin1Char('0'))
                                  .arg(sec, 2, 10, QLatin1Char('0')));
    ui->horizontalSlider_seek->setRange(0, 1331);

    ui->label_timepos->setFixedWidth(45);
    ui->label_timelength->setFixedWidth(45);
    pline() << ui->label_timelength->text();

    m_vol = 20;
    ui->sliderVol->setRange(0, 35);
    ui->sliderVol->setValue(m_vol);

}

QMPlayerUI::~QMPlayerUI()
{
    delete ui;
}

void QMPlayerUI::on_toolButton_mute_clicked()
{
    static bool m = false;
    m = ~m;
    app->mute(m);
}

void QMPlayerUI::posChanged()
{
    double curpos = app->timePos();

    if(curpos >= 1331) app->stop();

    int nowPos = qRound(curpos);

    int min = nowPos/60;
    int sec = nowPos-min*60;

    ui->label_timepos->setText(QString("%1:%2")
                               .arg(min, 2, 10, QLatin1Char('0'))
                               .arg(sec, 2, 10, QLatin1Char('0')));
    ui->horizontalSlider_seek->setValue(curpos);

    if( m_startPos < 6 )
    {
        m_startPos++;
        int min = m_startPos/60;
        int sec = m_startPos-min*60;
        ui->label_timepos->setText(QString("%1:%2")
                                   .arg(min, 2, 10, QLatin1Char('0'))
                                   .arg(sec, 2, 10, QLatin1Char('0')));
        ui->horizontalSlider_seek->setValue(m_startPos);
        update();
    }

    pline() << ui->label_timepos->text();
}

void QMPlayerUI::on_btn_play_clicked()
{
    if(0 == m_bplayed)
    {
        m_bplayed = 1;
        app->play(QString("%1/%2").arg(AV_PATH).arg("Tank.flv"), this->winId());
        QPoint point(ui->widget_show->rect().left(), ui->widget_show->rect().top());
        app->setRect(ui->widget_show->mapToGlobal(point).x(), ui->widget_show->mapToGlobal(point).y(),
                ui->widget_show->rect().width(), ui->widget_show->rect().height());
        ui->sliderVol->setValue(m_vol);
        ui->horizontalSlider_seek->setValue(0);
        timer->start(1000);
        m_startPos = -1;
    }
    else if( 1 == m_bplayed )
    {
        m_bplayed = 2;
        timer->stop();
        app->pause();
    }
    else if( 2 == m_bplayed )
    {
        m_bplayed = 1;
        timer->start(1000);
        app->pause();
    }
}

void QMPlayerUI::on_btn_stop_clicked()
{
    if(m_bplayed==0)
        return;

    m_bplayed = 0;
    ui->horizontalSlider_seek->setValue(0);
    ui->label_timepos->setText("00:00");
    timer->stop();
    app->stop();
}


void QMPlayerUI::on_sliderVol_valueChanged(int value)
{
    app->setVolume(value);
    m_vol = value;
}
