#ifndef HNREPORTER_H
#define HNREPORTER_H

#include <QObject>
#include "hngui-qt.h"

class HNReporter : public QObject
{
    Q_OBJECT
public:
    explicit HNReporter(QObject *parent = 0);

    //定氮仪简单打印需要的数据
    void insertSamplePaper(QString title, QStringList text, QTableView* table);
    //生成简单打印模板
    void GenerateTemplateSample();

    //定氮仪详细打印需要的数据
    //未实现

    //导出pdf
    void exportPdf(const QString &filename);

    int pageNum() { return pages; }
    void getPage(QGraphicsView* view, int num);

signals:

public slots:

protected:
    //在一次交易中规则不能改变，如果要改变需要等待下一阶段
    virtual void paintPage(int pagenum);

private:
    //输出
    QPrinter *printer;
    //显示
    QVector<QGraphicsScene> pageSceneVector;
    QGraphicsScene pageScene;

    //页面元素
    int pages;
    int leftMargin;
    int rightMargin;
    int topMargin;
    int bottomMargin;
    int spacing;
    int sceneZoomFactor;
    double columnZoomFactor;
    double columnMultiplier;

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
    QVector<QTextLength> colSizes;
    QAbstractItemModel* model;
    int lines;
    double rowHeight;
};

#endif // HNREPORTER_H
