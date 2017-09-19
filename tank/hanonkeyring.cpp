#include "hanonkeyring.h"
#include "qtankdefine.h"
#include "qtankpublic.h"

HanonKeyRing::HanonKeyRing(QObject *parent) : QObject(parent)
{
    app = new QProcess(this);

    QString filename = "";
    int width=0, height=0, wid=0;

    QString mppath="mplayer";
    QStringList mpargs;
    mpargs << "-slave";
    mpargs << "-quiet";
    mpargs << "-idle";
    mpargs << "-zoom";
    mpargs << "-x";
    mpargs << QString("%1").arg(width);
    mpargs << "-y";
    mpargs << QString("%1").arg(height);
    mpargs << "-wid";
    mpargs << QString::number(wid);
    mpargs << filename;

    app->setProcessChannelMode(QProcess::SeparateChannels);
    app->start(mppath, mpargs, QIODevice::Truncate|QIODevice::ReadWrite);

    if(!app->waitForStarted(3000))
        pline() << "mpp2 start fail :(";

    pline() << "mpp2 start success :)";

}

HanonKeyRing::~HanonKeyRing()
{
    char buf[256]= {0};
    sprintf(buf, "quit\n");
    app->write(buf);
    app->close();
}

void HanonKeyRing::play(QString filename)
{
    char buf[256]= {0};
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    sprintf(buf, "load %s\n", filename.toAscii().constData());
#else
    sprintf(buf, "load %s\n", filename.toLocal8Bit().constData());
#endif
    app->write(buf);
}


void HanonKeyRingInstance(QObject *parent)
{
    static HanonKeyRing* p = new HanonKeyRing(parent);
    p->play(QString("%1/%2").arg(AV_PATH).arg("ring.wav"));
}
