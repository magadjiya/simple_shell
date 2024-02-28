#include "shell.h"

/**
 * promptline - displays a "$" sign and waits for user command.
 * Stores the command in a buffer
 * @line: the command line argument
 *
 * Return: pointer to the buffer containing commandline or NULL
 */

char *promptline(char *line)
{
	size_t n =  0;

	if (line != NULL)
	{
		free(line);
		line = NULL;
	}

	printf("$ ");
	if ((getline(&line, &n, stdin)) == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
