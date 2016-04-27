#include "hnsampleview.h"
#include "ui_hnsampleview.h"

HNSampleView::HNSampleView(QWidget *parent) :
    QTableView(parent),
    ui(new Ui::HNSampleView)
{
    ui->setupUi(this);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    horizontalHeader()->setStretchLastSection(true);

#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif
    setAlternatingRowColors(true);
}

HNSampleView::~HNSampleView()
{
    delete ui;
}
