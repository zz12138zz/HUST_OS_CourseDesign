#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <unistd.h>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),isSearching(false)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer=new QTimer(this);
    timer->start(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    for(int i=0;i<120;i++)
    {
       time[i]=119-i;
    }
    ui->cpu_graphic->xAxis->setLabel("time/s");
    ui->cpu_graphic->yAxis->setLabel("cpu/%");
    ui->cpu_graphic->xAxis->setRange(0,120);
    ui->cpu_graphic->yAxis->setRange(0,100);
    ui->mem_graphic->xAxis->setLabel("time/s");
    ui->mem_graphic->yAxis->setLabel("memory/%");
    ui->mem_graphic->xAxis->setRange(0,120);
    ui->mem_graphic->yAxis->setRange(0,100);
    ui->swap_graphic->xAxis->setLabel("time/s");
    ui->swap_graphic->yAxis->setLabel("swap/%");
    ui->swap_graphic->xAxis->setRange(0,120);
    ui->swap_graphic->yAxis->setRange(0,100);
}
void MainWindow::show_system_info(){
    QFile  f;
    QString info;
    //get host name
    f.setFileName("/proc/sys/kernel/hostname");
    f.open(QIODevice::ReadOnly);
    info = f.readLine();
    ui->hostName->setText(info);
    f.close();

    //get startup time and up time
    //there are two num in the file,the first is what we need
    f.setFileName("/proc/uptime");
    f.open(QIODevice::ReadOnly);
    info = f.readLine();
    float alltime=info.section(" ",0,0).toFloat();
    int h = alltime/3600;
    int min = (alltime - h*3600)/60;
    int sec = alltime - h*3600 - min*60;
    QString all_time=info.sprintf ("%dh %dmin %dsec",h,min,sec);
    ui->startUpTime->setText(QDateTime::currentDateTime().addSecs(alltime*(-1)).toString());
    ui->uptime->setText(all_time);
    f.close();

    //get system version
    //use '(' as the end of version string
    f.setFileName("/proc/version");
    f.open(QIODevice::ReadOnly);
    info = f.readLine();
    ui->version->setText(info.mid(0,info.indexOf('(')));
    f.close();

    //get cpu model and frequency
    //lots of infomation in the file,just use what we need
    f.setFileName("/proc/cpuinfo");
    f.open(QIODevice::ReadOnly);
    while (1)
    {
       info = f.readLine();
       if(info == NULL)
       {
           break;
       }
       int pos=0;
       if((pos=info.indexOf("model name"))!=-1)
       {
           QString cpu_id=info.mid(pos+13,info.length());
           ui->cpu->setText(cpu_id);
       }
       if((pos=info.indexOf("cpu MHz"))!=-1)
       {
           QString cpu_hz=info.mid(pos+10,info.length());
           ui->frequency->setText(cpu_hz);
       }
   }
   f.close();

}

void MainWindow::show_process_info(){
    QFile  f;
    ui->listWidget->clear();
    //the infomation of process is stored in folders named with numbers
    //so we should get these folders first
    QDir qd("/proc");
    QStringList qslist=qd.entryList();
    QString qs=qslist.join("\n");
//    qDebug()<<qs;
    //the first two folders are '.' and '..',so we should find '/n' after the first three char
    int find_start = 3;
//    int all_pid_num=0;
    bool back;
    int l=0,r=0;
    ui->listWidget->addItem("pid\tppid\tstate\tpriority\tmemsize\tname");
    while(find_start!=-1)
    {
        l=qs.indexOf("\n",find_start);
        r=qs.indexOf("\n",l+1);
        find_start=r;
        QString name_of_pro=qs.mid(l+1,r-l-1);
        name_of_pro.toInt(&back,10);
        if(!back)
            continue;
//        all_pid_num++;
        f.setFileName("/proc/"+ name_of_pro +"/stat");
        f.open(QIODevice::ReadOnly);
        QString content = f.readAll();
        QStringList temp=content.split(' ');
        //get process name
        QString name=temp.at(1);
        QString temp_proc_name=name.mid(1,name.length()-2);
//        qDebug()<<name_of_pro<<" "<<temp_proc_name;
        //get process state
        QString temp_proc_state=temp.at(2);
        //get ppid
        QString temp_proc_ppid=temp.at(3);//ppid
        //get process priority
        QString temp_proc_priority=temp.at(17);
        //get process memory use
        QString temp_proc_mem=temp.at(22);
        //change mem_used unit from b to kb for better displaying
        int size=temp_proc_mem.toUInt()/1024;
        ui->listWidget->addItem(name_of_pro+'\t'+temp_proc_ppid+'\t'+temp_proc_state+'\t'+temp_proc_priority+'\t'+QString::number(size)+"KB"+'\t'+temp_proc_name);
        f.close();
    }
//    qDebug()<<all_pid_num;
}

bool MainWindow::show_certain_pro(){
    QFile  f;
    QDir qd("/proc");
    QStringList qslist=qd.entryList();
    QString qs=qslist.join("\n");
    int find_start = 3;
    bool back,found=false;
    int l=0,r=0;
    QStringList temp;
    QString content;
    QString temp_proc_name;
    ui->listWidget->clear();
    ui->listWidget->addItem("pid\tppid\tstate\tpriority\tmemsize\tname");
    while(find_start!=-1){
        l=qs.indexOf("\n",find_start);
        r=qs.indexOf("\n",l+1);
        find_start=r;
        QString name_of_pro=qs.mid(l+1,r-l-1);
        name_of_pro.toInt(&back,10);
        if(!back)
            break;
        f.setFileName("/proc/"+ name_of_pro +"/stat");
        f.open(QIODevice::ReadOnly);
        content = f.readAll();
        temp=content.split(' ');
        //get process name
        temp_proc_name=temp.at(1);
        temp_proc_name=temp_proc_name.mid(1,temp_proc_name.length()-2);
        if(this->pro_name==temp_proc_name){
            found=true;
            //get pid
            QString pid_num=temp.at(0);
            //get process state
            QString temp_proc_state=temp.at(2);
            //get ppid
            QString temp_proc_ppid=temp.at(3);//ppid
            //get process priority
            QString temp_proc_priority=temp.at(17);
            //get process memory use
            QString temp_proc_mem=temp.at(22);
            //change mem_used unit from b to kb for better displaying
            int size=temp_proc_mem.toUInt()/1024;
            ui->listWidget->addItem(pid_num+'\t'+temp_proc_ppid+'\t'+temp_proc_state+'\t'+temp_proc_priority+'\t'+QString::number(size)+"KB"+'\t'+temp_proc_name);
        }
        f.close();
    }
    return found;
}

void MainWindow::show_performance(){
    QFile f;
    QStringList info;
    QString temp;
    int totaltime[2]={0,0};
    int cputime[2][9];
    for(int k=0;k<2;k++)
    {
        f.setFileName("/proc/stat");
        f.open(QIODevice::ReadOnly);
        temp =f.readLine();
//        qDebug()<<temp;
        info=temp.split(' ');
        for(int i=0;i<9;i++)
        {
            cputime[k][i] = info.at(i+2).toInt();
            totaltime[k]+=cputime[k][i];
        }
        f.close();
        usleep(100000);
    }
    double idle=qAbs(cputime[0][3]-cputime[1][3]);
    double total=qAbs(totaltime[0]-totaltime[1]);
    double pcpu = 100* (total-idle)/total;
    QString cpu_used=temp.sprintf ("%.4f",pcpu);
    ui->cpu_used->setValue(pcpu);
    f.setFileName("/proc/meminfo");
    double mem_size;
    double mem_free_size;
    double swap_size;
    double swap_free_size;
    double mem_use=0;
    double swap_use=0;
    f.open(QIODevice::ReadOnly);
    while ((temp = f.readLine())!=NULL)
    {
        int from=0;
        if((from=temp.indexOf("MemTotal"))!=-1)
        {
            QString mem_total=temp.mid(from+10,temp.length()-from-14).trimmed();
            mem_size = mem_total.toInt();
        }
        if((from=temp.indexOf("MemFree"))!=-1)
        {
            QString mem_free=temp.mid(from+10,temp.length()-from-14).trimmed();
            mem_free_size = mem_free.toInt();
        }
        if((from=temp.indexOf("SwapTotal"))!=-1)
        {
            QString swap_total=temp.mid(from+10,temp.length()-from-14).trimmed();
            swap_size = swap_total.toInt();
        }
        if((from=temp.indexOf("SwapFree"))!=-1)
        {
            QString swap_free=temp.mid(from+10,temp.length()-from-14).trimmed();
            swap_free_size = swap_free.toInt();
        }
    }
    f.close();
    mem_use= 100*(mem_size-mem_free_size)/mem_size;
    ui->mem_used->setValue(mem_use);
    swap_use = 100*(swap_size-swap_free_size)/swap_size;
    QVector<double> x1(120);
    QVector<double> y1(120);
    QVector<double> x2(120);
    QVector<double> y2(120);
    QVector<double> x3(120);
    QVector<double> y3(120);
    for(int i=0;i<119;i++)
    {
       cpu[i]=cpu[i+1];
       mem[i]=mem[i+1];
       swap[i]=swap[i+1];
    }
    mem[119]=mem_use;
    swap[119]=swap_use;
    cpu[119]=pcpu;
    for(int i=0;i<120;i++)
    {
       x1[i]=time[i];
       y1[i]=cpu[i];
       x2[i]=time[i];
       y2[i]=mem[i];
       x3[i]=time[i];
       y3[i]=swap[i];
    }
    ui->cpu_graphic->addGraph();
    ui->cpu_graphic->graph(0)->setPen(QPen(Qt::red));
    ui->cpu_graphic->graph(0)->setData(x1,y1);
    ui->cpu_graphic->replot();

    ui->mem_graphic->addGraph();
    ui->mem_graphic->graph(0)->setPen(QPen(Qt::red));
    ui->mem_graphic->graph(0)->setData(x2,y2);
    ui->mem_graphic->replot();

    ui->swap_graphic->addGraph();
    ui->swap_graphic->graph(0)->setPen(QPen(Qt::red));
    ui->swap_graphic->graph(0)->setData(x3,y3);
    ui->swap_graphic->replot();
}

void MainWindow::update()
{
    this->show_system_info();
    if(!isSearching)
        this->show_process_info();
    else
        this->show_certain_pro();
    this->show_performance();
    ui->time ->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_poweroff_clicked()
{
    system("shutdown -h now");
}

void MainWindow::on_pushButton_run_clicked()
{
    QString pro = ui->new_pro->text();
    int status=system(pro.toLatin1()+"&");
    if(status==-1||!WIFEXITED(status)||WEXITSTATUS(status)){
        QMessageBox::warning(this, tr("run"), QString::fromUtf8("run process failed!"), QMessageBox::Yes);
    }
    ui->new_pro->clear();
}

void MainWindow::on_pushButton_search_clicked()
{
    QString name = ui->targrt_pro->text();
    if(name.isEmpty()){
        if(!isSearching)
            QMessageBox::warning(this,tr("run"),QString::fromUtf8("input a process name first!"),QMessageBox::Yes);
        else{
            isSearching=false;
            this->show_process_info();
        }
        return;
    }
    this->pro_name=name;
    isSearching=true;
    if(!this->show_certain_pro()){
        QMessageBox::warning(this,tr("run"),QString::fromUtf8("process not exist!"),QMessageBox::Yes);
    }
    ui->targrt_pro->clear();
}

void MainWindow::on_pushButton_kill_clicked()
{
    QString pid_num = ui->kill_pro->text();
    int status = system("kill "+pid_num.toLatin1());
    ui->kill_pro->clear();
    if(status==-1||!WIFEXITED(status)||WEXITSTATUS(status)){
        QMessageBox::warning(this, tr("run"), QString::fromUtf8("kill process failed!"), QMessageBox::Yes);
        return;
    }
    QMessageBox::information(this,tr("run"),QString::fromUtf8("kill process success"),QMessageBox::Yes);
}

//void MainWindow::on_pushButton_clicked()
//{
//    this->show_system_info();
//    this->show_process_info();
//    this->show_performance();

//}


