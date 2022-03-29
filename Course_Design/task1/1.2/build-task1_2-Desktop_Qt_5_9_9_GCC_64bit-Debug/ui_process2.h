/********************************************************************************
** Form generated from reading UI file 'process2.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROCESS2_H
#define UI_PROCESS2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_process2
{
public:
    QLabel *label;
    QLabel *pid;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *process2)
    {
        if (process2->objectName().isEmpty())
            process2->setObjectName(QStringLiteral("process2"));
        process2->resize(500, 300);
        label = new QLabel(process2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 5, 67, 17));
        pid = new QLabel(process2);
        pid->setObjectName(QStringLiteral("pid"));
        pid->setGeometry(QRect(90, 5, 67, 17));
        textBrowser = new QTextBrowser(process2);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(25, 30, 450, 250));

        retranslateUi(process2);

        QMetaObject::connectSlotsByName(process2);
    } // setupUi

    void retranslateUi(QWidget *process2)
    {
        process2->setWindowTitle(QApplication::translate("process2", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("process2", "pid:", Q_NULLPTR));
        pid->setText(QApplication::translate("process2", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class process2: public Ui_process2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROCESS2_H
