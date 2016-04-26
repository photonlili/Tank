#include "hnsampleview.h"
#include "ui_hnsampleview.h"

HNSampleView::HNSampleView(QWidget *parent) :
    HNTableView(parent),
    ui(new Ui::HNSampleView)
{
    ui->setupUi(this);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
#ifdef __MIPS_LINUX__
    setFocusPolicy(Qt::NoFocus);
#endif
}

HNSampleView::~HNSampleView()
{
    delete ui;
}
