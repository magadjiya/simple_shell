#include "shell.h"

/**
 * is_exit - checks if cmdline is "exit" and exits the shell terminal
 * @cmdline: the command line
 * @cmdstatus: the exit status of the last command run
 * @argv: array of arguments containing program name
 * @dirHead: pointer to linked list of PATH directories
 * @pathValcpy: copy of directory string in PATH
 * @aliasHead: pointer to list of all aliases in the process
 *
 * Return: -1 if exit is not executed, 0 or status if executed
 */

int is_exit(char **cmdline, int cmdstatus, char **argv, pdir_t **dirHead,
		char *pathValcpy, alias **aliasHead)
{
	/* Handle the 'exit' shell builting */
	char *line, *linecp, *stat;
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
			if (status <= 0)
			{
				fprintf(stderr, "%s: 1: exit: Illegal number: %s\n", argv[0], stat);
				free(line);
				return (2);
			}
			else
			{
				free(line);
				_exit_shell_wstatus(cmdline, status, dirHead, pathValcpy, aliasHead);
			}
		}
		else
		{
			free(line);
			_exit_shell(cmdline, cmdstatus, dirHead, pathValcpy, aliasHead);
		}
	}

	free(line);
	return (0);
}

/**
 * _exit_shell - exits the shell with the last status
 * @cmdline: the command line
 * @cmdstatus: the exit status of the last command run
 * @dirHead: pointer to linked list of PATH directories
 * @pathValcpy: copy of directory string in PATH
 * @aliasHead: pointer to list of all aliases in the process
 *
 * Return: -1 if exit is not executed, 0 or status if executed
 */

void _exit_shell(char **cmdline, int cmdstatus, pdir_t **dirHead,
		char *pathValcpy, alias **aliasHead)
{
	free(pathValcpy);
	free(*cmdline);
	free_pdir(*dirHead);
	free_alias(*aliasHead);
	exit(cmdstatus);
}



/**
 * _exit_shell_wstatus - exits the shell with a given status
 * @cmdline: the command line
 * @status: the status to exit the shell with
 * @dirHead: pointer to linked list of PATH directories
 * @pathValcpy: copy of directory string in PATH
 * @aliasHead: pointer to list of all aliases in the process
 *
 * Return: nothing
 */

void _exit_shell_wstatus(char **cmdline, int status, pdir_t **dirHead,
		char *pathValcpy, alias **aliasHead)
{
	free(pathValcpy);
	free(*cmdline);
	free_pdir(*dirHead);
	free_alias(*aliasHead);
	exit(status);
}
