#ifndef QCHEADERVIEW_H
#define QCHEADERVIEW_H

#include <QHeaderView>

class QCHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit QCHeaderView(Qt::Orientation orientation = Qt::Horizontal, QWidget *parent = 0);

signals:

public slots:


    // QHeaderView interface
protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    QSize sectionSizeFromContents(int logicalIndex) const;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

private:
    Qt::Orientation ori;
};

#endif // QCHEADERVIEW_H
