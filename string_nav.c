#include "shell.h"

/**
 **string_cpy - this copies a string
 *@dest: destination string to be copied to
 *@src: source string
 *@n: amount of characters to be copied
 *Return: concatenated string
 */
char *string_cpy(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	for (x = 0; src[x] != '\0' && x < n - 1; x++)
	{
		dest[x] = src[x];
	}
	if (x < n)
	{
		for (y = x; y < n; y++)
		{
			dest[y] = '\0';
		}
	}
	return (s);
}

/**
 **string_cat - it concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be maximally used
 *Return: concatenated string
 */
char *string_cat(char *dest, char *src, int n)
{
	int x, y;
	char *s = dest;

	x = 0;
	y = 0;
	while (dest[x] != '\0')
		x++;
	while (src[y] != '\0' && y < n)
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	if (y < n)
		dest[x] = '\0';
	return (s);
}

/**
 **string_chr - points a character in a string
 *@s: string to be parsed
 *@c: character to look for
 *Return: (s) a pointer to the memory area s
 */
char *string_chr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
