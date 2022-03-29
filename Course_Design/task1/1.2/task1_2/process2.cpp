#include "process2.h"
#include "ui_process2.h"
#include<unistd.h>
process2::process2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::process2),i(0)
{
    ui->setupUi(this);
    ui->pid->setText(QString::number(getpid()));
    QTimer *t=new QTimer(this);
    connect(t,SIGNAL(timeout()),this,SLOT(print()));
    t->start(1000);
}

void process2::print(){
    ui->textBrowser->append(QString('a'+i));
    i=(i+1)%26;
}

process2::~process2()
{
    delete ui;
}
