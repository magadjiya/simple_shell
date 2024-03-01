#include "shell.h"

/**
 * is_exit - checks if cmdline is "exit" and exits the shell terminal
 * @cmdline: the command line
 * @cmdstatus: the exit status of the last command run
 * @argv: array of arguments containing program name
 * @dirHead: pointer to linked list of PATH directories
 * @pathValcpy: copy of directory string in PATH
 *
 * Return: -1 if exit is not executed, 0 or status if executed
 */

int is_exit(char **cmdline, int cmdstatus, char **argv,
		pdir_t **dirHead, char *pathValcpy)
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
		free(*cmdline);
		free(pathValcpy);
		free_pdir(*dirHead);
		/* Check for exit status */
		stat = strtok(line, " ");
		stat = strtok(NULL, " ");
		if (stat)
		{
			status = atoi(stat);
			if (status <= 0)
			{
				fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", argv[0], stat);
				free(line);
				return (-1);
			}
			else
			{
				free(line);
				exit(status);
			}
		}
		else
		{
			free(line);
			exit(cmdstatus);
		}
	}
	free(line);
	return (-1);
}
