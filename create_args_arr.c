#include "shell.h"

/**
 * createArgsArr - gets the arguments from a command line
 * and stores them in an array
 * @cmdline: the command line
 *
 * Return: pointer to a NULL terminated array of arguments
 */

char **createArgsArr(char *cmdline)
{
	char *line, *fullCmd, *cmd;
	char **arr = NULL;
	int i = 0;
	size_t j = 0;

	/* Make a copy of the command line */
	line = strdup(cmdline);
	/* Strip the newline character */
	fullCmd = strtok(line, "\n");
	/* Get the first argument */
	cmd = strtok(fullCmd, " ");

	/* Allocate memory to array for storing the arguments */
	arr = (char **)malloc(sizeof(char *) * 1);
	if (arr == NULL)
		return (NULL);

	/* Get other arguments (if there are) and store them in the argument array */
	while (cmd) /* --> Initiate loop <-- */
	{
		/* Allocate memory to store the command */
		arr[i] = (char *)malloc(sizeof(char) * (strlen(cmd) + 1));
		if (arr[i] == NULL)
		{
			free(line);
			free_arr(arr);
			return (NULL);
		}
		else
		{
			/* Store the argument into the array */
			/*strcpy(arr[i], cmd);*/
			for (j = 0; j < strlen(cmd); j++)
				arr[i][j] = cmd[j];
			arr[i][j] = '\0';
			/* Get the next argument */
			cmd = strtok(NULL, " ");
			++i;
			/* Resize the argument array to accomodate the next argument */
			arr = (char **)reallocarray(arr, i + 1, sizeof(char *));
			if (arr == NULL)
				return (NULL);
		}
	}
	arr[i] = NULL;
	free(line);
	return (arr);
}


/**
 * free_arr - frees the arguments in the arguments array
 * @arr: the address of the array
 *
 * Return: nothing
 */

void free_arr(char **arr)
{
	int i = 0;

	if (arr != NULL)
	{
		for (i = 0; arr[i] != NULL; i++)
			free(arr[i]);
		free(arr);
	}
}

