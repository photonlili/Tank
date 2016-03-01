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
    m_value = 0;
    m_min = 0;
    m_max = 100;
    m_back = "://theme/basic/bk_progress_background.png";
    m_trunk = "://theme/basic/bk_progress_chunk.png";
    ui->lbTrunk->setPixmap(QPixmap(m_trunk));
}

HNProgressBar::~HNProgressBar()
{
    delete ui;
}

void HNProgressBar::setPixMap(QString back, QString trunk)
{
    m_back = back;
    m_trunk = trunk;
    ui->lbTrunk->setPixmap(QPixmap(m_trunk));
}

void HNProgressBar::setValue(int value)
{
    m_value = value;
    int w = width() * value / (m_max-m_min);
    ui->lbTrunk->setFixedWidth(w);
    ui->lbTrunk->update();
}

void HNProgressBar::setRange(int min, int max)
{
    m_min = min;
    m_max = max;
}

void HNProgressBar::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    if(m_back.isEmpty())
        return;
    p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(m_back).pixmap(rect().size(), QIcon::Normal, QIcon::On));
}
