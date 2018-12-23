#include "server.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>

Server::Server(QObject *parent) : QObject(parent)
{
    _server = new QTcpServer(this);
    _server->listen(QHostAddress::LocalHost,7777);
    connect(_server,&QTcpServer::newConnection,this,&Server::OnNewConnection);
}


void Server::OnNewConnection()
{
    qInfo()<<"new connect!";
    auto newClientSocket = _server->nextPendingConnection();

    connect(newClientSocket, &QTcpSocket::readyRead, this, &Server::OnReadyRead);
    connect(newClientSocket, &QTcpSocket::disconnected, this, &Server::OnDisconnected);

}

void Server::OnDisconnected()
{
    qInfo() << __FUNCTION__;
    auto socket = static_cast<QTcpSocket*>(sender());
    QString key;
    for (const auto& k : _clientlist.keys()) {
        if (_clientlist[k].socket == socket){
            key = k;
            _clientlist.remove(k);
            break;
        }
    }
    for (auto& item : _clientlist){
        QDataStream out(item.socket);
        out << TYPE_DEL << key;
        item.socket->flush();
    }
}

void Server::OnReadyRead()
{
    auto socket = static_cast<QTcpSocket*>(sender());
    QDataStream in(socket);
    QDataStream out(socket);

    //获取用户名作为标识
    QString userName;
    in >> userName;

    qDebug()<<"获取到的用户名为" << userName;

    //检测是否有同名用户名
    if (_clientlist.find(userName) != _clientlist.end()) {
        qInfo()<<userName<<"用户名已存在，即将断开连接";
        socket->close();
    }

    quint16 listenport;
    in >> listenport;

    qDebug()<<"获取到的端口号为" << listenport;


    client newclient {socket->peerAddress(), listenport, socket};

    _clientlist[userName] = newclient;

    //向新登陆的客户端发送其他所有人的客户端信息（用户名，IP，监听端口）
    for (const auto& k : _clientlist.keys()){
        if (_clientlist[k].socket != socket) {
            out << TYPE_ADD << k << _clientlist[k].ip << _clientlist[k].listenport;
        }
    }
    socket->flush();

    // 向其他客户端广播新加入网络的客户端信息
    for (const auto& item : _clientlist){
        if (item.socket != socket) {
            QDataStream out(item.socket);
            out << TYPE_ADD << userName << _clientlist[userName].ip << listenport;
            item.socket->flush();
        }
    }

}
