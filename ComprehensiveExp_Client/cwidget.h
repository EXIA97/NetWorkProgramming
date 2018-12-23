#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>

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
    void TryToConnect(QString username);
    void SendFile(QString key,QString file);

public slots:
    void OnClientAdd(QString key);
    void OnClientDel(QString key);
    void OnButtonClick();
    void OnReceiveMessage(QString message);
    void Login();
    void SendFileClick();

private:
    Ui::CWidget *ui;
    QString history;
    class Client* client;
    QString file;
};

#endif // CWIDGET_H
