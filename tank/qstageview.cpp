#include "qstageview.h"
#include "ui_qstageview.h"
#include "qcheaderview.h"

QStageView::QStageView(QWidget *parent) :
    QCTableView(parent),
    ui(new Ui::QStageView)
{
    ui->setupUi(this);

    setSelectionMode(QAbstractItemView::NoSelection);
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
}

QStageView::~QStageView()
{
    delete ui;
}
