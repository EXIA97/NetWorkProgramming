/********************************************************************************
** Form generated from reading UI file 'cwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CWIDGET_H
#define UI_CWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CWidget
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QListWidget *clientlist;
    QTextEdit *inputText;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QTextEdit *textEdit;
    QPushButton *pushButton_2;
    QLabel *label;
    QPushButton *pushButton_3;
    QProgressBar *progressBar;

    void setupUi(QWidget *CWidget)
    {
        if (CWidget->objectName().isEmpty())
            CWidget->setObjectName(QStringLiteral("CWidget"));
        CWidget->resize(552, 340);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CWidget->sizePolicy().hasHeightForWidth());
        CWidget->setSizePolicy(sizePolicy);
        verticalLayoutWidget = new QWidget(CWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 40, 201, 301));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        clientlist = new QListWidget(verticalLayoutWidget);
        clientlist->setObjectName(QStringLiteral("clientlist"));

        verticalLayout->addWidget(clientlist);

        inputText = new QTextEdit(verticalLayoutWidget);
        inputText->setObjectName(QStringLiteral("inputText"));

        verticalLayout->addWidget(inputText);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        textBrowser = new QTextBrowser(CWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(200, 40, 471, 301));
        textEdit = new QTextEdit(CWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(110, 0, 171, 31));
        pushButton_2 = new QPushButton(CWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(290, 0, 111, 31));
        label = new QLabel(CWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 91, 31));
        QFont font;
        font.setFamily(QStringLiteral("Adobe Arabic"));
        font.setPointSize(12);
        label->setFont(font);
        label->setTextFormat(Qt::RichText);
        label->setAlignment(Qt::AlignCenter);
        pushButton_3 = new QPushButton(CWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(420, 0, 101, 31));
        progressBar = new QProgressBar(CWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(440, 310, 118, 23));
        progressBar->setValue(24);

        retranslateUi(CWidget);

        QMetaObject::connectSlotsByName(CWidget);
    } // setupUi

    void retranslateUi(QWidget *CWidget)
    {
        CWidget->setWindowTitle(QApplication::translate("CWidget", "Client", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CWidget", "Send Message", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("CWidget", "\347\231\273\351\231\206", Q_NULLPTR));
        label->setText(QApplication::translate("CWidget", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("CWidget", "\345\217\221\351\200\201\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CWidget: public Ui_CWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CWIDGET_H
