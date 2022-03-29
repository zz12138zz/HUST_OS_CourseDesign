#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "signal.h"
#include <sys/wait.h>
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "unistd.h"
#include "sys/sem.h"

#define SHMKEY1 11
#define SHMKEY2 22
#define SHMKEY3 33
#define SHMKEY4 44

int semid;

int shmid1, shmid2, shmid3, shmid4;

int pid_read, pid_write;

union semun{
	int val;
};

int main(int argc,char*argv[])
{
	shmid1 = shmget(SHMKEY1, 101 * sizeof(char), 0666 | IPC_CREAT);
	shmid2 = shmget(SHMKEY2, 101 * sizeof(char), 0666 | IPC_CREAT);
	shmid3 = shmget(SHMKEY3, 101 * sizeof(char), 0666 | IPC_CREAT);
	shmid4 = shmget(SHMKEY4, 101 * sizeof(char), 0666 | IPC_CREAT);
	semid = semget((key_t)1, 3, IPC_CREAT | 0666);
	union semun arg1, arg2,arg3;
	arg1.val = 4;
	semctl(semid, 0, SETVAL, arg1); //number of writable buf
	arg2.val = 0;
	semctl(semid, 1, SETVAL, arg2); //number of readable buf
	arg3.val = 1;
	semctl(semid, 2, SETVAL, arg3); //mutex
	char *argv_read[]= {"readbuf",argv[1],NULL};
	char *argv_write[]={"writebuf",argv[2],NULL};
	if ((pid_read = fork()) == 0){
		puts("read created\n");
		execv("./readbuf", argv_read);
	}
	else if ((pid_write = fork()) == 0){
		puts("write created\n");
		execv("./writebuf", argv_write);
	}
	int status=0;
	int pid1=wait(&status);
	if(WEXITSTATUS(status)!=0){
		pid1 = pid1==pid_read?pid_write:pid_read;
		kill(pid1,SIGKILL);
	}
	else	wait(NULL);
	printf("delete shm\n");
	shmctl(shmid1, IPC_RMID, 0);
	shmctl(shmid2, IPC_RMID, 0);
	shmctl(shmid3, IPC_RMID, 0);
	shmctl(shmid4, IPC_RMID, 0);
	printf("delete sem\n");
	semctl(semid, IPC_RMID, 0);
	return 0;
}
