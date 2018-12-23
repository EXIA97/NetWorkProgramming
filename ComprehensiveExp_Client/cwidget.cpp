#include "cwidget.h"
#include "ui_cwidget.h"
#include "client.h"
#include <QDebug>
#include <QFileDialog>

CWidget::CWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidget)
{
    ui->setupUi(this);

    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
    setFixedSize(552,340);
    this->client = new Client(this);
    this->ui->progressBar->setVisible(false);
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
    connect(ui->pushButton_2, &QPushButton::clicked, this, &CWidget::Login);
    connect(this, &CWidget::TryToConnect, client, &Client::ConnectToServer);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &CWidget::SendFileClick);
    connect(this, &CWidget::SendFile, client, &Client::SendFileToPeerClient);
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
    if (!message.isEmpty()&&!key.isEmpty()){
        emit SendMessage(key, message);
    }
}

void CWidget::OnReceiveMessage(QString message)
{
    history.append(message);
    this->ui->textBrowser->setText(history);
}

void CWidget::Login()
{
    QString username = this->ui->textEdit->toPlainText();
    emit TryToConnect(username);
}

void CWidget::SendFileClick()
{
    auto file = QFileDialog::getOpenFileName();
    auto key = this->ui->clientlist->selectedItems().first()->text();
    if (!key.isEmpty()){
        if (!file.isEmpty()){
            emit SendFile(key,file);
            ui->progressBar->setValue(0);
        }
    }
}
