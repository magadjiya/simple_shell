#include "shell.h"

/**
 * is_unsetenv - checks if cmdline is "unsetenv" and handles the builtin
 * @cmdline: the command line given to the terminal
 *
 * Return: 1 if setenv is successful, 0 if not
 */

int is_unsetenv(char *cmdline)
{
	char *var_name = NULL;
	char *line = strdup(cmdline);
	char *linecp;
	int status = 1;

	linecp = strtok(line, "\n");

	if (strncmp(linecp, "unsetenv", 8) == 0)
	{
		var_name = strtok(linecp, " ");
		var_name = strtok(NULL, " ");
		if (var_name != NULL)
		{
			status = _unsetenv(var_name);
			free(line);
			return (status);
		}
		else
		{
			fprintf(stderr, "./hsh: Usage: unsetenv VARIABLE\n");
			free(line);
			return (2);
		}
	}
	else
	{
		fprintf(stderr, "./hsh: Usage: unsetenv VARIABLE\n");
		free(line);
		return (2);
	}
	free(line);
	return (1);
}


