#include "shell.h"

/**
 * printenv - prints the environment variables
 * @cmdline: the command line given to the terminal
 *
 * Return: 1 if environment is printed, 0 if not
 */

int printenv(char *cmdline)
{
	char *line;
	char **env = environ;
	char *linecp;

	line = strdup(cmdline);
	linecp = strtok(line, "\n");

	/* Handle env shell builtin -> Task 5 */
	if ((strcmp(linecp, "env") == 0))
	{
		while (*env != NULL)
		{
			printf("%s\n", *env);
			++env;
		}
		free(line);
		return (1);
	}
	free(line);
	return (0);
}
