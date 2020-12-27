#include "SRCS/shell_header.h"

int main(void)
{
	int fd[2];
	int	id;
	int	res;

	if (pipe(fd) == -1)
		return (-1);
	id = fork();
	if (id == 0)
	{
		//child process
		res = 6;
	}
	else
	{
		//parent process
		res = 1;
	}
	printf("result %i\n", res);
	if (id == 0)
	{
		close (fd[0]);
		write(fd[1], &res, sizeof(res));
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int sum;
		read(fd[0], &sum, sizeof(sum));
		close(fd[0]);
		int total = sum + res;
		printf("Total sum is %d\n", total);
		wait(NULL);
	}
	return (0);	
}