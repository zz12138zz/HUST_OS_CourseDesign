#include "process3.h"
#include "ui_process3.h"
#include<unistd.h>
process3::process3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::process3),i(0)
{
    ui->setupUi(this);
    ui->pid->setText(QString::number(getpid()));
    QTimer *t=new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(print()));
    t->start(1000);
}

void process3::print(){
    ui->textBrowser->append(QString('A'+i));
    i=(i+1)%26;
}

process3::~process3()
{
    delete ui;
}
