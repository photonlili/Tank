#ifndef HANONKEYRING_H
#define HANONKEYRING_H

#include <QObject>
#include <QProcess>

class HanonKeyRing : public QObject
{
    Q_OBJECT
public:
    explicit HanonKeyRing(QObject *parent = 0);
    ~HanonKeyRing();

    void play(QString filename);

signals:

public slots:
private:
    QProcess* app;
};

void HanonKeyRingInstance(QObject* parent = 0);

#endif // HANONKEYRING_H
