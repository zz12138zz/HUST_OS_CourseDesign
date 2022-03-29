#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <fcntl.h>
#define SHMKEY1 11
#define SHMKEY2 22
#define SHMKEY3 33
#define SHMKEY4 44
void V(int semid, int index);
void P(int semid, int index);
union semun{
	int val;
};
int main(int argc,char *argv[])
{
	char *buf[4];
	int *len;
	int shmid1, shmid2, shmid3, shmid4,l;
	shmid1 = shmget(SHMKEY1, 101 * sizeof(char), 0666);
	shmid2 = shmget(SHMKEY2, 101 * sizeof(char), 0666);
	shmid3 = shmget(SHMKEY3, 101 * sizeof(char), 0666);
	shmid4 = shmget(SHMKEY4, 101 * sizeof(char), 0666);
	buf[0] = (char *)shmat(shmid1, 0, 0);
	buf[1] = (char *)shmat(shmid2, 0, 0);
	buf[2] = (char *)shmat(shmid3, 0, 0);
	buf[3] = (char *)shmat(shmid4, 0, 0);
	int semid;
	semid = semget((key_t)1, 3, IPC_CREAT | 0666);
    int file=open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IXUSR);
    if (file == -1){
        printf("create copy file failed!\n");
        exit(-1);
    }
	int i = 0;
	int d = 0;
	while (1)
	{
		P(semid, 1);
		P(semid, 2);
		if (buf[i][100] == 0)
		{
			V(semid, 2);
			V(semid, 0);
			close(file);
			break;
		}
		// printf("%s",buf[i]);
		write(file,buf[i],buf[i][100]);
		V(semid, 2);
		V(semid, 0);
		printf("write runs %d times in the %d shm\n",d++, i);
		i = (i + 1) % 4;
	}
	printf("write finish\n");
	exit(0);
}

void P(int semid, int index)
{
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	semop(semid, &sem, 1);
	return;
}

void V(int semid, int index)
{
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	semop(semid, &sem, 1);
	return;
}