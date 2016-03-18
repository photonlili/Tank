#include "qcheaderview.h"
#include <QPainter>
#include "qtankpublic.h"
#include <QStylePainter>
#include <QPaintEvent>
#include <QStandardItemModel>
#include <QStringListModel>

QCHeaderView::QCHeaderView(Qt::Orientation orientation, QWidget *parent) :
    QHeaderView(orientation, parent), ori(orientation)
{
    setFocusPolicy(Qt::NoFocus);
}

void QCHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->drawText(rect, Qt::AlignCenter, model()->headerData(logicalIndex, ori).toString());
}

QSize QCHeaderView::sectionSizeFromContents(int logicalIndex) const
{
    // 文字宽度 不是section宽度
    return QHeaderView::sectionSizeFromContents(logicalIndex);
}

void QCHeaderView::paintEvent(QPaintEvent *e)
{
    QStylePainter p(this->viewport());

    for(int i = 0; i < model()->columnCount(); i++)
    {
        if(isSectionHidden(i))
            continue;
        QRect rect(sectionPosition(i), 0, sectionSize(i), height());
        paintSection(&p, rect, i);
    }

    return;
}
