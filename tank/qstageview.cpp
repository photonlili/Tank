#include "qstageview.h"
#include "ui_qstageview.h"
#include "qcheaderview.h"
#include "qtankdefine.h"
#include "qtankpublic.h"

QStageView::QStageView(QWidget *parent) :
    QCTableView(parent),
    ui(new Ui::QStageView)
{
    ui->setupUi(this);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif
    horizontalHeader()->setMinimumHeight(36);
    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    verticalHeader()->setHidden(true);
    resizeColumnsToContents();
    setShowGrid(false);

    dg = new QStageFormatTextDelegate(this);
    setItemDelegateForColumn(Stage_Timeramp, dg);
}

QStageView::~QStageView()
{
    delete ui;
}


void QStageFormatTextDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    qint32 time = text.toInt();
    qint32 hour = time / 60;
    qint32 minute = time % 60;
    painter->save();
    //pline() << quint32(option.state);
    if( 98561 == option.state)
        painter->setPen(option.palette.color(QPalette::BrightText));
    //else if( 98305 == option.state)
    //    painter->setPen(Qt::red);
    painter->drawText(rect, Qt::AlignCenter, QString("%1:%2")
                      .arg(hour, 2, 10, QLatin1Char('0'))
                      .arg(minute, 2, 10, QLatin1Char('0')));
    painter->restore();
}

void QStageFormatTextDelegate::drawDecoration(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QPixmap &pixmap) const
{

}

void QStageFormatTextDelegate::drawFocus(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const
{

}

void QStageFormatTextDelegate::drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const
{

}
