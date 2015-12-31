#ifndef QCTABBAR_H
#define QCTABBAR_H

#include <QTabBar>
#include <QList>
#include "qcomponent.h"

class QCTabBar : public QTabBar
{
    Q_OBJECT

public:
    explicit QCTabBar(QWidget *parent = 0);

    void tabPixmap(int index, QImage &icon, QImage &iconSel);
    void setTabPixmap(int index, const QString& icon = QString(), const QString &iconSel = QString());

protected:
    void paintEvent(QPaintEvent *);
    inline bool verticalTabs();

public slots:

private:
    QList<TBtnIconTable> iconList;
};

#endif // QCTABBAR_H
