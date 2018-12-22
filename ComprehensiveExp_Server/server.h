#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QHash>

class Server : public QObject
{
    Q_OBJECT

    struct client{
         quint16 listenport;
         class QTcpSocket* socket;
    };

private:
    class QTcpServer* _server;
    QHash<QString,client> _clientlist;

    static const int TYPE_ADD = 0x4141;
    static const int TYPE_DEL = 0x4142;

public:
    explicit Server(QObject *parent = nullptr);


private slots:
    void OnNewConnection();
    void OnDisconnected();
    void OnReadyRead();
};

#endif // SERVER_H
