#include "qcomponent.h"


QByteArray &operator<<(QByteArray &l, const quint8 r)
{
    return l.append(r);
}


QByteArray &operator<<(QByteArray &l, const quint16 r)
{
    return l<<quint8(r>>8)<<quint8(r);
}


QByteArray &operator<<(QByteArray &l, const quint32 r)
{
    return l<<quint16(r>>16)<<quint16(r);
}


QByteArray &operator<<(QByteArray &l, const QByteArray &r)
{
    return l.append(r);
}


QByteArray &operator>>(QByteArray &l, quint8 &r)
{
    r = l.left(sizeof(quint8))[0];
    return l.remove(0, sizeof(quint8));
}


QByteArray &operator>>(QByteArray &l, quint16 &r)
{
    quint8 r0 = 0, r1 = 0;
    l >> r0 >> r1;
    r = ( r0 << 8 ) | r1;
    return l;
}


QByteArray &operator>>(QByteArray &l, quint32 &r)
{
    quint8 r0 = 0, r1 = 0, r2 = 0, r3 = 0;
    l >> r0 >> r1 >> r2 >> r3;
    r = ( r0 << 24 ) | ( r1 << 16 ) | ( r2 << 8 ) | r3;
    return l;
}


QByteArray &operator>>(QByteArray &l, QByteArray &r)
{
    r = l.left(r.size());
    return l.remove(0, r.size());
}

tagBtnIconTable::tagBtnIconTable()
{
    pixmap[BTN_NORMAL] = "://theme/basic/bt_bt_normal.png";
    pixmap[BTN_UNCHECK] = "://theme/basic/bt_bt_normal.png";
#ifdef __MIPS_LINUX__
    pixmap[BTN_HOVER] = "://theme/basic/bt_bt_hover.png";
    pixmap[BTN_CHECK] = "://theme/basic/bt_bt_hover.png";
    pixmap[BTN_PRESS] = "://theme/basic/bt_bt_hover.png";
#else
    pixmap[BTN_HOVER] = "://theme/basic/bt_bt_hover.png";
    pixmap[BTN_CHECK] = "://theme/basic/bt_bt_check.png";
    pixmap[BTN_PRESS] = "://theme/basic/bt_bt_press.png";
#endif
    pixmap[BTN_DISABLE] = "://theme/basic/bt_bt_disable.png";
}

QString tagBtnIconTable::pixMap(int index)
{
    if(index < 0 || index + 1 > BTN_MAX)
        return pixmap[BTN_NORMAL];
    return pixmap[index];
}

void tagBtnIconTable::setPixMap(int index, QString pix)
{
    if(index < 0 || index + 1 > BTN_MAX)
        return;
    pixmap[index] = pix;
}

void tagBtnIconTable::initNormal(QString normal, QString press)
{
    if(!normal.isEmpty())
        pixmap[BTN_NORMAL] = normal;
    if(!press.isEmpty())
        pixmap[BTN_PRESS] = press;
}

void tagBtnIconTable::initCheck(QString uncheck, QString check)
{
    if(!uncheck.isEmpty())
        pixmap[BTN_UNCHECK] = uncheck;
    if(!check.isEmpty())
        pixmap[BTN_CHECK] = check;
}

void tagBtnIconTable::initOther(QString hover, QString disable)
{
    if(!hover.isEmpty())
        pixmap[BTN_HOVER] = hover;
    if(!disable.isEmpty())
        pixmap[BTN_DISABLE] = disable;
}

QString &tagBtnIconTable::operator [](int index)
{
    if(index < 0 || index >= BTN_MAX)
        return pixmap[0];

    return pixmap[index];
}

const QString &tagBtnIconTable::operator[](int index) const
{
    return operator [](index);
}


bool tagWifi::isValid()
{
    return wifi[ESSID_BSSID].isEmpty() ? false : true;
}

#ifdef __MIPS_LINUX__
tagWifi& tagWifi::operator= (tagWifi& w)
#else
tagWifi &tagWifi::operator=(const tagWifi &w)
#endif
{
    for(int i = ESSID_STATUS; i < ESSID_MAX; i++)
        wifi[i] = w[i];
    return *this;
}

QString &tagWifi::operator[](int index)
{
    if(index < ESSID_STATUS || index >= ESSID_MAX)
        return wifi[0];

    return wifi[index];
}

const QString &tagWifi::operator[](int index) const
{
    return operator [](index);
}

QByteArray &operator>>(QByteArray &l, qint8 &r)
{
    r = l.left(sizeof(qint8))[0];
    return l.remove(0, sizeof(qint8));

    quint8 a = 0;
    l >> a;
    r = qint8(a);
    return l;
}

QByteArray &operator>>(QByteArray &l, qint16 &r)
{
#if 0
    quint16 a = 0;
    l >> a;
    r = qint16(a);
    return l;
#endif
    qint8 r0 = 0;
    quint8 r1 = 0;
    l >> r0 >> r1;
    r = ( r0 << 8 ) | r1;
    return l;
}
