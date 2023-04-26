#include "shell.h"

/**
 * stoint_err - converts a string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
int stoint_err(char *s)
{
	int x = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (x = 0;  s[x] != '\0'; x++)
	{
		if (s[x] >= '0' && s[x] <= '9')
		{
			result *= 10;
			result += (s[x] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - displays an error message
 * @info: parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 * -1 on error
 */
void print_err(info_t *info, char *estr)
{
	err_strput(info->fname);
	err_strput(": ");
	print_deci(info->line_count, STDERR_FILENO);
	err_strput(": ");
	err_strput(info->argv[0]);
	err_strput(": ");
	err_strput(estr);
}

/**
 * print_deci - displays a decimal (integer) number (base 10)
 * @input: input
 * @fd: filedescriptor to write to
 * Return: number of characters printed
 */
int print_deci(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int x, count = 0;
	unsigned int _abs_, active;

	if (fd == STDERR_FILENO)
		__putchar = err_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	active = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + active / x);
			count++;
		}
		active %= x;
	}
	__putchar('0' + active);
	count++;

	return (count);
}

/**
 * num_convert - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *num_convert(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long u = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		u = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[u % base];
		u /= base;
	} while (u != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * comment_del - replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: 0;
 */
void comment_del(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
