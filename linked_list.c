#include "shell.h"

/**
 * cmd_list_length - calculates length of linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t cmd_list_length(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * cmd_list_to_string - gives an array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */
char **cmd_list_to_string(list_t *head)
{
	list_t *node = head;
	size_t x = cmd_list_length(head), y;
	char **strs;
	char *str;

	if (!head || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}

/**
 * cmd_list_print - displays all elements of a list_t linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t cmd_list_print(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_strput(num_convert(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_strput(h->str ? h->str : "(nil)");
		_strput("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * node_begins - gives node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: next character after prefix to match
 * Return: match node or null
 */
list_t *node_begins(list_t *node, char *prefix, char c)
{
	char *q = NULL;

	while (node)
	{
		q = begins_with(node->str, prefix);
		if (q && ((c == -1) || (*q == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_index_fetch - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t node_index_fetch(list_t *head, list_t *node)
{
	size_t x = 0;

	while (head)
	{
		if (head == node)
			return (x);
		head = head->next;
		x++;
	}
	return (-1);
}
