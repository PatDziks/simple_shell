#include "shell.h"

/**
 * hsh - the shell loop of the main
 * @info: parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t s = 0;
	int sys_ret = 0;

	while (s != -1 && sys_ret != -2)
	{
		info_wipe(info);
		if (interactive(info))
			_strput("$ ");
		err_putchar(BUF_FLUSH);
		s = cmd_fetch(info);
		if (s != -1)
		{
			gen_info(info, av);
			sys_ret = detect_sys_cmd(info);
			if (sys_ret == -1)
				detect_cmd_prmt(info);
		}
		else if (interactive(info))
			_putchar('\n');
		purge_info(info, 0);
	}
	history_write(info);
	purge_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (sys_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (sys_ret);
}

/**
 * detect_sys_cmd - detects a system command
 * @info: parameter & return info struct
 * Return: -1 if system cmd not found,
 * 0 if system cmd executed successfully,
 * 1 if system cmd found but not successful,
 * -2 if builtin signals exit()
 */
int detect_sys_cmd(info_t *info)
{
	int x, sys_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", __exit},
		{"env", __env},
		{"help", __help},
		{"history", _myhistory},
		{"setenv", _env_set},
		{"unsetenv", _env_undo},
		{"cd", __cd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			sys_ret = builtintbl[x].func(info);
			break;
		}
	return (sys_ret);
}

/**
 * detect_cmd_prmt - detects a command in PATH
 * @info: parameter & return info struct
 * Return: void
 */
void detect_cmd_prmt(info_t *info)
{
	char *path = NULL;
	int x, l;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, l = 0; info->arg[x]; x++)
		if (!_xdelim(info->arg[x], " \t\n"))
			l++;
	if (!l)
		return;

	path = detect_path(info, fetch_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		create_cmd_fork(info);
	}
	else
	{
		if ((interactive(info) || fetch_env(info, "PATH=")
			|| info->argv[0][0] == '/') && cmd_prompt(info, info->argv[0]))
			create_cmd_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_err(info, "not found\n");
		}
	}
}

/**
 * create_cmd_fork - forks an exec thread to run cmd
 * @info: parameter & return info struct
 * Return: void
 */
void create_cmd_fork(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, env_fetch(info)) == -1)
		{
			purge_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_err(info, "Permission denied\n");
		}
	}
}
