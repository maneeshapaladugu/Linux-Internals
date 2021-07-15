/*Program to create a communication channel using pipe system call*/

/* Pipes provide unidirectional inter process communication channel.
 * Pipes can be used to create communication channel between related processes (parent and child).
 * Any process uses file descriptor fd[1] to write the data and used file descriptor fd[0] to read the data.
 * pipe() system call returns 0 on success and -1 on failure
 * fork() system call returns: 
 * On success - pid of child process is returned in parent and 0 is retunred in child
 * On failure- -1 is returned in parent and no child process is created   
 */

#include<stdio.h>
#include<string.h>
#include<unistd.h> //Provides predefined function declaration of pipe()
int main()
{
	int fd[2];
	if(pipe(fd) < 0)
	{
		perror("pipe");
		return 0;
	}

	if(fork()) // Parent process
	{
		char parentBuffer[20];
		
		printf("Parent process: Enter the data to write into pipe:\n");
		fgets(parentBuffer,sizeof(parentBuffer),stdin);
		write(fd[1],parentBuffer,strlen(parentBuffer)+1);
	}
	else  // Child process
	{
		char childBuffer[20];

		read(fd[0],childBuffer,sizeof(childBuffer));
		printf("Child process: Reading data from pipe:\n%s",childBuffer);
	}
}

