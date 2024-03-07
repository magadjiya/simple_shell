#include "shell.h"

/**
 * is_setenv - checks if cmdline is "setenv" and prints the env variables
 * @cmdline: the command line given to the terminal
 *
 * Return: 1 if setenv is successful, 0 if not
 */

int is_setenv(char *cmdline)
{
	char *var_name = NULL;
	char *val = NULL;
	char *line = strdup(cmdline);
	char *linecp;
	int status = 1;

	linecp = strtok(line, "\n");

	if (strncmp(linecp, "setenv", 6) == 0)
	{
		var_name = strtok(linecp, " ");
		var_name = strtok(NULL, " ");
		if (var_name != NULL)
		{
			val = strtok(NULL, " ");
			if (val !=  NULL)
			{
				status = _setenv(var_name, val);
				free(line);
				return (status);
			}
			else
			{
				fprintf(stderr, "./hsh: Usage: setenv VARIABLE VALUE\n");
				free(line);
				return (2);
			}
		}
		else
		{
			fprintf(stderr, "./hsh: Usage: setenv VARIABLE VALUE\n");
			free(line);
			return (2);
		}
	}
	free(line);
	return (1);
}


