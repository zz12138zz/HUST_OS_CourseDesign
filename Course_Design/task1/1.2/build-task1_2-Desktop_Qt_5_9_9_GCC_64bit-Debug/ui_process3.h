/********************************************************************************
** Form generated from reading UI file 'process3.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESS3_H
#define UI_PROCESS3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_process3
{
public:
    QLabel *label;
    QLabel *pid;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *process3)
    {
        if (process3->objectName().isEmpty())
            process3->setObjectName(QStringLiteral("process3"));
        process3->resize(500, 300);
        label = new QLabel(process3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 5, 67, 17));
        pid = new QLabel(process3);
        pid->setObjectName(QStringLiteral("pid"));
        pid->setGeometry(QRect(90, 5, 67, 17));
        textBrowser = new QTextBrowser(process3);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(25, 30, 450, 250));

        retranslateUi(process3);

        QMetaObject::connectSlotsByName(process3);
    } // setupUi

    void retranslateUi(QWidget *process3)
    {
        process3->setWindowTitle(QApplication::translate("process3", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("process3", "pid:", Q_NULLPTR));
        pid->setText(QApplication::translate("process3", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class process3: public Ui_process3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESS3_H
