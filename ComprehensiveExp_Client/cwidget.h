#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>
#include <loginwidget.h>

namespace Ui {
class CWidget;
}

class CWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CWidget(QWidget *parent = 0);
    ~CWidget();

private:
    void ConnectSlots();

signals:
    void SendMessage(QString key,QString message);

public slots:
    void OnClientAdd(QString key);
    void OnClientDel(QString key);
    void OnButtonClick();
    void OnReceiveMessage(QString message);
    void Login(QString username);

private:
    Ui::CWidget *ui;
    QString history;
    class Client* client;
    Ui::LoginWidget *loginui;
};

#endif // CWIDGET_H
