#ifndef QUSERSETVIEW_H
#define QUSERSETVIEW_H

#include "qctableview.h"
#include <QItemDelegate>

class QUserSetViewTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QUserSetViewTextDelegate(QObject *parent = 0): QItemDelegate(parent) { }

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
};

namespace Ui {
class QUserSetView;
}

class QUserSetView : public QCTableView
{
    Q_OBJECT

public:
    explicit QUserSetView(QWidget *parent = 0);
    ~QUserSetView();

private:
    Ui::QUserSetView *ui;
    QUserSetViewTextDelegate* m_dg;
};

#endif // QUSERSETVIEW_H
