#include "shell.h"

/**
 * **str_tok_delim - chops a string into words. Repeat delimiters are ignored
 * @str: input string
 * @d: delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **str_tok_delim(char *str, char *d)
{
	int x, y, l, n, wordscount = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!_xdelim(str[x], d) && (_xdelim(str[x + 1], d) || !str[x + 1]))
			wordscount++;

	if (wordscount == 0)
		return (NULL);
	s = malloc((1 + wordscount) * sizeof(char *));
	if (s == NULL)
		return (NULL);
	for (x = 0, y = 0; y < wordscount; y++)
	{
		while (_xdelim(str[x], d))
			x++;
		l = 0;
		while (!_xdelim(str[x + l], d) && str[x + l])
			l++;
		s[y] = malloc((l + 1) * sizeof(char));
		if (!s[y])
		{
			for (l = 0; l < y; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s[y][n] = str[x++];
		s[y][n] = 0;
	}
	s[y] = NULL;
	return (s);
}

/**
 * **str_tok - seperates a string into words
 * @str: the input string
 * @d: delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **str_tok(char *str, char d)
{
	int x, y, l, n, wordscount = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
		    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			wordscount++;
	if (wordscount == 0)
		return (NULL);
	s = malloc((1 + wordscount) * sizeof(char *));
	if (s == NULL)
		return (NULL);
	for (x = 0, y = 0; y < wordscount; y++)
	{
		while (str[x] == d && str[x] != d)
			x++;
		l = 0;
		while (str[x + l] != d && str[x + l] && str[x + l] != d)
			l++;
		s[y] = malloc((l + 1) * sizeof(char));
		if (!s[y])
		{
			for (l = 0; l < y; l++)
				free(s[l]);
			free(s);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			s[y][n] = str[x++];
		s[y][n] = 0;
	}
	s[y] = NULL;
	return (s);
}
