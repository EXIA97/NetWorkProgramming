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

    //获取用户名作为标识
    QDataStream in(newClientSocket);
    QString userName;
    in >> userName;

    //检测是否有同名用户名
    if (_clientlist.find(userName) != _clientlist.end()) {
        qInfo()<<userName<<"用户名已存在，即将断开连接";
        newClientSocket->close();
    }
//    auto port = static_cast<int>(newClientSocket->peerPort());
//    auto ip = newClientSocket->peerAddress().toString();
//    auto key = ip + ":" + QString::number(port);

    client newclient {0, newClientSocket};

    connect(newClientSocket, &QTcpSocket::readyRead, this, &Server::OnReadyRead);
    connect(newClientSocket, &QTcpSocket::disconnected, this, &Server::OnDisconnected);

    QDataStream out(newClientSocket);
    qInfo() << "向新登陆的客户端发送其他所有人的客户端信息";
    //向新登陆的客户端发送其他所有人的客户端信息
    for (const auto& k : _clientlist.keys()){
        if (_clientlist[k].listenport != 0) {
            out << TYPE_ADD << k << _clientlist[k].listenport;
        }
    }
    newClientSocket->flush();

    _clientlist[key] = std::move(newclient);
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

    quint16 listenport;
    in >> listenport;

    QString key;
    // 查找Hash中的对应的客户端进行录入
    for (const auto& k : _clientlist.keys()) {
        if (_clientlist[k].socket == socket){
            key = k;
            _clientlist[k].listenport = listenport;
            break;
        }
    }
    // 向其他客户端广播新加入网络的客户端信息
    for (const auto& item : _clientlist){
        if (item.socket != socket) {
            QDataStream out(item.socket);
            out << TYPE_ADD << key << listenport;
            item.socket->flush();
        }
    }

}
