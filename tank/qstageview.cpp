#include "qstageview.h"
#include "ui_qstageview.h"
#include "qcheaderview.h"
#include "qtankdefine.h"

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
