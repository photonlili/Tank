#include "txtrecode.h"


int QTxtRecode::ConvertFile(QFile &inFile, QFile &outFile, EConvertMode mode)
{
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return -2;

    QTextStream instream(&inFile);
    QTextStream outstream(&outFile);

    switch (mode) {
    case EGBK2UTF8:
        instream.setCodec("gb2312");
        outstream.setCodec("utf-8");
        break;
    case EUTF82GBK:
        instream.setCodec("utf-8");
        outstream.setCodec("gb2312");
        break;
    default:
        break;
    }

    outstream << instream.readAll();

    inFile.close();
    outFile.close();

    return 0;
}
