#ifndef _RECODE_H_
#define _RECODE_H_

#include <QTextCodec>
#include <QFile>
#include <QTextStream>

enum EConvertMode
{
    EGBK2UTF8,
    EUTF82GBK,
};

class QTxtRecode : QTextCodec
{
public:
    static int ConvertFile(QFile &inFile, QFile &outFile, EConvertMode mode);

};

#endif // RECODE_H
