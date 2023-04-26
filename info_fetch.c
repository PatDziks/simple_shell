#include "term.h"
​
/**
 * info_wipe - starts info_t struct
 * @info: struct address
 */
void info_wipe(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
​
/**
 * gen_info - starts info_t struct
 * @info: struct address
 * @av: argument vector
 */
void gen_info(info_t *info, char **av)
{
	int x = 0;
​
	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_tok_delim(info->arg, " \t");
		if (!info->argv)
		{
​
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strclone(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (x = 0; info->argv && info->argv[x]; x++)
​
		info->argc = x;
​
		overwrite_alias(info);
		overwrite_vars(info);
	}
}
​
/**
 * purge_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void purge_info(info_t *info, int all)
{
	stfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_node_list(&(info->env));
		if (info->history)
			free_node_list(&(info->history));
		if (info->alias)
			free_node_list(&(info->alias));
		stfree(info->environ);
			info->environ = NULL;
		st_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
