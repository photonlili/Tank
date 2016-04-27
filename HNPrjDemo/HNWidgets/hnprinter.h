#ifndef _HNPRINTER_H
#define _HNPRINTER_H

#include <QObject>

class HNPrinter : public QObject
{
    Q_OBJECT
public:
    explicit HNPrinter(QObject *parent = 0) :
        QObject(parent) {}

    static void print(QString pdf);

signals:

public slots:

};

#endif // HNPRINTER_H
