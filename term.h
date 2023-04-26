#ifndef _TERM_H_
#define _TERM_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for num_convert() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int detect_sys_cmd(info_t *);
void detect_cmd_prmt(info_t *);
void create_cmd_fork(info_t *);

/* toem_cmd_parse.c */
int cmd_prompt(info_t *, char *);
char *chars_clone(char *, int, int);
char *detect_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_char_errors.c */
void err_strput(char *);
int err_putchar(char);
int fd_putc(char c, int fd);
int fd_strput(char *str, int fd);

/* toem_string_util.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *begins_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string_util.clips.c */
char *_strcpy(char *, char *);
char *_strclone(const char *);
void _strput(char *);
int _putchar(char);

/* toem_string_nav.c */
char *string_cpy(char *, char *, int);
char *string_cat(char *, char *, int);
char *string_chr(char *, char);

/* toem_string_tokenizer.c */
char **str_tok_delim(char *, char *);
char **str_tok_(char *, char);

/* toemst_dynamic_realloc.c */
char *prep_storage(char *, char, unsigned int);
void stfree(char **);
void *st_realloc(void *, unsigned int, unsigned int);

/* toem_storage.c */
int st_free(void **);

/* alpha_del.c */
int interactive(info_t *);
int _xdelim(char, char *);
int _xalpha(int);
int _stoint(char *);

/* toem_cmd_error */
int stoint_err(char *);
void print_err(info_t *, char *);
int print_deci(int, int);
char *num_convert(long int, int, int);
void comment_del(char *);

/* toem_exit.c */
int __exit(info_t *);

/* toem_cd.c */
int __cd(info_t *);

/* toem_help.c */
int __help(info_t *);

/* sys_alias.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/*toemline_fetch.c */
ssize_t cmd_fetch(info_t *);
int line_fetch(info_t *, char **, size_t *);
void sign_in_hdl(int);

/* toem_info_fetch.c */
void info_wipe(info_t *);
void gen_info(info_t *, char **);
void purge_info(info_t *, int);

/* toem_cmd_env.c */
char *fetch_env(info_t *, const char *);
int __env(info_t *);
int _env_set(info_t *);
int _env_undo(info_t *);
int gen_env_list(info_t *);

/* toem_env_fetcher.c */
char **env_fetch(info_t *);
int env_undo(info_t *, char *);
int env_set(info_t *, char *, char *);

/* toem_cmd_history.c */
char *history_file_fetch(info_t *info);
int history_write(info_t *info);
int history_rd(info_t *info);
int gen_history(info_t *info, char *buf, int linecount);
int order_history(info_t *info);

/* toem_node_list_nav.c */
list_t *node_input(list_t **, const char *, int);
list_t *node_input_end(list_t **, const char *, int);
size_t cmd_list_print_str(const list_t *);
int remove_node_index(list_t **, unsigned int);
void free_node_list(list_t **);

/* toem_linked_list.c */
size_t cmd_list_length(const list_t *);
char **cmd_list_to_string(list_t *);
size_t cmd_list_print(const list_t *);
list_t *node_begins(list_t *, char *, char);
ssize_t node_index_fetch(list_t *, list_t *);

/* toem_vars_util.c */
int cmd_combo(info_t *, char *, size_t *);
void cmd_combo_check(info_t *, char *, size_t *, size_t, size_t);
int overwrite_alias(info_t *);
int overwrite_vars(info_t *);
int overwrite_strings(char **, char *);

#endif
