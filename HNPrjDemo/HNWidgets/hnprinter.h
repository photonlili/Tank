#ifndef HNPRINTER_H
#define HNPRINTER_H

#include <QObject>
#include <QTableView>

class HNPrinter : public QObject
{
    Q_OBJECT

public:
    explicit HNPrinter(QObject* parent = 0);

    void addTable(QTableView* table);

public:
    static void htmltopdf(QString pdf, QString html);
    static void printpdf(QString pdf);

private:

};

#endif // HNPRINTER_H
