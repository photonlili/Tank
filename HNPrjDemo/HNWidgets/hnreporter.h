#ifndef HNREPORTER_H
#define HNREPORTER_H

#include <QObject>
#include "hngui-qt.h"

class HNReportEngine : public QObject
{
    Q_OBJECT
public:
    explicit HNReportEngine(QObject *parent = 0);


    //定氮仪简单打印需要的数据
    void insertSamplePaper(QString title, QStringList text, QTableView* table);

    //定氮仪详细打印需要的数据
    //未实现

    //导出pdf
    void exportPdf(const QString &filename);
    int pageNum() { return pageSceneVector.size(); }
    //单页浏览
    QGraphicsScene *getPage(int num);

signals:

public slots:

protected:
    //生成简单打印模板
    virtual void GenerateSampleTemplate();
    //在一次交易中规则不能改变，如果要改变需要等待下一阶段
    virtual bool paintSamplePage(int pagenum);

    virtual void paintPageHeader();
    virtual void paintPageFooter();
    virtual void paintPageTitle();

private:
    //输出
    QPrinter *printer;
    //对页面元素高度不能迅速统计的场景
    QVector<QGraphicsScene*> pageSceneVector;
    QGraphicsScene* pageScene;

    //页面元素
    int xpos, xposr, ypos, ypos2;
    int dx, dy;
    QRectF rectScene;
    int currentPage;
    int currentTableRow;
    int leftMargin;
    int rightMargin;
    int topMargin;
    int bottomMargin;
    int spacing;

    //页眉
    int headerSize;
    QString headerText;
    QFont headerFont;
    QFontMetrics *headerFmt;
    QString headerStdText;
    //页脚
    int footerSize;
    QString footerText;
    //标题
    QString titleText;
    QFont titleFont;
    QFontMetrics *titleFmt;
    //正文
    QStringList text;
    QFont font;
    QFontMetrics *fmt;
    //表格
    QTableView *tableView;
    QFont tableHeaderFont;
    QFont tableContentFont;
    QFontMetrics *tableHeaderFmt;
    QFontMetrics *tableContentFmt;
    QVector<QTextLength> colSizes;
    QAbstractItemModel* model;
    int lines;
    double rowHeight;
};

#endif // HNREPORTER_H
