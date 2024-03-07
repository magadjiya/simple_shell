#include "shell.h"

/**
 * processCmds_withSemi - handles the processing of commands
 * separated by a semicolon
 * @cmdline: the line of command to process
 * @argv: array of arguments to shell program
 * @dirHead: the head of the path directory linked list
 * @envp: the array of environment variables
 * @aliasHead: pointer to the linked list of aliases
 * @pathValcpy: copy of directory string in PATH
 *
 * Return: 0 on success, -1 on failure
 */

int processCmds_withSemi(char *cmdline, char **argv, pdir_t **dirHead,
		char *envp[], alias **aliasHead, char *pathValcpy)
{
	char *cmdcpy, *arg_set;
	char **arr = NULL;
	int status = 0;
	int i = 0, j = 0, k = 0;
	size_t cmdlen = strlen(cmdline);

	cmdcpy = strdup(cmdline);
	cmdcpy[cmdlen - 1] = '\0';

	while (cmdcpy[i] != '\0')
	{
		j = 0;
		while (cmdcpy[i + j] != ';' && cmdcpy[i + j] != '\0')
			++j;
		arg_set = (char *)malloc(sizeof(char) * (j + 1));
		if (arg_set == NULL)
			return (0);

		for (k = 0; k < j; k++)
			arg_set[k] = cmdcpy[i + k];
		arg_set[k] = '\0';

		arr = createArgsArr(arg_set);
		status = processCmds(arr, cmdline, argv, dirHead,
				envp, aliasHead, pathValcpy);
		free(arg_set);
		if (cmdcpy[i + j] == '\0')
			break;
		i = i + j + 1;
	}
	free(cmdcpy);
	return (status);
}
