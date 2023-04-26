#include "term.h"
​
/**
 * st_free - clears a pointer and NULLs the address
 * @ptr: address of pointer to clear
 * Return: 1 if freed, otherwise 0.
 */
int st_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
