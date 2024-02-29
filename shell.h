#ifndef SHELL_H
#define SHELL_H
#define _GNU_SOURCE

/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * struct pathdir - a data type for storing directories in the PATH variable
 * @dir: the string name of the directory
 * @next_dir: pointer to the next directory
 */

typedef struct pathdir
{
	char *dir;
	struct pathdir *next_dir;
} pdir_t;


/* Function Prototypes */

char *getPATH(void);

pdir_t *makePathList(char *pathVal);

int _INT_MODE(char **argv, pdir_t **dirHead);

int _NON_INT_MODE(char **argv, pdir_t **dirHead);

void ctrlC_handler(int signum);

char *promptline(char *line);

int isNewline(char *line);

int isShellBuiltin(char **cmdline, pdir_t **dirHead);

int is_env(char *cmdline);

int is_exit(char **cmdline, pdir_t **dirHead);

int processCmds(char *cmdline, char **argv, pdir_t **dirHead);

char **createArgsArr(char *cmdline);

int print_error_message(char **argv, char **arr);

int countArgs(char **arr);

char *validateCmd(char *cmd, pdir_t **dirHead);

int executeCmds(char *cmdline, char *cmd, char **arr, pdir_t **dirHead);

pdir_t *add_dir(pdir_t **path_head, char *dir);

pdir_t *add_dir_end(pdir_t **path_head, char *dir);

int free_pdir(pdir_t *path_head);

char *absPath(char *dir, char *fileName);

int printenv(char *cmdline);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

int isEmpty(char *line);

#endif /* SHELL_H */
