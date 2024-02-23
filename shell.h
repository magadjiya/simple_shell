#ifndef SHELL_H
#define SHELL_H

/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

/**
 * struct savecmd - saves commands that have flags
 * @cmd: the command
 * @next: pointer to the flags
 */
typedef struct savecmd
{
	char *cmd;
	struct savecmd *next;
}
savecmd_t;

/* Function Prototypes */
char *changeLastChar(char *line, char c);
void handleCmd(char *line);
savecmd_t *addCmdEnd(savecmd_t **start, char *s);

#endif /* SHELL_H */
