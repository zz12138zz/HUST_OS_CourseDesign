/********************************************************************************
** Form generated from reading UI file 'process1.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESS1_H
#define UI_PROCESS1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_process1
{
public:
    QLabel *label;
    QLabel *pid;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *process1)
    {
        if (process1->objectName().isEmpty())
            process1->setObjectName(QStringLiteral("process1"));
        process1->resize(500, 300);
        label = new QLabel(process1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 5, 67, 17));
        pid = new QLabel(process1);
        pid->setObjectName(QStringLiteral("pid"));
        pid->setGeometry(QRect(90, 5, 67, 17));
        textBrowser = new QTextBrowser(process1);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(25, 30, 450, 250));

        retranslateUi(process1);

        QMetaObject::connectSlotsByName(process1);
    } // setupUi

    void retranslateUi(QWidget *process1)
    {
        process1->setWindowTitle(QApplication::translate("process1", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("process1", "pid:", Q_NULLPTR));
        pid->setText(QApplication::translate("process1", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class process1: public Ui_process1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESS1_H
