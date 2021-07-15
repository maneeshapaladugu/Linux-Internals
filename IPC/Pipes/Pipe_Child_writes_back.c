/*Program to create a communication channel using pipe system call. Parent process writes data into pipe, 
 * Child process reads and converts data into opposite case
 * Then child process writes back data into pipe*/

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
		
		sleep(1);
		
		printf("Parent process: Reading data from pipe after case conversion:\n");
		read(fd[0],parentBuffer,sizeof(parentBuffer));
		printf("Data:%s\n",parentBuffer);
	}
	else  // Child process
	{
		char ch, childBuffer[20];
		int count =0;
		
		read(fd[0],childBuffer,sizeof(childBuffer));
		printf("Data:%s\n",childBuffer);
		
		printf("Child process: -- Processing case conversion --\n");
		while (childBuffer[count] != '\0') 
		{
		      	ch = childBuffer[count];
     		 	if (ch >= 'A' && ch <= 'Z')
         			childBuffer[count] = childBuffer[count] + 32;
      			else if (ch >= 'a' && ch <= 'z')
         			childBuffer[count] = childBuffer[count] - 32;  
      			count++;  
   		}
		
		printf("Child process: Writing data into pipe:\n");
		write(fd[1],childBuffer,strlen(childBuffer)+1);
	}
}

