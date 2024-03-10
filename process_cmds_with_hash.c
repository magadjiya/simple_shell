#include "shell.h"

/**
 * processCmds_withHash - handles the processing of commands
 * containing the command replacement operator $
 * @cmdline: the line of command to process
 * @argv: array of arguments to shell program
 * @dirHead: the head of the path directory linked list
 * @envp: the array of environment variables
 * @aliasHead: pointer to the linked list of aliases
 * @pathValcpy: copy of directory string in PATH
 *
 * Return: 0 on success, -1 on failure
 */

int processCmds_withHash(char *cmdline, char **argv, pdir_t **dirHead,
		char *envp[], alias **aliasHead, char *pathValcpy)
{
	char *cmdcpy;
	char fullCmd[1024];
	char **arr = NULL;
	size_t cmdlen = strlen(cmdline);
	size_t i = 0, j = 0;
	int status = 0;

	cmdcpy = strdup(cmdline);
	cmdcpy[cmdlen - 1] = '\0';

	while (cmdcpy[i] != '#')
		++i;

	if (i == 0)
	{
		free(cmdcpy);
		return (status);
	}

	for (j = 0; j < i; j++)
		fullCmd[j] = cmdcpy[j];
	fullCmd[j] = '\0';

	arr = createArgsArr(fullCmd);
	status = processCmds(arr, cmdline, argv, dirHead,
			envp, aliasHead, pathValcpy);
	free(cmdcpy);
	return (status);


	/*while (cmdcpy[h] != '\0')
	{
		i = 0;
		while (cmdcpy[h + i] != '#' && cmdcpy[h + i] != '\0')
			i++;
		for (j = 0; j < i; j++)
			fullCmd[j + m] = cmdcpy[h + j];
		i++;
		k = 0;
		while (cmdcpy[h + i + k] != ' ' && cmdcpy[h + i + k] != '\0')
			k++;
		if (k == 0)
			fullCmd[j + m]  = cmdcpy[h + j];
		arg = (char *)malloc(sizeof(char) * (k + 1));
		for (j = 0; j < k; j++)
			arg[j] = cmdcpy[h + i + j];
		arg[j] = '\0';
		fullarg = expand_var(arg, cmdstatus);
		--i;
		if (fullarg == NULL)
		{
			if (k == 0)
				fullCmd[i + m + 1] = '\0';
			else
				fullCmd[i + m] = '\0';
		}
		else
		{
			for (j = 0; fullarg[j] != '\0'; j++)
				continue;
			l = j;
			for (j = 0; j < l; j++)
				fullCmd[i + j + m] = fullarg[j];
			fullCmd[i + j + m]  = '\0';
		}
		if (k == 0)
			m = m + i + j + 1;
		else
			m = m + i + j;
		++i;
		i = i + k;
		h = h + i;
		if (arg[0] == '?' || arg[0] == '$')
			free(fullarg);
		free(arg);
		arg = NULL;
	}*/
}

