#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <qstring.h>
#include "qdebug.h"
#include "QRect"

//自定义组件的公共部分
enum
{
    BTN_NORMAL = 0,
    BTN_UNCHECK = BTN_NORMAL,
    BTN_PRESS = 1,
    BTN_CHECK = BTN_PRESS,
    BTN_HOVER,
    BTN_DISABLE,
    BTN_MAX,
};

typedef struct tagBtnIconTable
{
    QString pixmap[BTN_MAX];

    tagBtnIconTable();
    QString pixMap(int index);
    void setPixMap(int index, QString pix);
    void initNormal(QString normal, QString press);
    void initCheck(QString uncheck, QString check);
    void initOther(QString hover, QString disable);
    const QString& operator[] (int index) const;
    QString &operator [](int index);
}TBtnIconTable;

enum {
    ESSID_STATUS = 0,
    ESSID_NAME,//SSID
    ESSID_TYPE,
    ESSID_ENCRYP,
    ESSID_PASS,
    ESSID_BSSID,
    ESSID_FREQ,
    ESSID_SIGNAL,
    ESSID_FLAG,
    ESSID_MAX,
};

typedef struct tagWifi
{
    QString wifi[ESSID_MAX];

    bool isValid();

#ifdef __MIPS_LINUX__
    tagWifi& operator= (tagWifi& w);
#else
    tagWifi &operator=(const tagWifi &w);
#endif

    const QString &operator[] (int index) const;

    QString& operator[] (int index);
}TWifi;


QByteArray &operator<<(QByteArray &l, const quint8 r);

QByteArray &operator<<(QByteArray &l, const quint16 r);

QByteArray &operator<<(QByteArray &l, const quint32 r);

QByteArray &operator<<(QByteArray &l, const QByteArray &r);

QByteArray &operator>>(QByteArray &l, quint8& r);

QByteArray &operator>>(QByteArray &l, quint16& r);

QByteArray &operator>>(QByteArray &l, qint8& r);

QByteArray &operator>>(QByteArray &l, qint16& r);

QByteArray &operator>>(QByteArray &l, quint32& r);

QByteArray &operator>>(QByteArray &l, QByteArray& r);

#endif // _COMPONENT_H
