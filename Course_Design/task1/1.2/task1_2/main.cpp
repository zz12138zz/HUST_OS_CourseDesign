#include "process1.h"
#include "process2.h"
#include "process3.h"
#include<unistd.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    int pid_1=0;
    int pid_2=0;
    int pid_3=0;

    //create child1
    if((pid_1==fork())==0){
        QApplication a1(argc, argv);
        process1 w1;
        w1.setWindowTitle("Process1");
        w1.show();

        a1.exec();
        exit(0);
    }
    else if((pid_2==fork())==0){
        QApplication a2(argc, argv);
        process2 w2;
        w2.setWindowTitle("Process2");
        w2.show();
        a2.exec();
        exit(0);
    }
    else if((pid_3==fork())==0){
        QApplication a3(argc, argv);
        process3 w3;
        w3.setWindowTitle("Process3");
        w3.show();
        a3.exec();
        exit(0);
    }




    return 0;
}
