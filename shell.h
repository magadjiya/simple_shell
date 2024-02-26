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
int processCmds(char *cmdline, char **argv, int mode);

void free_arr(char **arr);

char *validateCmd(char *cmd);

char *getPATH(void);

pdir_t *makePathList(char *pathVal);

pdir_t *add_dir(pdir_t **path_head, char *dir);

pdir_t *add_dir_end(pdir_t **path_head, char *dir);

int free_pdir(pdir_t *path_head);

char *absPath(char *dir, char *fileName);

int printenv(char *cmdline);

int exit_shell(char **cmdline);

int printenv(char *cmdline);

#endif /* SHELL_H */
