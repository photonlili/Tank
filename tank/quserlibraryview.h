#ifndef QUSERLIBRARYVIEW_H
#define QUSERLIBRARYVIEW_H

#include "qctableview.h"
#include <QItemDelegate>

class QUserLibraryFormatTextDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    QUserLibraryFormatTextDelegate(QObject *parent = 0): QItemDelegate(parent), parent(parent) { }

    // QItemDelegate interface
protected:
    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;

private:
    QObject* parent;
};

namespace Ui {
class QUserLibraryView;
}

class QUserLibraryView : public QCTableView
{
    Q_OBJECT

public:
    explicit QUserLibraryView(QWidget *parent = 0);
    ~QUserLibraryView();

private:
    Ui::QUserLibraryView *ui;
    QUserLibraryFormatTextDelegate* m_dg;
};

#endif // QUSERLIBRARYVIEW_H
