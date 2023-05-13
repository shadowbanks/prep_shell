#include <stdio.h>
#include <unistd.h>

/**
 * main - ppid
 *
 * Return: always return 0
 */
int main()
{
	pid_t my_ppid;

	my_ppid = getppid();
	printf("%u\n", my_ppid);
}
