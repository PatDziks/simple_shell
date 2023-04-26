#include "term.h"
​
/**
 *err_strput - displays an input string
 * @str: string to be printed
 * Return: Nothing (void)
 */
void err_strput(char *str)
{
	int x;
​
	if (!str)
		return;
	for (x = 0; str[x] != '\0'; x++)
	{
		err_putchar(str[x]);
	}
}
​
/**
 * err_putchar - puts character c to stderr
 * @c: character to print
 * Return: On success 1.
 * On error, -1 is returned, & errno is set appropriately.
 */
int err_putchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];
​
	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}
​
/**
 * fd_putc - puts character c to given fd
 * @c: character to print
 * @fd: filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int fd_putc(char c, int fd)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];
​
	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}
​
/**
 *fd_strput - displays an input string
 * @str: string to be printed
 * @fd: filedescriptor to write to
 * Return: the number of chars put
 */
int fd_strput(char *str, int fd)
{
	int x = 0;
​
	if (!str)
		return (0);
	while (*str)
	{
		x += fd_putc(*str++, fd);
	}
	return (x);
}
