#ifndef CLIENT_H
#define CLIENT_H

#include <QHash>
#include <QObject>


class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

    struct client{
         quint16 listenport;
         class QTcpSocket* socket;
    };

private:
    QHash<QString,client> _clients;

    class QTcpSocket* _socket;
    class QTcpServer* _server;

    static const int TYPE_ADD = 0x4141;
    static const int TYPE_DEL = 0x4142;

private:

signals:
    void NewMessageReceive(QString message);
    void NewClientAdd(QString key);
    void NewClientDel(QString key);


public slots:
    void OnConnectedServer();
    void OnReadyReadServer();
    void OnDisConnectedServer();

    void OnClientNewConnect();

    void SendMessageToPeerClient(QString key,QString message);
    void OnReceiveMessageFromClient();

};

#endif // CLIENT_H
