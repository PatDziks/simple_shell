#include "term.h"
​
/**
 * _strcpy - copies a string
 * @dest: destination
 * @src: source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0;
​
	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}
​
/**
 * _strclone - clones a string
 * @str: string to clone
 * Return: pointer to the duplicated string
 */
char *_strclone(const char *str)
{
	int len = 0;
	char *ret;
​
	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}
​
/**
 *_strput - displays an input string
 *@str: the string to be printed
 * Return: Nothing
 */
void _strput(char *str)
{
	int x = 0;
​
	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}
​
/**
 * _putchar - writes character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];
​
	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}
