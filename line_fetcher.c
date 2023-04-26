#include "shell.h"

/**
 * cmd_buf - buffers linked commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t cmd_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t s = 0;
	size_t len_q = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*st_free((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sign_in_hdl);
#if USE_GETLINE
		s = getline(buf, &len_q, stdin);
#else
		s = line_fetch(info, buf, &len_q);
#endif
		if (s > 0)
		{
			if ((*buf)[s - 1] == '\n')
			{
				(*buf)[s - 1] = '\0'; /* remove trailing newline */
				s--;
			}
			info->linecount_flag = 1;
			comment_del(*buf);
			gen_history(info, *buf, info->histcount++);
			/* if (string_chr(*buf, ';')) is this a command chain? */
			{
				*len = s;
				info->cmd_buf = buf;
			}
		}
	}
	return (s);
}

/**
 * cmd_fetch - fetch a line minus the newline
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t cmd_fetch(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t x, y, len;
	ssize_t s = 0;
	char **buf_q = &(info->arg), *q;

	_putchar(BUF_FLUSH);
	s = cmd_buf(info, &buf, &len);
	if (s == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		y = x; /* init new iterator to current buf position */
		q = buf + x; /* get pointer for return */

		cmd_combo_check(info, buf, &y, x, len);
		while (y < len) /* iterate to semicolon or end */
		{
			if (cmd_combo(info, buf, &y))
				break;
			y++;
		}

		x = y + 1; /* increment past nulled ';'' */
		if (x >= len) /* reached end of buffer? */
		{
			x = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_q = q; /* pass back pointer to current command position */
		return (_strlen(q)); /* return length of current command */
	}

	*buf_q = buf; /* else not a chain, pass back buffer from line_fetch() */
	return (s); /* return length of buffer from line_fetch() */
}

/**
 * buf_rd - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t buf_rd(info_t *info, char *buf, size_t *i)
{
	ssize_t s = 0;

	if (*i)
		return (0);
	s = read(info->readfd, buf, READ_BUF_SIZE);
	if (s >= 0)
		*i = s;
	return (s);
}

/**
 * line_fetch - fetch next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int line_fetch(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t l;
	ssize_t t = 0, d = 0;
	char *q = NULL, *new_q = NULL, *c;

	q = *ptr;
	if (q && length)
		d = *length;
	if (x == len)
		x = len = 0;

	t = buf_rd(info, buf, &len);
	if (t == -1 || (t == 0 && len == 0))
		return (-1);

	c = string_chr(buf + x, '\n');
	l = c ? 1 + (unsigned int)(c - buf) : len;
	new_q = st_realloc(q, d, d ? d + l : l + 1);
	if (!new_q) /* MALLOC FAILURE! */
		return (q ? free(q), -1 : -1);

	if (d)
		string_cat(new_q, buf + x, l - x);
	else
		string_cpy(new_q, buf + x, l - x + 1);

	d += l - x;
	x = l;
	q = new_q;

	if (length)
		*length = d;
	*ptr = q;
	return (d);
}

/**
 * sign_in_hdl - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sign_in_hdl(__attribute__((unused))int sig_num)
{
	_strput("\n");
	_strput("$ ");
	_putchar(BUF_FLUSH);
}
