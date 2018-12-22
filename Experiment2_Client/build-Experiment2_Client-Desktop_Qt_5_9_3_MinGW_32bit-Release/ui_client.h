/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QLabel *label_2;
    QTextEdit *IPText;
    QLabel *label;
    QTextEdit *receiveText;
    QLabel *label_5;
    QPushButton *pushButton;
    QLabel *label_4;
    QTextEdit *portText;
    QTextEdit *inputEdit;

    void setupUi(QWidget *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QStringLiteral("Client"));
        Client->resize(542, 429);
        label_2 = new QLabel(Client);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 54, 12));
        IPText = new QTextEdit(Client);
        IPText->setObjectName(QStringLiteral("IPText"));
        IPText->setEnabled(false);
        IPText->setGeometry(QRect(10, 30, 241, 31));
        IPText->setAcceptDrops(true);
        IPText->setReadOnly(true);
        IPText->setAcceptRichText(true);
        label = new QLabel(Client);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 54, 12));
        receiveText = new QTextEdit(Client);
        receiveText->setObjectName(QStringLiteral("receiveText"));
        receiveText->setGeometry(QRect(280, 30, 231, 331));
        label_5 = new QLabel(Client);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(280, 10, 101, 16));
        pushButton = new QPushButton(Client);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(180, 390, 75, 23));
        label_4 = new QLabel(Client);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 120, 111, 16));
        portText = new QTextEdit(Client);
        portText->setObjectName(QStringLiteral("portText"));
        portText->setEnabled(false);
        portText->setGeometry(QRect(10, 80, 241, 31));
        portText->setAcceptDrops(true);
        portText->setInputMethodHints(Qt::ImhMultiLine);
        portText->setReadOnly(true);
        portText->setAcceptRichText(true);
        inputEdit = new QTextEdit(Client);
        inputEdit->setObjectName(QStringLiteral("inputEdit"));
        inputEdit->setGeometry(QRect(10, 140, 241, 221));

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QWidget *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Client", Q_NULLPTR));
        label_2->setText(QApplication::translate("Client", "Port", Q_NULLPTR));
        label->setText(QApplication::translate("Client", "IPAddress", Q_NULLPTR));
        label_5->setText(QApplication::translate("Client", "Receive Message", Q_NULLPTR));
        pushButton->setText(QApplication::translate("Client", "SendMessage", Q_NULLPTR));
        label_4->setText(QApplication::translate("Client", "Input Message", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
