#include <stdio.h>
#include <unistd.h>

int main(void)
{
	pid_t my_pid;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	my_pid = getpid();
	printf("My pid is %u\n", my_pid);

	if (child_pid == 0)
		printf("(%u) Nooooooooooo\n", my_pid);
	else
		printf("(%u) %u I'm you father\n", my_pid, child_pid);
	return (0);

}
