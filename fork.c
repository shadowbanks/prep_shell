#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t my_pid;
	pid_t pid;

	my_pid = getpid();
	printf("My pid is %u\n", my_pid);
	puts("Before fork");
	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return (1);
	}
	puts("After fork");
	my_pid = getpid();
	printf("My pid is %u\n", my_pid);
	return (0);
}
