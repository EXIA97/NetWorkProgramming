#ifndef CLIENT_H
#define CLIENT_H

#include <QHash>
#include <QObject>
#include <QHostAddress>
#include <QString>


class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr,QString name = nullptr);

    struct client{
         QHostAddress ip;
         quint16 listenport;
         class QTcpSocket* socket;
    };

private:
    QHash<QString,client> _clients;

    QString username;

    class QTcpSocket* _socket;
    class QTcpServer* _server;

    static const int TYPE_ADD = 0x4141;
    static const int TYPE_DEL = 0x4142;
    static const int TYPE_MESSAGE = 0x4143;
    static const int TYPE_FILE = 0x4144;


signals:
    void NewMessageReceive(QString message);
    void NewClientAdd(QString key);
    void NewClientDel(QString key);


public slots:
    void ConnectToServer(QString username);

    void OnConnectedServer();
    void OnReadyReadServer();
    void OnDisConnectedServer();

    void OnClientNewConnect();

    void SendMessageToPeerClient(QString key,QString message);
    void OnReceiveMessageFromClient();

    void SendFileToPeerClient(QString key, QString filename);

};

#endif // CLIENT_H
