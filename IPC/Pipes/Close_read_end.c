/*Program to observe the behavior on closing the read end of file descriptor and then writing into the write end of file descriptor*/

/*
 * Observation:
 * SIGPIPE signal no 13 causes abnormal process termination on writing into the write end of pipe when read end of pipe is closed
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

	close(fd[0]); //Closing read end of pipe

	printf("Enter the data to write into pipe:\n");
	fgets(buffer,sizeof(buffer),stdin);

	returnValue = write(fd[1],buffer,sizeof(buffer)+1); //Leads to abnormal process termination on reaching this statement
	printf("returnValue of write: %d\n",returnValue);

	while(1);
}
