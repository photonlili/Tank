#ifndef QCTABWIDGET_H
#define QCTABWIDGET_H

#include <QTabWidget>
#include "qctabbar.h"

namespace Ui {
class QCTabWidget;
}

class QCTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit QCTabWidget(QWidget *parent = 0);
    ~QCTabWidget();

    QCTabBar* cTabBar();
    void setObjectName(const QString &name);
    void setToolTipDuration(int index){;}

protected:
    //void showEvent(QShowEvent *);
    //void resizeEvent(QResizeEvent *);
    //void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
    //void changeEvent(QEvent *);
    //bool event(QEvent *);
    //void initStyleOption(QStyleOptionTabWidgetFrame *option) const;

private:
    Ui::QCTabWidget *ui;

    QCTabBar* m_bar;
};

#endif // QCTABWIDGET_H
