#ifndef QSTAGEVIEW_H
#define QSTAGEVIEW_H

#include <QTableView>
#include "qctableview.h"
#include <QItemDelegate>

class QStageFormatTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QStageFormatTextDelegate(QObject *parent = 0): QItemDelegate(parent) { }

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;

private:

    // QItemDelegate interface
protected:
    void drawDecoration(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QPixmap &pixmap) const;
    void drawFocus(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const;
    void drawCheck(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, Qt::CheckState state) const;
};

namespace Ui {
class QStageView;
}

class QStageView : public QCTableView
{
    Q_OBJECT

public:
    explicit QStageView(QWidget *parent = 0);
    ~QStageView();

private:
    Ui::QStageView *ui;
    QStageFormatTextDelegate* dg;
    QStageFormatTextDelegate* dgHold;
};

#endif // QSTAGEVIEW_H
