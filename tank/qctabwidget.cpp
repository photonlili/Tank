#include "qctabwidget.h"
#include "ui_qctabwidget.h"
#include "qctabbar.h"
#include <QDebug>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionTabWidgetFrameV2>
#include "qtankpublic.h"

QCTabWidget::QCTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::QCTabWidget)
{
    m_bar = new QCTabBar(this);
    setTabBar(m_bar);

    ui->setupUi(this);
}

QCTabWidget::~QCTabWidget()
{
    delete ui;
}

QCTabBar *QCTabWidget::cTabBar()
{
    return m_bar;
}

void QCTabWidget::setObjectName(const QString &name)
{
    m_bar->setObjectName(QString("%1_bar").arg(name));
    QTabWidget::setObjectName(name);
}

void QCTabWidget::paintEvent(QPaintEvent *e)
{
    QTabWidget::paintEvent(e);
    return;

    QStylePainter p(this);
    p.setPen(QPen(Qt::red, 2));

    QStyleOptionTabWidgetFrameV2 opt;
    initStyleOption(&opt);

    pline() << opt.lineWidth;
    pline() << opt.midLineWidth;
    //opt.lineWidth = 9;


    //opt.rect = currentWidget()->rect();
    pline() << opt.tabBarRect;
    pline() << opt.rect;
    pline() << currentWidget()->rect();
    pline() << tabPosition();

    int left = 0, top = 0, width = 0, height = 0;
    switch( tabPosition() )
    {
    case QTabWidget::West:
        left = opt.tabBarRect.width();
        top = 0;
        width = opt.rect.width() - opt.tabBarRect.width();
        height = opt.rect.height();
        break;
    case QTabWidget::North:
        left = 0;
        top = opt.tabBarRect.height();
        width = opt.rect.width();
        height = opt.rect.height() - opt.tabBarRect.height();
        break;
    default:
        left = 0;
        top = 0;
        width = opt.rect.width();
        height = opt.rect.height();
        break;
    }

    QRect paneRect(left, top, width, height);

    pline() << paneRect;

    //p.drawRect(paneRect);
    pline() << e->type();
    if (tabPosition() == QTabWidget::North)
        p.drawItemPixmap(paneRect, Qt::AlignCenter, QPixmap("://theme/basic/bk_tab_content.png"));
}
