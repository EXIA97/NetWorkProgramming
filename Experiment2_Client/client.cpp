#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    ui->IPText->setText("127.0.0.1");
    ui->portText->setText("7777");

    socket = new QTcpSocket(this);
    hostaddress = new QHostAddress("127.0.0.1");
    port = 7777;

    BindSlots();

    connect(socket,SIGNAL(connected()),this,SLOT(OnConnected()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(OnError()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(OnDisconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(OnReadable()));

    tryToConnect();
}

Client::~Client()
{
    delete ui;
}

void Client::tryToConnect()
{
    history.append("try to connect\n");
    ui->receiveText->setText(history);
    socket->connectToHost(*hostaddress,port);

}

void Client::BindSlots()
{
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(SendMessage()));
}


void Client::OnConnected()
{
    qDebug()<<"connected";
    history.append("connect to server\n");
    ui->receiveText->setText(history);
}

void Client::OnReadable()
{
    QByteArray buffer;
    buffer = socket->readAll();
    QString message = QString::fromUtf8(buffer);
    QString showInfo;
    showInfo.append("from server");
    showInfo.append(" : ");
    showInfo.append(message);
    showInfo.append("\n");
    history.append(showInfo);
    ui->receiveText->setText(history);
}

void Client::OnDisconnected()
{
    qDebug()<<"disconnected ";
    history.append("disconnect to server\n");
    ui->receiveText->setText(history);
    tryToConnect();
}

void Client::SendMessage()
{
    QString message = ui->inputEdit->toPlainText();
    socket->write(message.toUtf8());
    socket->flush();
}

void Client::OnError()
{
    //ui->linkLabel->setText(QString("error occured"));

    qDebug()<<socket->errorString();

    if (socket->error()==QAbstractSocket::RemoteHostClosedError){
        tryToConnect();
    }
    else if (socket->error()==QAbstractSocket::ConnectionRefusedError){
        for (int i=0; i<10 ; i++){
            socket->connectToHost(*hostaddress,port);
            socket->waitForConnected(3000);
        }
        history.append("connect failed\n");
        ui->receiveText->setText(history);
    }
}
