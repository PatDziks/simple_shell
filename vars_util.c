#include "term.h"

/**
 * cmd_combo - test current char in buffer if its a chain delimeter
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int cmd_combo(info_t *info, char *buf, size_t *p)
{
	size_t y = *p;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[y] == ';') /* found end of this command */
	{
		buf[y] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = y;
	return (1);
}

/**
 * cmd_combo_check - checks if it should continue chaining based on last status
 * @info: parameter struct
 * @buf: char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void cmd_combo_check(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t y = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			y = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			y = len;
		}
	}

	*p = y;
}

/**
 * overwrite_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int overwrite_alias(info_t *info)
{
	int x;
	list_t *node;
	char *q;

	for (x = 0; x < 10; x++)
	{
		node = node_begins(info->alias, info->argv[0], '=');
		if (node == 0)
			return (0);
		free(info->argv[0]);
		q = string_chr(node->str, '=');
		if (q == 0)
			return (0);
		q = _strclone(q + 1);
		if (q == 0)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * overwrite_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int overwrite_vars(info_t *info)
{
	int x = 0;
	list_t *node;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			overwrite_strings(&(info->argv[x]),
				_strclone(num_convert(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			overwrite_strings(&(info->argv[x]),
				_strclone(num_convert(getpid(), 10, 0)));
			continue;
		}
		node = node_begins(info->env, &info->argv[x][1], '=');
		if (node)
		{
			overwrite_strings(&(info->argv[x]),
				_strclone(string_chr(node->str, '=') + 1));
			continue;
		}
		overwrite_strings(&info->argv[x], _strclone(""));
	}
	return (0);
}

/**
 * overwrite_strings - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int overwrite_strings(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
