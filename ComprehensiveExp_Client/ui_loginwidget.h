/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

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

class Ui_LoginWidget
{
public:
    QLabel *label;
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName(QStringLiteral("LoginWidget"));
        LoginWidget->resize(264, 113);
        label = new QLabel(LoginWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 20, 71, 21));
        textEdit = new QTextEdit(LoginWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(100, 20, 151, 21));
        pushButton = new QPushButton(LoginWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(90, 70, 80, 20));

        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QApplication::translate("LoginWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("LoginWidget", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        pushButton->setText(QApplication::translate("LoginWidget", "\347\231\273\345\275\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
