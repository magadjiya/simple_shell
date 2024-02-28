#include "shell.h"

/**
 * processCmds - handles the processing of commands passed to the terminal
 * @cmdline: the line of command to process
 * @argv: array of arguments to shell program
 * @dirHead: the head of the path directory linked list
 *
 * Return: 0 on success, -1 on failure
 */

int processCmds(char *cmdline, char **argv, pdir_t **dirHead)
{
	char *fullCmd;
	char **arr = NULL;

	/* Create array of arguments */
	arr = createArgsArr(cmdline);
	if (arr == NULL)
		return (0);

	/*  Validate the command @ arr[0] */
	fullCmd = validateCmd(arr[0], dirHead);

	/* Invalid command */
	if (fullCmd == NULL)
		printf("%s: 1: %s: not found\n", argv[0], arr[0]);
	/* Valid command */
	else
		executeCmds(cmdline, fullCmd, arr, dirHead);


	if (arr[0] != fullCmd)
		free(fullCmd);
	free(arr[0]);
	free(arr);
	return (0);
}
