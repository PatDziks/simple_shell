#include "shell.h"

/**
 * history_file_fetch - gets the history file
 * @info: parameter struct
 * Return: assigns string containg history file
 */
char *history_file_fetch(info_t *info)
{
	char *buff, *dirc;

	dirc = fetch_env(info, "HOME=");
	if (!dirc)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirc) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirc);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * history_write - makes a file, or appends to an existing file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int history_write(info_t *info)
{
	ssize_t fd;
	char *filename = history_file_fetch(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		fd_strput(node->str, fd);
		fd_putc('\n', fd);
	}
	fd_putc(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * history_rd - obtains history from file
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int history_rd(info_t *info)
{
	int x, end = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = history_file_fetch(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			gen_history(info, buf + end, linecount++);
			end = x + 1;
		}
	if (end != x)
		gen_history(info, buf + end, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		remove_node_index(&(info->history), 0);
	order_history(info);
	return (info->histcount);
}

/**
 * gen_history - puts entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: 0
 */
int gen_history(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	node_input_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * order_history - reorder history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 * Return: new histcount
 */
int order_history(info_t *info)
{
	list_t *node = info->history;
	int x = 0;

	while (node)
	{
		node->num = x++;
		node = node->next;
	}
	return (info->histcount = x);
}
