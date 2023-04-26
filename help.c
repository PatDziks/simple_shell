#include "term.h"
/**
 * __help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int __help(info_t *info)
{
	char **arg_array;
​
	arg_array = info->argv;
	_strput("help call works. Function not yet implemented \n");
	if (0)
		_strput(*arg_array); /* temp att_unused workaround */
	return (0);
}
