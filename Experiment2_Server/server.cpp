#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server),
    port(7777)
{
    ui->setupUi(this);
    ui->IPText->setText("127.0.0.1");
    ui->portText->setText("7777");

    BindSlots();

    mServer = new QTcpServer(this);

    //connect(mServer,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(OnError()));
    connect(mServer,SIGNAL(newConnection()),this,SLOT(OnClientConnect()));//连接信号与槽
    mServer->listen(QHostAddress("127.0.0.1"),port);
}

Server::~Server()
{
    delete ui;
}

void Server::BindSlots()
{
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(SendMessage()));
}

void Server::UpdateIPList()
{
    // 用户列表的更新
    ui->listWidget->clear();
    foreach (auto item, mIPWithSocket.keys()) {
             ui->listWidget->addItem(item);
         }

}

void Server::SendMessage()
{
    QString message = ui->inputEdit->toPlainText();
    QList<QListWidgetItem*> list = ui->listWidget->selectedItems();
    foreach (auto item,list) {
       QTcpSocket* targetSocket = mIPWithSocket.value(item->text());
       targetSocket->write(message.toUtf8());
       targetSocket->flush();
    }
}

void Server::OnClientConnect()
{
    QTcpSocket* clientSocket = mServer->nextPendingConnection();

    connect(clientSocket,SIGNAL(readyRead()),this,SLOT(OnReadable()));
    connect(clientSocket,SIGNAL(disconnected()),this,SLOT(OndisConnect()));

    QString welcomInfo = QString("welcome my friend");
    clientSocket->write(welcomInfo.toUtf8());
    clientSocket->flush();

    int port = (int)clientSocket->peerPort();
    QString portString = QString::number(port);
    QString address(clientSocket->peerAddress().toString());
    QString key = address + ":" + portString;
    mIPWithSocket.insert(key,clientSocket);
    UpdateIPList();

    QString linkInfo = key;
    linkInfo.append(" a new client is connected\n");
    history.append(linkInfo);
    ui->receiveText->setText(history);
}

void Server::OndisConnect()
{

    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());

    // UI操作
    QString disconnectIP = mIPWithSocket.key(socket);
    disconnectIP.append(" has disconnected");
    history.append(disconnectIP);
    ui->receiveText->setText(history);
    // 把对应地址从map里删除
    mIPWithSocket.remove(mIPWithSocket.key(socket));
    qDebug()<<mIPWithSocket.size();
    UpdateIPList();
}

void Server::OnError(QAbstractSocket::SocketError e)
{
    qDebug()<<e;
}


void Server::OnReadable()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QByteArray buffer;
    buffer = socket->readAll();
    QString message = QString::fromUtf8(buffer);
    QString senderAddress = mIPWithSocket.key(socket);
    QString showInfo;
    showInfo.append("from ");
    showInfo.append(senderAddress);
    showInfo.append(" : ");
    showInfo.append(message);
    showInfo.append("\n");
    history.append(showInfo);
    ui->receiveText->setText(history);
}
