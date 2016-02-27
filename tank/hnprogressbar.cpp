#include "hnprogressbar.h"
#include "ui_hnprogressbar.h"
#include "QStylePainter"
#include "qtankpublic.h"
#include "QHBoxLayout"
#include "QSpacerItem"

HNProgressBar::HNProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNProgressBar)
{
    ui->setupUi(this);
    this->value = 0;
    this->min = 0;
    this->max = 100;
    this->back = "://theme/basic/bk_progress_background.png";
    this->trunk = "://theme/basic/bk_progress_chunk.png";
    ui->lbTrunk->setPixmap(QPixmap(this->trunk));
}

HNProgressBar::~HNProgressBar()
{
    delete ui;
}

void HNProgressBar::setPixMap(QString back, QString trunk)
{
    this->back = back;
    this->trunk = trunk;
    ui->lbTrunk->setPixmap(QPixmap(this->trunk));
}

void HNProgressBar::setValue(int value)
{
    this->value = value;
    int w = width() * value / (max-min);
    ui->lbTrunk->setFixedWidth(w);
    ui->lbTrunk->update();
}

void HNProgressBar::setRange(int min, int max)
{
    this->min = min;
    this->max = max;
}

void HNProgressBar::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    if(back.isEmpty())
        return;
    p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(back).pixmap(rect().size(), QIcon::Normal, QIcon::On));
}
