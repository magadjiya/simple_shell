#include "shell.h"

/**
 * processCmds - handles the processing of commands passed to the terminal
 * @arr: an array containing the commands to process
 * @cmdline: the command line to be freed if fails
 * @argv: array of arguments given to the shell program
 * @dirHead: pointer to the path directory linked list
 * @envp: the array of environment variables
 * @aliasHead: pointer to the linked list of aliases
 * @pathValcpy: copy of the value string of 'PATH'
 *
 * Return: 0 on success, -1 on failure
 */

int processCmds(char **arr, char *cmdline, char **argv, pdir_t **dirHead,
		char *envp[], alias **aliasHead, char *pathValcpy)
{
	char *fullCmd;
	int status;

	if (arr == NULL)
		return (0);

	/*  Validate the command @ arr[0] or get its fullpath */
	fullCmd = validateCmd(&arr[0], dirHead, aliasHead);

	/* Invalid command */
	if (fullCmd == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", argv[0], arr[0]);
		free_arr(arr);
		return (127);
	}

	/* Valid command */
	else
		status = executeCmds(cmdline, fullCmd, arr, dirHead,
				aliasHead, envp, pathValcpy);

	if (arr[0] != fullCmd)
		free(fullCmd);
	free_arr(arr);
	return (status);
}
