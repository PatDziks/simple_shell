#include "term.h"

/**
 * env_fetch - brings string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0
 */
char **env_fetch(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = cmd_list_to_string(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * env_undo - deletes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: string env var attributes
 */
int env_undo(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t x = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = begins_with(node->str, var);
		if (q && *q == '=')
		{
			info->env_changed = remove_node_index(&(info->env), x);
			x = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		x++;
	}
	return (info->env_changed);
}

/**
 * env_set - starts a new environment variable,
 * or modify an existing one
 * @info: Structure containing presented arguments. Used to maintain
 * constant function prototype.
 * @var: string env var property
 * @value: string env var value
 *  Return: 0
 */
int env_set(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *q;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		q = begins_with(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	node_input_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
