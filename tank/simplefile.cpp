#include "simplefile.h"
#include <QDebug>

QSimpleFile::QSimpleFile(QObject *parent) :
    QFile(parent)
{
}

void QSimpleFile::insertString(int position, const QString &str)
{
    reset();
    QString strFile = readAll();
    strFile.insert(position, str);
    reset();
    write(strFile.toUtf8());
    flush();
}
