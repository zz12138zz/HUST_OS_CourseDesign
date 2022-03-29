#include<linux/kernel.h>
#include<sys/syscall.h>
#include <stdio.h>
#include <unistd.h>

int main()
{

    long int aaa=syscall(333,"sys.c","222.c");
    printf("%ld\n",aaa);
    return 0;
}
