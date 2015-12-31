#ifndef QMETHODVIEW_H
#define QMETHODVIEW_H

#include <QTableView>
#include <QItemDelegate>
#include <QPainter>
#include "qctableview.h"

class QMethodFormatTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QMethodFormatTextDelegate(QObject *parent = 0): QItemDelegate(parent), parent(parent) { }

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;

private:
    QObject* parent;

    // QItemDelegate interface
protected:
    void drawDecoration(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QPixmap &pixmap) const;
    void drawFocus(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const;
    void drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const;
};

namespace Ui {
class QMethodView;
}

class QMethodView : public QCTableView
{
    Q_OBJECT

public:
    explicit QMethodView(QWidget *parent = 0);
    ~QMethodView();

private:
    Ui::QMethodView *ui;
    QMethodFormatTextDelegate* m_dg;
};

#endif // QMETHODVIEW_H
