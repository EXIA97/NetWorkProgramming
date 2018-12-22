#include "client.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>

Client::Client(QObject *parent) : QObject(parent)
{
    _socket = new QTcpSocket(this);
    _server = new QTcpServer(this);

    _server->listen(QHostAddress::LocalHost);
    connect(_server,&QTcpServer::newConnection,this,&Client::OnClientNewConnect);
    _socket->connectToHost(QHostAddress::LocalHost, 7777);
    connect(_socket, &QTcpSocket::connected, this, &Client::OnConnectedServer);
}

void Client::OnConnectedServer()
{
    QDataStream out(_socket);
    quint16 listenport = _server->serverPort();
    out << listenport;
    qDebug() << listenport;
    _socket->flush();

    connect(_socket, &QTcpSocket::readyRead, this, &Client::OnReadyReadServer);
    connect(_socket, &QTcpSocket::disconnected, this ,&Client::OnDisConnectedServer);
}

void Client::OnReadyReadServer()
{
    qDebug() << __FUNCTION__;
    QDataStream in(this->_socket);
    int type;
    QString key;
    quint16 listenPort;
    while (this->_socket->bytesAvailable() > 0){
        in >> type;
        if (type == TYPE_ADD){
            in >> key;
            in >> listenPort;

            client newClient {listenPort, nullptr};
            this->_clients[key] = newClient;

            emit NewClientAdd(key);
        }
        else if (type == TYPE_DEL){
            in >> key;
            // 删除该客户信息
            this->_clients.remove(key);
            emit NewClientDel(key);
        }
    }

    for (auto item : this->_clients.keys()){
        qDebug()<< item;
    }

}

void Client::OnDisConnectedServer()
{
    qDebug() << "You have been disconnected to server";
}

void Client::OnClientNewConnect()
{
    auto newClient = this->_server->nextPendingConnection();
    connect(newClient, &QTcpSocket::readyRead, this, &Client::OnReceiveMessageFromClient);

}

void Client::SendMessageToPeerClient(QString key, QString message)
{
    qDebug() << __FUNCTION__;
    if (this->_clients.contains(key)){
        client& target = this->_clients[key];
        if (target.socket == nullptr){
            target.socket = new QTcpSocket(this);
            QString address = key.split(":").first();
            qDebug() << address;
            target.socket->connectToHost(QHostAddress(address), target.listenport);
            target.socket->waitForConnected(-1);
            connect(target.socket, &QTcpSocket::readyRead, this, &Client::OnReceiveMessageFromClient);
            qDebug() << target.listenport;
        }
        QDataStream out(target.socket);
        QString name;
        name.append("127.0.0.1: ");
        name.append(QString::number(_socket->localPort()));
        out << name;
        out << message;
        target.socket->flush();
    }
}

void Client::OnReceiveMessageFromClient()
{
    qDebug() << __FUNCTION__;
    auto peerSocket = static_cast<QTcpSocket*>(sender());
    QDataStream in(peerSocket);
    QString key;
    QString message;
    in >> key;
    in >> message;
    auto fullMessage = key + " has said : " + message + "\n";
    qDebug() << fullMessage;
    emit NewMessageReceive(fullMessage);

    if (this->_clients.contains(key)){
       client& target = this->_clients[key];
       if (target.socket == nullptr){
           target.socket = peerSocket;
       }
    }
}

