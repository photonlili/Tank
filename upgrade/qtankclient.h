/**************************************************
 * QTankClient
 * 在一个工程当中仅仅存在一个实例，通过调用HNClient实现。
 **************************************************/
#ifndef QTANKCLIENT_H
#define QTANKCLIENT_H

#include <QTcpSocket>
#include <QHostInfo>
#include "qtankmessage.h"
#include <QTimer>
#include <QThread>
#include "qtankpublic.h"

#define TANK_Q_TCP_SOCKET 0
#define TANK_Q_SOCKET 1
#define TANK_Q_THREAD 0

class QTankClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit QTankClient(QObject *parent = 0);
    virtual ~QTankClient();

    QTCloudListDirResult& getDirs() { return m_dirs; }
    QTCloudListFileResult& getFiles() { return m_files; }
signals:
    void signalDownSucc();
    void signalListDirOK();
    void signalListFileOK();
    void signalLogined();
    void signalUploadSucc(QString code);
public slots:
    //服务器需要解析收到的命令，而此处不需要，所以客户端和服务器代码分开编写。
    void sendHeatBeatMessage();
    void sendLoginMessage();
    void sendLogoutMessage();
    void sendListDirectory(QString code = "");
    void sendAddDirectory();
    void sendModDirectory();
    void sendDelDirectory();
    void sendListFiles(QString code = "001");
    void sendDelFile(QString code, QString id);
    void sendListPubDirectory();
    void sendListPubFiles();
    void sendDownDevFiles(QString path, QString id, QString local);
    void sendDownPubFiles();
    void sendCancelDown();
    void sendUploadFile(QString code, QString path, QString filename, int filelength);
    void sendCancelUpload();
private:
    enum {
        E_LIANTONG,
        E_DIANXIN,
        E_DOMAIN,
        E_CONNMAX,
    };
    //TODO:如果文件传输影响到了UI线程，那么需要将QTcpSocket局部变量化
    //阻塞UI不必考虑此处
    //非阻塞UI，UI却工作很慢，考虑此处。
    //QTcpSocket* m_sock;
    quint8 eConType;
    quint32 m_UID;
    qint8 m_heartCount;
    QTimer* timer;
    void saveConType();
    void readConType();
    void connectToSingelHost();
    //TODO:public for debug
    template <typename T>
    void sendMessage(quint16 cmd, const T &t)
    {
        QTankMessage qMsg;
        qMsg.setUid(m_UID);
        qMsg.setCmd(cmd);
        QByteArray d;
        QTankData::pack(d, cmd, t);
        qMsg.setData(d);
        qMsg.translate();
        pline() << qMsg;
        QByteArray b;
        QTankParser::pack(b, qMsg);
        write(b);
        /*
        qint64 bb = bytesToWrite();
        bool cc = waitForBytesWritten();
        qint64 dd = bytesToWrite();
        pline() << cc << bb << dd;
        */
    }
    QTCloudUploadFile m_uploadfile;
    QTCloudUploadFileData m_uploadfiledata;
    QTCloudListDirResult m_dirs;
    QTCloudListFileResult m_files;
    QTCloudListPubDirResult m_pubdirs;
    QTCloudListPubFileResult m_pubfiles;
    QTCloudDownDevFileResult m_downfileresult;
    QTCloudDownFileData m_downfiledata;
signals:
    void signalSendData();
    void signalDownData();
    void signalUpdateProgress(int value);
private slots:
    void domainHostFound();
    void socketStateChanged(QAbstractSocket::SocketState);
    void socketErrorOccured(QAbstractSocket::SocketError);
    void socketConnected();
    void socketDisconnect();
    void updateProgress(qint64);
private slots:
    void sendUploadFileData();
    void sendDownFileData();
    void sendDownFileSuccess();
    void readyReadData();
    void dispatchRecvedMessage(QByteArray& blockOnNet);
    void recvLoginResultMessage(QTankMessage&);
    void recvHeatBeatResultMessage(QTankMessage&);
    void recvConnPoolFullMessage(QTankMessage&){}
    void recvListDirResultMessage(QTankMessage&);
    void recvAddDirResultMessage(QTankMessage&){}
    void recvDelDirResultMessage(QTankMessage&){}
    void recvModDirResultMessage(QTankMessage&){}
    void recvListFilesResultMessage(QTankMessage&);
    void recvListPubDirResultMessage(QTankMessage&);
    void recvListPubFilesResultMessage(QTankMessage&);
    void recvDownFileResultMessage(QTankMessage&);
    void recvDownFileDataResultMessage(QTankMessage&);
    void recvUploadFileResult(QTankMessage&);
    void recvUploadFileDataResult(QTankMessage&);
    void recvUploadFileSuccess(QTankMessage&);
};

QTankClient *HNSingleClient(QObject *parent = 0);

#endif // QTANKCLIENT_H
