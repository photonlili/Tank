#include "hndialog.h"
#include "ui_hndialog.h"
#include "QPainter"
#include "QPainterPath"
#include "HNDefine.h"

HNDialog::HNDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HNDialog)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭 show的功能强大起来 可以使用输入法
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());
    setAttribute(Qt::WA_TranslucentBackground, true);
    QPalette plt = palette();
    plt.setColor(QPalette::Normal, QPalette::Shadow, QColor(72, 72, 72, 255));
    plt.setColor(QPalette::Normal, QPalette::Window, QColor(255, 255, 255, 255));
    setPalette(plt);
}

HNDialog::~HNDialog()
{
    delete ui;
}

void HNDialog::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QPalette plt = palette();

    //半透明背景
    QPen pen;
    int border = 1;
    int radius = 3;
    pen.setWidth(border);
    pen.setColor(plt.color(QPalette::Normal, QPalette::Shadow));
    p.setPen(pen);
    p.setBrush(plt.brush(QPalette::Normal, QPalette::Window));
    p.drawRoundedRect(QRect(3, 3, rect().width()-border-3, rect().height()-border-3), radius, radius);
}
