#include "hnreport.h"

HNReport::HNReport(QObject *parent) :
    HNWord(parent)
{
}

void HNReport::createSampleReport(const QString &head, const QString &foot, const QString &title, const QTableView *table)
{
    initWord();
    setHeaderText(head);
    setFooterText(foot);
    addText(title, titleFont());
    //addText("");
    addText("试验结果", title2Font(), Qt::AlignLeft);
    //addText("");
    addTable(table);
    addSignoffText("打印人:___________");
}

void HNReport::CreateComplexReport(const QString &head, const QString &foot,
                                     const QString &title, const QList<QTableView *> &table)
{
    initWord();
    setHeaderText(head);
    setFooterText(foot);
    addText(title, titleFont());
    //addText("");
    addText("试验结果", title2Font(), Qt::AlignLeft);
    QListIterator<QTableView*> itor(table);
    while(itor.hasNext())
    {
        QTableView* view = itor.next();
        addTable(view);
        addText("");
    }
    addSignoffText("打印人:___________");
}


HNReport *HNReportInstance(QObject *parent)
{
    static HNReport* r = new HNReport(parent);
    return r;
}

