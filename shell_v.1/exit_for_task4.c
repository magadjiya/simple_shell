#include "shell.h"

/**
 * exit_shell - exits the shell terminal
 * @cmdline: the command line
 * @dirHead: pointer to linked list of PATH directories
 *
 * Return: -1 if exit is not executed, 0 or status if executed
 */

int exit_shell(char **cmdline, pdir_t **dirHead)
{
	/* Handle the 'exit' shell builting -> Task 4 */
	char *line, *linecp;
	char *stat;
	int status;

	line = strdup(*cmdline);
	linecp = strtok(line, "\n");

	if ((strncmp(linecp, "exit", 4) == 0))
	{
		stat = strtok(line, " ");
		stat = strtok(NULL, " ");
		if (stat)
		{
			status = atoi(stat);
			free(line);
			free(*cmdline);
			free_pdir(*dirHead);
			exit(status);
		}
		free(line);
		free(*cmdline);
		free_pdir(*dirHead);
		exit(EXIT_SUCCESS);
	}
	free(line);
	return (-1);
}
