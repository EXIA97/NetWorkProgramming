#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QHostAddress>

namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private:
    Ui::Client *ui;
    QTcpSocket* socket;
    QHostAddress* hostaddress;
    quint16 port;
    QString history;

    void BindSlots();

private slots:
    void tryToConnect();
    void OnConnected();
    void OnReadable();
    void OnDisconnected();
    void SendMessage();
    void OnError();
};

#endif // CLIENT_H
