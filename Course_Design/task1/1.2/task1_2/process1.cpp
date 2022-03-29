#include "process1.h"
#include "ui_process1.h"
#include<unistd.h>
process1::process1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::process1),num(0)
{
    ui->setupUi(this);
    ui->pid->setText(QString::number(getpid()));
    QTimer *t=new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(print()));
    t->start(1000);
}

void process1::print(){
    ui->textBrowser->append(QString::number(this->num));
    this->num=(this->num+1)%10;
}

process1::~process1()
{
    delete ui;
}
