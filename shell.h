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
#include <errno.h>

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


typedef struct alias
{
	char *name;
	char *value;
	struct alias *next;
} alias;


/* Function Prototypes */

char *getPATH(void);

char *getHOME(void);

char *getPWD(void);

char *getOLDPWD(void);

pdir_t *makePathList(char *pathVal);

int _INT_MODE(char **argv, char *envp[], pdir_t **dirHead, char *pathValcpy);

int _NON_INT_MODE(char **argv, char *envp[], pdir_t **dirHead, char *pathValcpy);

void ctrlC_handler(int signum);

char *promptline(char *line);

int isNewline(char *line);

int isEmpty(char *line);

char *noWhiteSpaces(char *line);

int isShellBuiltin(char **cmdline, int cmdstatus, char **argv, pdir_t **dirHead, char *pathValcpy, alias **aliasHead);

int is_env(char *cmdline);

void printenv(char **env);

void unsetallenv(char **env);

int is_setenv(char *cmdline);

int _setenv(char *varName, char *val);

int is_unsetenv(char *cmdline);

int _unsetenv(char *varName);

int is_alias(char *cmdline, alias **aliasHead);

int is_cd(char *cmdline);

int is_exit(char **cmdline, int cmdstatus, char **argv,  pdir_t **dirHead, char *pathValcpy, alias **aliasHead);

void _exit_shell_wstatus(char **cmdline, int status, pdir_t **dirHead, char *pathValcpy, alias **aliasHead);

void _exit_shell(char **cmdline, int cmdstatus, pdir_t **dirHead, char *pathValcpy, alias **aliasHead);

int analyzeCmds(char *cmdline, char **argv, pdir_t **dirHead, char *envp[], alias **aliasHead, char *pathValcpy);

int is_semi(char *cmdline);

int processCmds_withSemi(char *cmdline, char **argv, pdir_t **dirHead, char *envp[], alias **aliasHead, char *pathValcpy);

int is_logical_op(char *cmdline);

int is_logical_and(char *cmdline);

int is_logical_or(char *cmdline);

int processCmds_withLogOp(char *cmdline, char **argv, pdir_t **dirHead, char *envp[], alias **aliasHead, char *pathValcpy);

int is_comment(char *cmdline);

int processCmds(char **arr, char *cmdline, char **argv, pdir_t **dirHead, char *envp[], alias **aliasHead, char *pathValcpy);

char **createArgsArr(char *cmdline);

void free_arr(char **arr);

int countArgs(char **arr);

char *validateCmd(char **cmd, pdir_t **dirHead, alias **aliasHead);

int executeCmds(char *cmdline, char *cmd, char **arr, pdir_t **dirHead, alias **aliasHead, char *envp[], char *pathValcpy);

pdir_t *add_dir(pdir_t **path_head, char *dir);

pdir_t *add_dir_end(pdir_t **path_head, char *dir);

int free_pdir(pdir_t *path_head);

char *absPath(char *dir, char *fileName);

ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

alias *add_alias(alias **aliasHead, char *name, char *val);

alias *add_alias_end(alias **aliasHead, char *name, char *val);

alias *update_alias(alias **aliasHead, char *name, char *val);

int check_alias(alias *aliasHead, char *name);

char *get_alias_name(alias *aliasHead, char *alias);

char *get_alias_val(alias *aliasHead, char *name);

int print_alias(alias *aliasHead, char *name);

int print_alias_all(alias **aliasHead);

int free_alias(alias *aliasHead);

#endif /* SHELL_H */
