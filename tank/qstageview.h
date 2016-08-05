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

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *);
    void keyPressEvent(QKeyEvent *);

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void keyReleaseEvent(QKeyEvent *);
};

#endif // QSTAGEVIEW_H
