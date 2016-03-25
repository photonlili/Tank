#include "hnprogressbar.h"
#include "ui_hnprogressbar.h"
#include "QStylePainter"
#include "HNDefine.h"
#include "QHBoxLayout"
#include "QSpacerItem"

HNProgressBar::HNProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HNProgressBar)
{
    ui->setupUi(this);
    m_value = m_min = 0;
    m_max = 100;
    m_back = "://theme/basic/bk_progress_background.png";
    m_trunk = "://theme/basic/bk_progress_chunk.png";
    ui->lbTrunk->setPixmap(QPixmap(m_trunk));
    ui->widgetBack->setPixmap(m_back);
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
    ui->widgetBack->setPixmap(m_back);
}

void HNProgressBar::setValue(int value)
{
    m_value = value;
    int w = width() * value / (m_max-m_min);
    int h = height();
    ui->lbTrunk->setFixedSize(w, h);
    ui->lbTrunk->update();
}

void HNProgressBar::setRange(int min, int max)
{
    m_min = min;
    m_max = max;
}

