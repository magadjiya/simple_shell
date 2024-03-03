#include "shell.h"

/**
 * is_env - checks if cmdline is "env" and prints the env variables
 * @cmdline: the command line given to the terminal
 * @envp: the array of environment variables
 *
 * Return: 1 if environment is printed, 0 if not
 */

int is_env(char *cmdline, char *envp[])
{
	char *line;
	/*char **env = environ;*/
	char *linecp;

	/* Strip the newline character */
	line = strdup(cmdline);
	linecp = strtok(line, "\n");

	/* Handle the "env" shell builtin */
	if ((strcmp(linecp, "env") == 0))
	{
		printenv(envp);
		free(line);
		return (1);
	}
	free(line);
	return (0);
}


/**
 * printenv - prints the environment variable
 * @env: the array of environment variables
 *
 * Return: nothing
 */

void printenv(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		/*write(STDOUT_FILENO, *env, strlen(*env));*/
		/*write(STDOUT_FILENO, "\n", 1);*/
		printf("%s\n", env[i]);
		++i;
	}
}
