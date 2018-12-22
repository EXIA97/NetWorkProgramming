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

public slots:
    void OnClientAdd(QString key);
    void OnClientDel(QString key);
    void OnButtonClick();
    void OnReceiveMessage(QString message);

private:
    Ui::CWidget *ui;
    QString history;
    class Client* client;
};

#endif // CWIDGET_H
