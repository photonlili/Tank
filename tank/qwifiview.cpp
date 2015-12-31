#include "qwifiview.h"
#include "ui_qwifiview.h"
#include "qcomponent.h"
#include "qtankpublic.h"

QWIFIView::QWIFIView(QWidget *parent) :
    QCTableView(parent),
    ui(new Ui::QWIFIView)
{
    ui->setupUi(this);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setHidden(true);
    verticalHeader()->setHidden(true);
    resizeColumnsToContents();
    horizontalHeader()->setStretchLastSection(true);
    setShowGrid(false);

#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif
    dg = new QWIFIViewTextDelegate(this);
    setItemDelegateForColumn(ESSID_STATUS, dg);
}

QWIFIView::~QWIFIView()
{
    delete ui;
}

void QWIFIViewTextDelegate::drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const
{
#if 0
    if (!rect.isValid())
        return;
    QStyleOptionViewItem opt(option);
    opt.rect = rect;
    opt.state = opt.state & ~QStyle::State_HasFocus;
    switch (state) {
    case Qt::Unchecked:
        opt.state |= QStyle::State_Off;
        break;
    case Qt::PartiallyChecked:
        opt.state |= QStyle::State_NoChange;
        break;
    case Qt::Checked:
            opt.state |= QStyle::State_On;
        break;
    }
    QApplication::style()->drawPrimitive(QStyle::PE_IndicatorViewItemCheck, &opt, painter);
#else
    QItemDelegate::drawCheck(painter, option, rect, state);
#endif
}

void QWIFIViewTextDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    if("COMPLETED" == text)
        painter->drawImage(rect, QImage("://theme/basic/bt_wifi_select.png"));
}
