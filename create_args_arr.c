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

	/* Make a copy of the command line */
	line = strdup(cmdline);
	/* Strip the newline character */
	fullCmd = strtok(line, "\n");
	/* Get the first argument */
	cmd = strtok(fullCmd, " ");

	/* Allocate memory to array for storing the argument */
	arr = (char **)malloc(sizeof(char *) * 1);
	if (arr == NULL)
		return (NULL);

	/* Get other arguments (if there are) and store them in the argument array */
	while (cmd) /* --> Initiate loop <-- */
	{
		/* Store the argument into the array */
		arr[i] = cmd;
		/* Get the next argument */
		cmd = strtok(NULL, " ");
		++i;
		/* Resize the argument array to accomodate the next argument */
		arr = (char **)reallocarray(arr, i + 1, sizeof(char *));
		if (arr == NULL)
			return (NULL);
	}
	arr[i] = NULL;

	return (arr);
}
