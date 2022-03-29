#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void update();
    void on_poweroff_clicked();

//    void on_pushButton_clicked();

    void on_pushButton_run_clicked();

    void on_pushButton_search_clicked();

    void on_pushButton_kill_clicked();

private:
    double time[120]={0};
    double cpu[120]={0};
    double mem[120]={0};
    double swap[120]={0};
    bool isSearching;
    QString pro_name;
    Ui::MainWindow *ui;
    bool show_certain_pro();
    void show_system_info();
    void show_process_info();
    void show_performance();
};
#endif // MAINWINDOW_H
