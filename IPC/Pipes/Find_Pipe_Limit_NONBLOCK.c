/*Program to create a communication channel using pipe system call and to find the size of a pipe (Limit if pipe) without bloking the process*/

/* Pipes provide unidirectional inter process communication channel.
 * Pipes can be used to create communication channel between related processes (parent and child).
 * Any process uses file descriptor fd[1] to write the data and used file descriptor fd[0] to read the data.
 * pipe() system call returns 0 on success and -1 on failure
 * fork() system call returns: 
 * On success - pid of child process is returned in parent and 0 is retunred in child
 * On failure- -1 is returned in parent and no child process is created   
 */

#define _GNU_SOURCE // Declares pipe2() 
#include<stdio.h>
#include<fcntl.h> // Declares flags for pipe2(). Eg: O_NONBLOCK
#include<unistd.h> // Declares pipe()
int main()
{
	int fd[2], count=0;
	char ch = 'a';
	
	if(pipe2(fd,O_NONBLOCK) < 0)
	{
		perror("pipe");
		return 0;
	}
	
	//Size of pipe is 65536 bytes 
	while(write(fd[1],&ch,1) > 0)
		count ++;
	printf("Size of pipe = %d\n",count); 
}

