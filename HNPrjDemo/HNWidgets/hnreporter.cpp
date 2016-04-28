#include "hnreporter.h"
#include "HNDefine.h"

HNReporter::HNReporter(QObject *parent) :
    QObject(parent)
{
    //variables
    leftMargin=80;
    rightMargin=80;
    topMargin=40;
    bottomMargin=40;
    spacing=6;
    headerSize=60;
    footerSize=60;

    //setup printer
    printer= new QPrinter(QPrinter::HighResolution);
    printer->setFullPage(true);
    printer->setColorMode(QPrinter::Color);
    printer->setPaperSize(QPrinter::A4);
    printer->setOrientation(QPrinter::Portrait);
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOutputFileName("");

    QString date=QDate::currentDate().toString(QLocale().dateFormat());
    QString time=QTime::currentTime().toString(QLocale().timeFormat(QLocale::ShortFormat));
    headerStdText = date+"  "+time;
    headerText = tr("济南海能仪器股份有限公司");
    footerText = tr("第 1 页");

    //header font
    headerFont = QApplication::font();;
    headerFont.setBold(false);
    headerFont.setUnderline(false);
    headerFont.setPointSize(9);
    headerFmt =new QFontMetrics(headerFont);

    //title font
    titleFont= QApplication::font();
    titleFont.setPointSize(24);
    titleFont.setBold(false);
    titleFont.setUnderline(false);
    titleFmt = new QFontMetrics(titleFont);

    //normal font
    font=QApplication::font();
    fmt = new QFontMetrics(font);

    rectScene = printer->paperRect();

    rowHeight = font.pointSize() + spacing;
    xpos = leftMargin;
    xposr = rectScene.width() - rightMargin;
    ypos = headerSize + topMargin + rowHeight;
    ypos2 = rectScene.height() - footerSize - bottomMargin - rowHeight;
    dx = xpos;
    dy = ypos;

    lines = ((ypos2-ypos)/rowHeight);
}

void HNReporter::insertSamplePaper(QString title, QStringList text, QTableView *table)
{
    this->titleText = title;
    this->text = text;
    this->tableView = table;
    GenerateSampleTemplate();
}


void HNReporter::GenerateSampleTemplate()
{
    model = tableView->model();
    tableHeaderFont = tableView->horizontalHeader()->font();
    tableHeaderFmt = new QFontMetrics(tableHeaderFont);
    tableContentFont = tableView->font();
    tableContentFmt = new QFontMetrics(tableContentFont);

    //get column widths
    for (int i=0; i<model->columnCount(); i++) {
        int colWidth=tableView->columnWidth(i);
        colSizes.append(QTextLength(QTextLength::FixedLength,colWidth));
    }

    currentTableRow = 0;
    currentPage = 0;

    //Delete all
    while ( ! pageSceneVector.isEmpty() ) {
        QGraphicsScene* pageScene = pageSceneVector.first();
        pageScene->clear();
        delete pageScene;
        pageSceneVector.remove(0);
    }

    for(int i = 1; ; i++)
    {
        pageScene = new QGraphicsScene(rectScene);
        //header
        paintPageHeader();
        //body
        bool ret = paintSamplePage(i);
        //footer
        paintPageFooter();

        pageSceneVector.append(pageScene);
        if(ret == true)
            break;
    }
}


bool HNReporter::paintSamplePage(int pagenum)
{

    int sdx=0;
    int sdy=0;
    int tableRowHeight = 0;

    if(pagenum == 1)
    {
        paintPageTitle();
        dy = ypos + titleFmt->height() + rowHeight;
    }
    else
        dy=sdy+ypos;


    //Table header
    dx=sdx+xpos;

    for (int i=0; i<model->columnCount(); i++) {
        int logicalIndex=tableView->horizontalHeader()->logicalIndex(i);
        int actColSize=QVariant(colSizes[logicalIndex].rawValue()).toInt();
        tableRowHeight = tableView->horizontalHeader()->height();
        QString txt = model->headerData(logicalIndex,Qt::Horizontal,Qt::DisplayRole).toString();
        QGraphicsTextItem *item=new QGraphicsTextItem();
        item->setFont(tableHeaderFont);
        txt=tableHeaderFmt->elidedText(txt, Qt::ElideRight, actColSize-8);
        item->setPlainText(txt);
        item->moveBy(dx, dy);
        pageScene->addRect(dx,dy,actColSize,tableRowHeight);
        pageScene->addItem(item);
        dx += actColSize;
    }

    //Table rows
    QPen pen(Qt::gray, 1);
    QBrush brush(Qt::gray,Qt::SolidPattern);
    bool ret = true;
    int sypos = (ypos2-dy)/tableRowHeight;
    for (int i=0; i<sypos; i++) {
        dx=sdx+xpos;
        dy += tableRowHeight;
        if(dy + tableRowHeight > ypos2)
        {
            ret = false;
            break;
        }

        if (currentTableRow>=model->rowCount()) {
            ret = true;
            break;
        }

        tableRowHeight = tableView->rowHeight(currentTableRow);
        for (int j=0; j<model->columnCount(); j++) {
            int logicalIndex=tableView->horizontalHeader()->logicalIndex(j);
            int actColSize=QVariant(colSizes[logicalIndex].rawValue()).toInt();
            QString txt = model->data(model->index(currentTableRow,logicalIndex)).toString();
            QGraphicsTextItem *item=new QGraphicsTextItem();
            item->setFont(tableContentFont);
            txt=tableContentFmt->elidedText(txt,Qt::ElideRight,actColSize-8);
            item->setPlainText(txt);
            item->moveBy(dx,dy);

            //rectangle
#if 1
            pageScene->addRect(dx,dy,actColSize,tableRowHeight);
#else
            int modulo=i % 2;
            if (modulo==0) {
                //rectangle grey
                QGraphicsRectItem *rItem=pageScene->addRect(leftMargin,dy+borderAdjust,csize,rowHeight,pen,brush);
                rItem->setZValue(-1);
            }
#endif
            pageScene->addItem(item);
            dx+=actColSize;
        }
        currentTableRow++;
    }

    currentPage++;

    return ret;
}

void HNReporter::paintPageHeader()
{
    // Page header
    if (headerSize > 0)
    {
        //line
        pageScene->addLine(xpos, ypos-rowHeight, xposr, ypos-rowHeight, QPen(Qt::black, 1.0));

        //页眉
        QGraphicsTextItem *headerItem=new QGraphicsTextItem();
        headerItem->setFont(headerFont);
        headerItem->setPlainText(headerText);
        headerItem->moveBy(xpos, ypos-(rowHeight)*2 - spacing);
        pageScene->addItem(headerItem);

        //std text
        QGraphicsTextItem *item=new QGraphicsTextItem();
        item->setFont(headerFont);
        item->setPlainText(headerStdText);
        item->moveBy(xposr - headerFmt->width(headerStdText), ypos-(rowHeight)*2 - spacing);
        pageScene->addItem(item);
    }
}

void HNReporter::paintPageFooter()
{
    // footer
    if (footerSize > 0) {
        pageScene->addLine(xpos, ypos2 + rowHeight, xposr, ypos2 + rowHeight, QPen(Qt::black, 1.0));
        QGraphicsTextItem *item=new QGraphicsTextItem();
        item->setFont(font);
        footerText = tr("第 ") + QString::number(currentPage) + tr(" 页");
        item->setPlainText( footerText );
        item->moveBy(xposr - fmt->width(footerText), ypos2 + (rowHeight)*2);
        pageScene->addItem(item);
    }
}

void HNReporter::paintPageTitle()
{
    //title
    QGraphicsTextItem *titleItem=new QGraphicsTextItem();
    titleItem->setFont(titleFont);
    titleItem->setPlainText(titleText);
    int titleWidth=titleFmt->width(titleText);
    titleItem->moveBy((pageScene->width()/2)-(titleWidth/2), ypos);
    pageScene->addItem(titleItem);
}


void HNReporter::exportPdf(const QString &filename)
{
    // setup printer
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOutputFileName(filename);

    // print pdf
    QPainter painter(printer);

    foreach (pageScene, pageSceneVector) {
        QGraphicsView v;
        //v.setSceneRect(rectScene);
        v.setScene(pageScene);
        v.show();

        qreal sourceDpiX = v.logicalDpiX();
        qreal sourceDpiY = v.logicalDpiY();
        const qreal dpiScaleX = qreal(printer->logicalDpiX()) / sourceDpiX;
        const qreal dpiScaleY = qreal(printer->logicalDpiY()) / sourceDpiY;
        // scale to dpi
        //painter.scale(dpiScaleX, dpiScaleY);

        QSizeF scaledPageSize = v.rect().size();
        scaledPageSize.rwidth() *= dpiScaleX;
        scaledPageSize.rheight() *= dpiScaleY;
        const QSizeF printerPageSize(printer->pageRect().size());
        // scale to page
        painter.scale(printerPageSize.width() / scaledPageSize.width(), printerPageSize.height() / scaledPageSize.height());

        v.render(&painter);

        break;
        if(pageScene != pageSceneVector.last())
            printer->newPage();
    }
}

QGraphicsScene* HNReporter::getPage(int num)
{
    if(num < 1 || num > pageSceneVector.size())
        return NULL;
    return pageSceneVector.at(num-1);
}
