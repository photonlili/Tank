#include "hnreporter.h"

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
    sceneZoomFactor=100;
    columnZoomFactor=0.65;

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
    footerText = tr("页");

    //header font
    headerFont = QApplication::font();;
    headerFont.setBold(true);
    headerFont.setUnderline(true);
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
    fmt =new  QFontMetrics(font);

    QRectF rect=printer->paperRect();
    QRectF rectNew = QRectF(0,0,rect.width() / printer->logicalDpiX() * sceneZoomFactor, rect.height() / printer->logicalDpiY() * sceneZoomFactor);
    pageScene.setSceneRect(rectNew);
}

void HNReporter::insertSamplePaper(QString title, QStringList text, QTableView *table)
{
    this->titleText = title;
    this->text = text;
    this->tableView = table;
    model = tableView->model();
}

void HNReporter::GenerateTemplateSample()
{
    //row height
    rowHeight = font.pointSize() + spacing;
    //count lines
    lines = ((pageScene.height()-topMargin-bottomMargin-headerSize-footerSize)/rowHeight);

    //get column widths
    for (int i=0; i<model->columnCount(); i++) {
        int colWidth=tableView->columnWidth(i);
        colSizes.append(QTextLength(QTextLength::FixedLength,colWidth));
    }

    //count pages
    int rowCount=model->rowCount();
    double div = rowCount / lines;
    int modulo = rowCount % lines;
    if (modulo == 0 ) {
        pages = QVariant(div).toInt();
    } else {
        div = div+1.0;
        pages = QVariant(div).toInt();
    }
    columnMultiplier=pageScene.width()/tableView->width()*columnZoomFactor;

}

void HNReporter::exportPdf(const QString &filename)
{
    // setup printer
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setOutputFileName(filename);

    // print pdf
    QPainter painter(printer);
    for (int pagenum=1; pagenum<=pages; pagenum++) {
        paintPage(pagenum);
        pageScene.render(&painter);
        if (pagenum < pages) {
            printer->newPage();
        }
    }
}

void HNReporter::getPage(QGraphicsView *view, int num)
{
    view->setScene(&pageScene);
    view->ensureVisible(0,0,10,10);
    paintPage(num);
    pageScene.addRect(0,0,pageScene.width(),pageScene.height(),QPen(Qt::black, 2.0));
}

void HNReporter::paintPage(int pagenum)
{
    //Delete all
    QList<QGraphicsItem*> L = pageScene.items();
    while ( ! L.empty() ) {
        pageScene.removeItem( L.first() );
        delete L.first();
        L.removeFirst();
    }


    //Table header
    int csize=0;
    for (int i=0; i<model->columnCount(); i++) {
        int logicalIndex=tableView->horizontalHeader()->logicalIndex(i);
        QString txt = model->headerData(logicalIndex,Qt::Horizontal,Qt::DisplayRole).toString();
        QGraphicsTextItem *item=new QGraphicsTextItem();
        item->setFont(headerFont);
        txt=headerFmt->elidedText(txt,Qt::ElideRight,QVariant(colSizes[logicalIndex].rawValue()).toInt()-8);
        item->setPlainText(txt);
        //item->moveBy((csize*columnMultiplier)+leftMargin,topMargin+headerSize+(spacing*2));
        item->moveBy(csize+leftMargin,topMargin+headerSize+(spacing*2));
        csize=csize+QVariant(colSizes[logicalIndex].rawValue()).toInt();
        pageScene.addItem(item);
    }

    //Table rows
    qreal dx,dy;
    QPen pen(Qt::gray, 1);
    QBrush brush(Qt::gray,Qt::SolidPattern);
    int borderAdjust=rowHeight / 5;

    for (int i=0; i<lines; i++) {
        csize=0;
        dy=(i*rowHeight)+topMargin+headerSize+(rowHeight*2);
        int modelIdxY=(pagenum-1)*lines+i;
        if (modelIdxY>=model->rowCount()) {
            break;
        }

        for (int j=0; j<model->columnCount(); j++) {
            int logicalIndex=tableView->horizontalHeader()->logicalIndex(j);
            int actColSize=QVariant(colSizes[logicalIndex].rawValue()).toInt();
            QString txt = model->data(model->index(modelIdxY,logicalIndex)).toString();
            QGraphicsTextItem *item=new QGraphicsTextItem();
            item->setFont(font);
            txt=fmt->elidedText(txt,Qt::ElideRight,actColSize-8);
            item->setPlainText(txt);
            //qreal dx=(csize*columnMultiplier)+leftMargin;
            dx=csize+leftMargin;
            item->moveBy(dx,dy);

            //rectangle
#if 1
            pageScene.addRect(dx,dy+borderAdjust,actColSize,rowHeight);
#else
            int modulo=i % 2;
            if (modulo==0) {
                //rectangle grey
                QGraphicsRectItem *rItem=pageScene.addRect(leftMargin,dy+borderAdjust,csize,rowHeight,pen,brush);
                rItem->setZValue(-1);
            }
#endif
            pageScene.addItem(item);
            csize=csize+actColSize;
        }

    }

    // Page header
    if (headerSize > 0) {
        //line
        pageScene.addLine(leftMargin,headerSize+topMargin,pageScene.width()-rightMargin, headerSize+topMargin,QPen(Qt::black, 1.0));

        //tile
        QGraphicsTextItem *titleItem=new QGraphicsTextItem();
        titleItem->setFont(titleFont);
        titleItem->setPlainText(headerText);
        int titleWidth=titleFmt->width(headerText);
        double xpos=(pageScene.width()/2)-(titleWidth/2);
        double ypos=(headerSize/2)-(titleFmt->height()/2);
        titleItem->moveBy(xpos,ypos+topMargin);
        pageScene.addItem(titleItem);

        //std text
        QGraphicsTextItem *item=new QGraphicsTextItem();
        item->setFont(font);
        item->setPlainText(headerStdText);
        item->moveBy(leftMargin,headerSize-rowHeight-spacing+topMargin);
        pageScene.addItem(item);
    }

    // footer
    if (footerSize > 0) {
        pageScene.addLine(leftMargin,pageScene.height()-footerSize-bottomMargin,pageScene.width()-rightMargin, pageScene.height()-footerSize-bottomMargin,QPen(Qt::black, 1.0));
        QGraphicsTextItem *item=new QGraphicsTextItem();
        item->setFont(font);
        item->setPlainText(footerText+QString::number(pages)+" / "+QString::number(pagenum));
        item->moveBy(leftMargin,pageScene.height()-footerSize-bottomMargin+spacing);
        pageScene.addItem(item);
    }
    //pageScene.update();
}
