#include "qcpushbutton.h"
#include "ui_qcpushbutton.h"
#include <QStylePainter>
#include <QMouseEvent>
#include "qtankpublic.h"

QCPushButton::QCPushButton(QWidget *parent) :
    QPushButton(parent),
    ui(new Ui::QCPushButton)
{
    ui->setupUi(this);
    state = BTN_NORMAL;
}

QCPushButton::~QCPushButton()
{
    delete ui;
}

void QCPushButton::paintEvent(QPaintEvent *e)
{
    QStylePainter p(this);

    bool enabled = isEnabled();

#ifdef __MIPS_LINUX__
    //pline() << this << e->type() << state;
#endif

#if 0
    //不会报告ｌｉｂｐｎｇｗａｒｎｉｎｇ
    QIcon::Mode iconFlag = QIcon::Normal;
    if(BTN_PRESS == state)
        iconFlag = QIcon::Selected;
    if(!enabled)
        iconFlag = QIcon::Disabled;
    p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(m_pixmap[state]).pixmap(rect().size(), iconFlag, QIcon::On));
#else
    //以下方法会导致图片失真 可以控制大小 可以控制图片状态 ｓｃａｌｅｄ函数打印ｌｉｂｐｎｇｗａｒｎｉｎｇ
    QImage image(m_pixmap[state]);
    p.drawItemPixmap(rect(), Qt::AlignCenter, QPixmap::fromImage(image.scaled(rect().size(), Qt::IgnoreAspectRatio)));
#endif

    QStyleOptionButton opt;
    initStyleOption(&opt);
    p.drawItemText(rect(), Qt::AlignCenter, opt.palette, enabled, text());
}

void QCPushButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        if(isEnabled())
            state = BTN_PRESS;
        QApplication::beep();
        //pline() << state;
    }
    QPushButton::mousePressEvent(e);
}

void QCPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
#ifdef __MIPS_LINUX__
        if(isEnabled())
            state = BTN_NORMAL;
        //pline() << state;
        update();
#else
        if(rect().contains(e->pos()))
            state = BTN_HOVER;
        else
            state = BTN_NORMAL;
#endif
    }
    QPushButton::mouseReleaseEvent(e);
}

void QCPushButton::enterEvent(QEvent *e)
{
    if(isEnabled())
        state = BTN_HOVER;
    QPushButton::enterEvent(e);
}

void QCPushButton::leaveEvent(QEvent *e)
{
    if(isEnabled())
    state = BTN_NORMAL;
    QPushButton::leaveEvent(e);
}

void QCPushButton::enabledChange(bool enabled)
{
    state = isEnabled() ? BTN_NORMAL : BTN_DISABLE;
    QPushButton::enabledChange(enabled);
}
