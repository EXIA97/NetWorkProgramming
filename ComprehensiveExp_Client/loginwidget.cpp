#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(Login()));
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::Login()
{
    emit TryToConnect(this->ui->textEdit->toPlainText());
}
