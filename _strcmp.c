#include "main.h"

/**
 * _strcmp - Compare two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: the integer difference
 */

int _strcmp(const char *s1, const char *s2)
{
	int i = 0;
	int s1Len = _strlen(s1);
	int s2Len = _strlen(s2);

	while (i < s1Len && i < s2Len)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (s1[i] - s2[i]);
}

/**
 * _strlen - Calculate length of string
 * @s: string
 *
 * Return: length of string
 */

int _strlen(char *s)
{
	int i = 0;

	while (*s != '\0')
		i++, s++;
	return (i);
}
