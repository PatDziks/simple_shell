#include "shell.h"

/**
 * __cd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int __cd(info_t *info)
{
	char *k, *dr, buffer[1024];
	int chdir_ret;

	k = getcwd(buffer, 1024);
	if (!k)
		_strput("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dr = fetch_env(info, "HOME=");
		if (!dr)
			chdir_ret = /* TODO: what should this be? */
				chdir((dr = fetch_env(info, "PWD=")) ? dr : "/");
		else
			chdir_ret = chdir(dr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!fetch_env(info, "OLDPWD="))
		{
			_strput(k);
			_putchar('\n');
			return (1);
		}
		_strput(fetch_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dr = fetch_env(info, "OLDPWD=")) ? dr : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(info, "can't cd to ");
		err_strput(info->argv[1]), err_putchar('\n');
	}
	else
	{
		env_set(info, "OLDPWD", fetch_env(info, "PWD="));
		env_set(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
