#include "quserlibraryview.h"
#include "ui_quserlibraryview.h"
#include "qtankdefine.h"
#include <QPainter>
#include "qtankpublic.h"

QUserLibraryView::QUserLibraryView(QWidget *parent) :
    QCTableView(parent),
    ui(new Ui::QUserLibraryView)
{
    ui->setupUi(this);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setHidden(true);
    verticalHeader()->setHidden(true);
    resizeColumnsToContents();
#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif
    horizontalHeader()->setStretchLastSection(true);
    setShowGrid(false);
    m_dg = new QUserLibraryFormatTextDelegate(this);
    setItemDelegateForColumn(Lib_Name, m_dg);
}

QUserLibraryView::~QUserLibraryView()
{
    delete ui;
}

void QUserLibraryFormatTextDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    QString txt = text;

    if(text == DB_EXTRACT)
        txt = tr("Extract");
    else if(text == DB_HANON)
        txt = tr("System");
    else if(text == DB_USER)
        txt = tr("User");

    painter->drawText(rect, Qt::AlignVCenter, txt);
}
