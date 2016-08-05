#include "hntextcodec.h"
#include <QTextCodec>
#include <QTextCodec>
#include <QFile>
#include <QTextStream>

int HNTextCodec::ConvertFile(QFile &inFile, QFile &outFile, EConvertMode mode)
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

int HNTextCodec::ConvertBytes(QByteArray &in, QByteArray &out, EConvertMode mode)
{
    QTextCodec *gbk = QTextCodec::codecForName("gb18030");
    QTextCodec *utf8 = QTextCodec::codecForName("utf-8");

    switch (mode) {
    case EGBK2UTF8:
    {
        //输入 gbk编码的 字符数组；
        QByteArray gbkbytes = in;
        //将 gbk格式的字节数组 转换为 unicode编码的 QStirng
        QString str = gbk->toUnicode(gbkbytes);
        //将 unicode字符串 转换到 utf-8编码的字符数组
        QByteArray utf8bytes = utf8->fromUnicode(str);
        //将 utf8格式的字符数组 输出
        out = utf8bytes;
        break;
    }
    case EUTF82GBK:
    {
        //输入utf-8格式的bytes；
        QByteArray utf8bytes = in;
        //将utf-8格式的字节数组 转换为 unicode编码的 QStirng
        QString str = utf8->toUnicode(utf8bytes);
        //将 unicode字符串 转换到 gbk编码的字符数组
        QByteArray gbkbytes = gbk->fromUnicode(str);
        //将 gbk格式的字符数组 输出
        out = gbkbytes;
        break;
    }
    default:
        break;
    }

    return 0;
}
