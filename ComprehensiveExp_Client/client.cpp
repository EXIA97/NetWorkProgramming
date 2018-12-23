#include "client.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QDataStream>
#include <QNetworkInterface>

#include <thread>
#include <fstream>
#include <stdexcept>
#include <QDir>

Client::Client(QObject *parent,QString name) : QObject(parent)
{
    this->username = name;
    _socket = new QTcpSocket(this);
    _server = new QTcpServer(this);

    _server->listen(QHostAddress::LocalHost);
    connect(_server,&QTcpServer::newConnection,this,&Client::OnClientNewConnect);

}

void Client::ConnectToServer(QString username)
{
    this->username = username;
    if (this->username == nullptr)
        return;

    else{
        _socket->connectToHost(QHostAddress::LocalHost, 7777);
        connect(_socket, &QTcpSocket::connected, this, &Client::OnConnectedServer);
    }
}


void Client::OnConnectedServer()
{
    QDataStream out(_socket);
    quint16 listenport = _server->serverPort();

    //发送用户名以及监听的端口号
    out << this->username;
    out << listenport;
    qDebug() <<"发送的用户名为" << this->username;
    qDebug() <<"监听的端口号为" << listenport;
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
    QHostAddress ip;
    quint16 listenPort;
    while (this->_socket->bytesAvailable() > 0){
        in >> type;
        if (type == TYPE_ADD){
            in >> key;
            in >> ip;
            in >> listenPort;

            client newClient {ip, listenPort, nullptr};
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
            target.socket->connectToHost(target.ip, target.listenport);
            target.socket->waitForConnected(-1);
            connect(target.socket, &QTcpSocket::readyRead, this, &Client::OnReceiveMessageFromClient);
            qDebug() << target.listenport;
        }
        QDataStream out(target.socket);
        out << TYPE_MESSAGE;
        out << this->username;
        out << message;
        target.socket->flush();
    }
}

void Client::OnReceiveMessageFromClient()
{
    qDebug() << __FUNCTION__;
    auto peerSocket = static_cast<QTcpSocket*>(sender());
    QDataStream in(peerSocket);
    using namespace std;

    int type;
    in >> type;

    switch (type) {
    case TYPE_MESSAGE:
    {
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
        break;
    }
    case TYPE_FILE:
    { 
        QDir dir;
        if(!dir.exists("Downloads")){
            dir.mkdir("Downloads");
        }

        static string file_prefix("Downloads/");
                    QString filename;
                    QString name;
                    char buffer[2048];
                    int length, count = 0;
                    in >> name >> filename >> length;
                    ofstream fout;
                    fout.open(file_prefix+filename.toLatin1().toStdString(), ios::out | ios::binary);
                    if (!fout.is_open())
                    {
                        qDebug() << "open " << (file_prefix + filename.toStdString()).c_str() << " failed.";
                        abort();
                    }
                    while (count < length) {
                        auto len = in.readRawData(buffer, 2048);
                        fout.write(buffer, len).flush();
                        count += len;
                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                    qDebug() << "finish " << (file_prefix + filename.toStdString()).c_str() << " receive.";
                    break;
    }
    default:
        break;
    }

}

void Client::SendFileToPeerClient(QString key, QString filename)
{

    qDebug() << __FUNCTION__;
    qDebug() << "target: " << key << endl
             << "file: " << filename;

    auto& target = _clients[key];

    if (target.socket == nullptr){
        target.socket = new QTcpSocket(this);
        target.socket->connectToHost(target.ip, target.listenport);
        target.socket->waitForConnected(-1);
        connect(target.socket, &QTcpSocket::readyRead, this, &Client::OnReceiveMessageFromClient);
        qDebug() << target.listenport;
    }

    char buffer[2048];
    QDataStream stream(target.socket);
    using namespace std;
    ifstream fin(filename.toLatin1().toStdString(), ios::in | ios::binary | ios::ate);
    int length=fin.tellg(), count = 0;
    fin.seekg(0, ios::beg);
    auto sfilename = filename.mid(filename.lastIndexOf("/") + 1);

    stream << TYPE_FILE << username << sfilename << length;
    qDebug() << "want send " << length << "bytes.";
    while (!fin.eof()) {
        fin.read(buffer, 2048);
        stream.writeRawData(buffer, fin.gcount());
        count += fin.gcount();
        //emit fileReceiveProgressChange(count/static_cast<float>(length)*100);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    target.socket->flush();
    qDebug() << "real send " << count << "bytes.";
}

