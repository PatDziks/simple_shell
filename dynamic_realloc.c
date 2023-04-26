#include "term.h"
​
/**
 ** prep_storage - occupies memory with a constant byte
 *@s: pointer to the memory area
 *@b: byte to fill *s with
 *@n: amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *prep_storage(char *s, char b, unsigned int n)
{
	unsigned int x;
​
	for (x = 0; x < n; x++)
		s[x] = b;
	return (s);
}
​
/**
 * stfree - clears a string of strings
 * @pp: string of strings
 */
void stfree(char **pp)
{
	char **s = pp;
​
	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(s);
}
​
/**
 * st_realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to old block name.
 */
void *st_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *q;
​
	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
​
	q = malloc(new_size);
	if (q == NULL)
		return (NULL);
​
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (q);
}
