#ifndef QWIFIVIEW_H
#define QWIFIVIEW_H

#include "qctableview.h"
#include <QItemDelegate>
#include <QStylePainter>

class QWIFIViewTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QWIFIViewTextDelegate(QObject *parent = 0): QItemDelegate(parent), parent(parent) { }

private:
    QObject* parent;

    // QItemDelegate interface
protected:
    void drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const;

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
};

namespace Ui {
class QWIFIView;
}

class QWIFIView : public QCTableView
{
    Q_OBJECT

public:
    explicit QWIFIView(QWidget *parent = 0);
    ~QWIFIView();

private:
    Ui::QWIFIView *ui;
    QWIFIViewTextDelegate* dg;
};

#endif // QWIFIVIEW_H
