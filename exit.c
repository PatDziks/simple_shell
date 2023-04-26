#include "shell.h"

/**
 * __exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int __exit(info_t *info)
{
	int exitck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitck = stoint_err(info->argv[1]);
		if (exitck == -1)
		{
			info->status = 2;
			print_err(info, "Illegal number: ");
			err_strput(info->argv[1]);
			err_putchar('\n');
			return (1);
		}
		info->err_num = stoint_err(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
