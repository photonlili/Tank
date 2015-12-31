/*****************************************************
 * 这个类使用于操作次数少的简单场合
 * 文件大小也被QString所限制
 * ****************************************************/
#ifndef SIMPLEFILE_H
#define SIMPLEFILE_H

#include <QFile>
#include <QTextStream>
#include <QDataStream>

class QSimpleFile : public QFile
{
    Q_OBJECT
public:
    explicit QSimpleFile(QObject *parent = 0);

    void insertString( int position, const QString & str );

signals:

public slots:

};

#endif // SIMPLEFILE_H
