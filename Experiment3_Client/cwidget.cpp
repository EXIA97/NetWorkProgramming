#include "cwidget.h"
#include "ui_cwidget.h"
#include "client.h"
#include <QDebug>

CWidget::CWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidget)
{
    ui->setupUi(this);
    client = new Client(this);
    ConnectSlots();
}

CWidget::~CWidget()
{
    delete ui;
}

void CWidget::ConnectSlots()
{
    connect(ui->pushButton, &QPushButton::clicked, this, &CWidget::OnButtonClick);
    connect(client, &Client::NewClientAdd, this, &CWidget::OnClientAdd);
    connect(client, &Client::NewClientDel, this, &CWidget::OnClientDel);
    connect(this, &CWidget::SendMessage, client, &Client::SendMessageToPeerClient);
    connect(client, &Client::NewMessageReceive, this, &CWidget::OnReceiveMessage);
}

void CWidget::OnClientAdd(QString key)
{
    this->ui->clientlist->addItem(key);
}

void CWidget::OnClientDel(QString key)
{
    qDebug() << __FUNCTION__;
    qDebug() << key;
    auto result = this->ui->clientlist->findItems(key, Qt::MatchExactly);
    if (result.size() > 0){
        delete result.first();
    }
}

void CWidget::OnButtonClick()
{
    QString message = this->ui->inputText->toPlainText();
    auto key = this->ui->clientlist->selectedItems().first()->text();
    if (!message.isEmpty()){
        emit SendMessage(key, message);
    }
}

void CWidget::OnReceiveMessage(QString message)
{
    history.append(message);
    this->ui->textBrowser->setText(history);
}
