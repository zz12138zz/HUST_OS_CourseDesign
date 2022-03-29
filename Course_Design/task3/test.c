#include <unistd.h>
#include<fcntl.h>
#include <stdio.h>


int main()
{
	char buf_read[1024];
	char buf_write[1024];
	int file = open("/dev/yizumi",O_RDWR|O_NONBLOCK);
	if(file == -1)
	{
		printf("open failed!\n");
		return -1;
	}
	else
	{
		read(file, buf_read, sizeof(buf_read));
		printf("read result:\n%s\n",buf_read);
		printf("input a string to test write:\n");
		scanf("%[^\n]", buf_write);
		write(file, buf_write, sizeof(buf_write));
		read(file, buf_read, sizeof(buf_read));
		printf("read after write result:\n%s\n",buf_read);
		close(file);
		return 0;
	}
}

