/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *sys_info;
    QLabel *label;
    QLabel *hostName;
    QLabel *label_3;
    QLabel *startUpTime;
    QLabel *label_5;
    QLabel *uptime;
    QLabel *frequency;
    QLabel *cpu;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *version;
    QWidget *pro_info;
    QListWidget *listWidget;
    QLineEdit *new_pro;
    QPushButton *pushButton_run;
    QLineEdit *targrt_pro;
    QPushButton *pushButton_search;
    QLineEdit *kill_pro;
    QPushButton *pushButton_kill;
    QWidget *cur_info;
    QCustomPlot *cpu_graphic;
    QLabel *label_4;
    QLabel *label_7;
    QCustomPlot *mem_graphic;
    QLabel *label_8;
    QCustomPlot *swap_graphic;
    QPushButton *poweroff;
    QLabel *time;
    QLabel *label_2;
    QLabel *label_6;
    QProgressBar *cpu_used;
    QProgressBar *mem_used;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(724, 553);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 701, 431));
        sys_info = new QWidget();
        sys_info->setObjectName(QStringLiteral("sys_info"));
        sys_info->setContextMenuPolicy(Qt::DefaultContextMenu);
        label = new QLabel(sys_info);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 50, 81, 16));
        hostName = new QLabel(sys_info);
        hostName->setObjectName(QStringLiteral("hostName"));
        hostName->setGeometry(QRect(330, 50, 191, 16));
        label_3 = new QLabel(sys_info);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 100, 161, 16));
        startUpTime = new QLabel(sys_info);
        startUpTime->setObjectName(QStringLiteral("startUpTime"));
        startUpTime->setGeometry(QRect(330, 100, 311, 16));
        label_5 = new QLabel(sys_info);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(110, 150, 161, 16));
        uptime = new QLabel(sys_info);
        uptime->setObjectName(QStringLiteral("uptime"));
        uptime->setGeometry(QRect(330, 150, 321, 16));
        frequency = new QLabel(sys_info);
        frequency->setObjectName(QStringLiteral("frequency"));
        frequency->setGeometry(QRect(330, 300, 291, 16));
        cpu = new QLabel(sys_info);
        cpu->setObjectName(QStringLiteral("cpu"));
        cpu->setGeometry(QRect(330, 250, 311, 16));
        label_9 = new QLabel(sys_info);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(110, 200, 161, 16));
        label_10 = new QLabel(sys_info);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(110, 250, 151, 16));
        label_11 = new QLabel(sys_info);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(110, 300, 131, 16));
        version = new QLabel(sys_info);
        version->setObjectName(QStringLiteral("version"));
        version->setGeometry(QRect(330, 200, 321, 21));
        tabWidget->addTab(sys_info, QString());
        pro_info = new QWidget();
        pro_info->setObjectName(QStringLiteral("pro_info"));
        listWidget = new QListWidget(pro_info);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 551, 371));
        new_pro = new QLineEdit(pro_info);
        new_pro->setObjectName(QStringLiteral("new_pro"));
        new_pro->setGeometry(QRect(570, 70, 113, 25));
        pushButton_run = new QPushButton(pro_info);
        pushButton_run->setObjectName(QStringLiteral("pushButton_run"));
        pushButton_run->setGeometry(QRect(590, 100, 71, 21));
        targrt_pro = new QLineEdit(pro_info);
        targrt_pro->setObjectName(QStringLiteral("targrt_pro"));
        targrt_pro->setGeometry(QRect(570, 160, 113, 25));
        pushButton_search = new QPushButton(pro_info);
        pushButton_search->setObjectName(QStringLiteral("pushButton_search"));
        pushButton_search->setGeometry(QRect(590, 190, 71, 21));
        kill_pro = new QLineEdit(pro_info);
        kill_pro->setObjectName(QStringLiteral("kill_pro"));
        kill_pro->setGeometry(QRect(570, 250, 113, 25));
        pushButton_kill = new QPushButton(pro_info);
        pushButton_kill->setObjectName(QStringLiteral("pushButton_kill"));
        pushButton_kill->setGeometry(QRect(590, 280, 71, 21));
        tabWidget->addTab(pro_info, QString());
        cur_info = new QWidget();
        cur_info->setObjectName(QStringLiteral("cur_info"));
        cpu_graphic = new QCustomPlot(cur_info);
        cpu_graphic->setObjectName(QStringLiteral("cpu_graphic"));
        cpu_graphic->setGeometry(QRect(0, 20, 691, 111));
        label_4 = new QLabel(cur_info);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(0, 0, 121, 21));
        label_7 = new QLabel(cur_info);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(0, 130, 121, 21));
        mem_graphic = new QCustomPlot(cur_info);
        mem_graphic->setObjectName(QStringLiteral("mem_graphic"));
        mem_graphic->setGeometry(QRect(0, 150, 691, 111));
        label_8 = new QLabel(cur_info);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(0, 260, 121, 21));
        swap_graphic = new QCustomPlot(cur_info);
        swap_graphic->setObjectName(QStringLiteral("swap_graphic"));
        swap_graphic->setGeometry(QRect(0, 280, 691, 111));
        tabWidget->addTab(cur_info, QString());
        poweroff = new QPushButton(centralwidget);
        poweroff->setObjectName(QStringLiteral("poweroff"));
        poweroff->setGeometry(QRect(510, 480, 81, 21));
        time = new QLabel(centralwidget);
        time->setObjectName(QStringLiteral("time"));
        time->setGeometry(QRect(470, 450, 201, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 450, 121, 21));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(60, 480, 121, 21));
        cpu_used = new QProgressBar(centralwidget);
        cpu_used->setObjectName(QStringLiteral("cpu_used"));
        cpu_used->setGeometry(QRect(160, 450, 118, 23));
        cpu_used->setValue(0);
        mem_used = new QProgressBar(centralwidget);
        mem_used->setObjectName(QStringLiteral("mem_used"));
        mem_used->setGeometry(QRect(160, 480, 118, 23));
        mem_used->setValue(0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 724, 27));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "host name:", Q_NULLPTR));
        hostName->setText(QApplication::translate("MainWindow", "NAME", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "time of system startup:", Q_NULLPTR));
        startUpTime->setText(QApplication::translate("MainWindow", "TIME", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "system uptime:", Q_NULLPTR));
        uptime->setText(QApplication::translate("MainWindow", "TIME", Q_NULLPTR));
        frequency->setText(QApplication::translate("MainWindow", "FREQUENCY", Q_NULLPTR));
        cpu->setText(QApplication::translate("MainWindow", "MODEL", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "system version:", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "CPU model:", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "CPU frequency:", Q_NULLPTR));
        version->setText(QApplication::translate("MainWindow", "VERSION", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(sys_info), QApplication::translate("MainWindow", "system infomation", Q_NULLPTR));
        pushButton_run->setText(QApplication::translate("MainWindow", "run ", Q_NULLPTR));
        pushButton_search->setText(QApplication::translate("MainWindow", "serch", Q_NULLPTR));
        pushButton_kill->setText(QApplication::translate("MainWindow", "kill", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(pro_info), QApplication::translate("MainWindow", "process", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "CPU:", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Memory", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Swap", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(cur_info), QApplication::translate("MainWindow", "performance", Q_NULLPTR));
        poweroff->setText(QApplication::translate("MainWindow", "power off", Q_NULLPTR));
        time->setText(QApplication::translate("MainWindow", "time", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "CPU:", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Memory:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
