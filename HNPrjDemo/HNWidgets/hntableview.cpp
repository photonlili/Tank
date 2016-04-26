#include "hntableview.h"
#include "ui_hntableview.h"

HNTableView::HNTableView(QWidget *parent) :
    QTableView(parent),
    ui(new Ui::HNTableView)
{
    m_header = new HNHeaderView(Qt::Horizontal, this);
    //setHorizontalHeader(m_header);
    m_vheader = new HNHeaderView(Qt::Vertical, this);
    //setVerticalHeader(m_vheader);

    ui->setupUi(this);
}

HNTableView::~HNTableView()
{
    delete ui;
}

void HNTableView::setObjectName(const QString &name)
{
    QTableView::setObjectName(name);
    m_header->setObjectName(QString("%1_Header").arg(name));
    m_vheader->setObjectName(QString("%1_VHeader").arg(name));
}
