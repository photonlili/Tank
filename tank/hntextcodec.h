#ifndef _RECODE_H_
#define _RECODE_H_

#include <QFile>

enum EConvertMode
{
    EGBK2UTF8,
    EUTF82GBK,
};

class HNTextCodec
{
public:
    static int ConvertFile(QFile &inFile, QFile &outFile, EConvertMode mode);
    static int ConvertBytes(QByteArray &in, QByteArray &out, EConvertMode mode);

};

#endif // RECODE_H
