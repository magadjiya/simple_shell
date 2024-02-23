#ifndef SHELL_H
#define SHELL_H

/* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

/**
 */
typedef struct savecmd
{
	char *cmd;
	struct savecmd *next;
}
savecmd_t;

/* Function Prototypes */
savecmd_t *addCmdEnd(savecmd_t **start, char *s);

#endif /* SHELL H */
