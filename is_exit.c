#include "shell.h"

/**
 * is_exit - checks if cmdline is "exit" and exits the shell terminal
 * @cmdline: the command line
 * @dirHead: pointer to linked list of PATH directories
 *
 * Return: -1 if exit is not executed, 0 or status if executed
 */

int is_exit(char **cmdline, pdir_t **dirHead)
{
	/* Handle the 'exit' shell builting */
	char *line, *linecp;
	char *stat;
	int status;

	/* Strip newline character from command */
	line = strdup(*cmdline);
	linecp = strtok(line, "\n");

	if ((strncmp(linecp, "exit", 4) == 0))
	{
		/* Check for exit status */
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
