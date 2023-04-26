#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	cmd_list_print(info->history);
	return (0);
}

/**
 * al_to_string - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int al_to_string(info_t *info, char *str)
{
	char *g, c;
	int ret;

	g = string_chr(str, '=');
	if (!g)
		return (1);
	c = *g;
	*g = 0;
	ret = remove_node_index(&(info->alias),
		node_index_fetch(info->alias, node_begins(info->alias, str, -1)));
	*g = c;
	return (ret);
}

/**
 * set_al - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_al(info_t *info, char *str)
{
	char *g;

	g = string_chr(str, '=');
	if (!g)
		return (1);
	if (!*++g)
		return (al_to_string(info, str));

	al_to_string(info, str);
	return (node_input_end(&(info->alias), str, 0) == NULL);
}

/**
 * get_al - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int get_al(list_t *node)
{
	char *g = NULL, *f = NULL;

	if (node)
	{
		g = string_chr(node->str, '=');
		for (f = node->str; f <= g; f++)
			_putchar(*f);
		_putchar('\'');
		_strput(g + 1);
		_strput("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - clones the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0
 */
int _myalias(info_t *info)
{
	int x = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			get_al(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		p = string_chr(info->argv[x], '=');
		if (p)
			set_al(info, info->argv[x]);
		else
			get_al(node_begins(info->alias, info->argv[x], '='));
	}

	return (0);
}
