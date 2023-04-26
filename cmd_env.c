#include "shell.h"

/**
 * __env - displays active environment
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0
 */
int __env(info_t *info)
{
	cmd_list_print_str(info->env);
	return (0);
}

/**
 * fetch_env - gets value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *fetch_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *q;

	while (node)
	{
		q = begins_with(node->str, name);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}

/**
 * _env_set - Initialize a new environment variable,
 * or enhance any existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0
 */
int _env_set(info_t *info)
{
	if (info->argc != 3)
	{
		err_strput("Incorrect number of arguements\n");
		return (1);
	}
	if (env_set(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _env_undo - takes off an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int _env_undo(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		err_strput("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		env_undo(info, info->argv[x]);

	return (0);
}

/**
 * gen_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int gen_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t x;

	for (x = 0; environ[x]; x++)
		node_input_end(&node, environ[x], 0);
	info->env = node;
	return (0);
}
