/*Program to observe the behavior on closing the write end of file descriptor and then reading from the read end of file descriptor*/

/*
 * Observations:
 * Process gets blocked on trying to read from the read end of empty pipe (if write end is NOT closed)
 * read() returns 0 to indicate the end of pipe on trying to read from the read end of empty pipe (if write end is closed) - Process is not blocked
*/

#include<stdio.h>
#include<unistd.h>
int main()
{
	int returnValue, fd[2];
	char buffer[20];

	if(pipe(fd) < 0)
	{
		printf("perror");
		return 0;
	}

	close(fd[1]); //Closing write end of pipe
	returnValue = read(fd[0],buffer,sizeof(buffer));
	printf("returnValue of read: %d\n",returnValue);
}
