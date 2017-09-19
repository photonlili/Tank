#include "qusersetview.h"
#include "ui_qusersetview.h"
#include "qtankdefine.h"
#include "qtankgui.h"
#include "qtankpublic.h"
#include "qcomponent.h"
QUserSetView::QUserSetView(QWidget *parent) :
    QCTableView(parent),
    ui(new Ui::QUserSetView)
{
    ui->setupUi(this);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setHidden(false);
    verticalHeader()->setHidden(true);
    resizeColumnsToContents();
#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#else
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#endif
    setShowGrid(false);

    m_dg = new QUserSetViewTextDelegate(this);
    setItemDelegateForColumn(Auth_Id, m_dg);
}

QUserSetView::~QUserSetView()
{
    delete ui;
}


void QUserSetViewTextDelegate::drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const
{
    QSettings set;
    QString id = set.value("DefaultLogin").toString();

    if(id == text)
        painter->drawImage(rect, QImage("://theme/basic/bk_sel.png"));
}
