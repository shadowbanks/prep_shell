#include "main.h"

/**
 * _strcat - Concatenate two strings
 * @dest: Destinantion string
 * @src: string to be append to dest
 *
 * Return: the pointer to concatenated string
 */

char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;
	char *temp = dest;

	while (temp[i] != '\0')
	{
		i++;
	}

	while (src[j] != '\0')
	{
		temp[i] = src[j];
		i++;
		j++;
	}

	temp[i] = '\0';

	return (dest);
}
