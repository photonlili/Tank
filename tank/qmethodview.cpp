#include "qmethodview.h"
#include "ui_qmethodview.h"
#include "qtankdefine.h"
#include "qtankpublic.h"

void QMethodFormatTextDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    QMethodView* view = (QMethodView*)parent;
    int index = view->rowAt(rect.top()) + 1;
    painter->drawText(rect, Qt::AlignVCenter, QString("%1、%2").arg(index).arg(text));
}

QMethodView::QMethodView(QWidget *parent) :
    QCTableView(parent),
    ui(new Ui::QMethodView)
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

    m_dg = new QMethodFormatTextDelegate(this);
    setItemDelegateForColumn(Method_Name, m_dg);
}

QMethodView::~QMethodView()
{
    delete ui;
}




void QMethodFormatTextDelegate::drawDecoration(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QPixmap &pixmap) const
{
}

void QMethodFormatTextDelegate::drawFocus(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const
{
}

void QMethodFormatTextDelegate::drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const
{
}
