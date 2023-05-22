#include "main.h"

/**
 * _strncmp - Compare two strings
 * @s1: first string
 * @s2: second string
 * @n: bytes to be copied
 *
 * Return: the integer difference
 */

int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0, s1Len = _strlen(s1), s2Len = _strlen(s2);

	while (i < s1Len && i < s2Len && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (0);
}

/**
 * _strlen - Calculate length of string
 * @s: string
 *
 * Return: length of string
 */

size_t _strlen(char *s)
{
	size_t i = 0;

	while (*s != '\0')
		i++, s++;
	return (i);
}
