#include "term.h"

/**
 * cmd_prompt - checks if file command is executable
 * @info: info struct
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int cmd_prompt(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * chars_clone - replicates characters
 * @pathstr: PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *chars_clone(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int x = 0, l = 0;

	for (l = 0, x = start; x < stop; x++)
		if (pathstr[x] != ':')
			buf[l++] = pathstr[x];
	buf[l] = 0;
	return (buf);
}

/**
 * detect_path - looks for cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *detect_path(info_t *info, char *pathstr, char *cmd)
{
	int x = 0, active_post = 0;
	char *path;

	if (pathstr == NULL)
		return (NULL);
	if ((_strlen(cmd) > 2) && begins_with(cmd, "./"))
	{
		if (cmd_prompt(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[x] || pathstr[x] == ':')
		{
			path = chars_clone(pathstr, active_post, x);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (cmd_prompt(info, path))
				return (path);
			if (!pathstr[x])
				break;
			active_post = x;
		}
		x++;
	}
	return (NULL);
}
