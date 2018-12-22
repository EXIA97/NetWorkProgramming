#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <utility>
#include <QObject>
#include <QStandardItem>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

namespace Ui {
class Server;
}

class Server : public QWidget
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private:
    Ui::Server *ui;
    void BindSlots();
    void UpdateIPList();
    int port;
    QTcpServer* mServer;
    QMap<QString,QTcpSocket*> mIPWithSocket;
    QString history;

private slots:
    void SendMessage();
    void OnClientConnect();
    void OndisConnect();
    void OnError(QAbstractSocket::SocketError e);
    void OnReadable();
};

#endif // SERVER_H
