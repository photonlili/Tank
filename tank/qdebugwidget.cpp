#include "qdebugwidget.h"
#include "ui_qdebugwidget.h"
#include "qcomponent.h"

QDebugWidget::QDebugWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDebugWidget)
{
    ui->setupUi(this);
}

QDebugWidget::~QDebugWidget()
{
    delete ui;
}

void QDebugWidget::slotRecvMsg(QByteArray msg)
{
    QByteArray m = msg;

    qint8 s1;
    qint16  s2;

    QString buf;

    m >> s1;
    buf += QString("V:%1 ").arg(s1);

    m>>s1;
    buf += QString("N1:%1 ").arg(s1);

    m>>s1;
    buf += QString("N2:%1 ").arg(s1);

    m>>s2;;
    buf += QString("T:%1 ").arg(s2);

    m>>s1;
    buf += QString("TX:%1 ").arg(QString::number(s1, 16));

    m>>s2;
    buf += QString("P:%1 ").arg(s2);

    m>>s1;
    buf += QString("PX:%1 ").arg(QString::number(s1, 16));

    m>>s1;
    buf += QString("P1:%1 ").arg(s1);

    m>>s1;
    buf += QString("P2:%1 ").arg(s1);

    m>>s2;
    buf += QString("V:%1 ").arg(s2);

    m>>s2;
    buf += QString("I1:%1 ").arg(s2);

    m>>s2;
    buf += QString("I2:%1 ").arg(s2);

    m>>s2;
    buf += QString("S:%1 ").arg(s2);

    m>>s1;
    buf += QString("KP:%1 ").arg(s1);

    m>>s1;
    buf += QString("KI:%1 ").arg(s1);

    m>>s1;
    buf += QString("KD:%1 ").arg(s1);

    m>>s1;
    buf += QString("TS:%1 ").arg(s1);

    m>>s2;
    buf += QString("OT:%1 ").arg(s2);

    ui->txtBrower->clear();
    ui->txtBrower->append(buf);
}
