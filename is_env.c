#include "shell.h"

/**
 * is_env - checks if cmdline is "env" and prints the env variables
 * @cmdline: the command line given to the terminal
 *
 * Return: 1 if environment is printed, 0 if not
 */

int is_env(char *cmdline)
{
	char *line;
	char **env = environ;
	char *linecp;

	/* Strip the newline character */
	line = strdup(cmdline);
	linecp = strtok(line, "\n");

	/* Handle the "env" shell builtin */
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
