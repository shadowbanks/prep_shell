#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF 10

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/**
 * _getline - my getline function
 * @lineptr - pointer to pointer where what is read
 * should be stored or NULL
 * @n: byte size or 0
 * @stream: where input should be read from
 *
 * Return: bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int fd = fileno(stream);
	ssize_t rd, red = 0;

	*lineptr = malloc((sizeof(char) * BUFF));
	if (*lineptr == NULL)
		return (-1);

	while ((rd = read(fd, *lineptr + red, BUFF)) > 0)
	{
		*n = *n + BUFF;
		*lineptr = _realloc(*lineptr, *n, (*n + BUFF));
		if (*lineptr == NULL)
		{
			free(*lineptr);
			return (-1);
		}
		red = red + rd;
		if ((*lineptr)[red - 1] == '\n')
			break;
	//	printf("Check %s\n", *lineptr);
	}
	if (rd < 0)
	{
		free(*lineptr);
		return (-1);
	}
	(*lineptr)[red] = '\0';
	return (red);
}

/**
 * _realloc - reallocates a momeory block using malloc and free
 * @ptr: pointer to old block of memory
 * @old_size: size of the old block of memory
 * @new_size: size of the new block of memory
 *
 * Return: pointer to memory block or NULL
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new = NULL;

//	printf("old_size: %u, new_size: %u\n", old_size, new_size);

	if (ptr != NULL)
	{
		if (new_size == old_size)
			return (ptr);
		if (new_size == 0)
		{
			free(ptr);
			return (NULL);
		}
		else if (new_size > old_size)
		{
			new = malloc(new_size);
			if (new != NULL)
			{
				memcpy(new, ptr, old_size);
				free(ptr);
				return (new);
			}
		}
	}
	ptr = malloc(new_size);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}

int main()
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t getl;
	char *pmt = "$ ";

	while (getl != EOF && getl != -1)
	{
		write(1, pmt, 2);
		getl = _getline(&lineptr, &n, stdin);
//		printf("%s\n", lineptr);
		write(1, lineptr, getl);
	}

	free(lineptr);
	return (0);
}
