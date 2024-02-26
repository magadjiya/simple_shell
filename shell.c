#include "shell.h"

/**
 * main - entry point of the shell terminal
 * @ac: the number of arguments passed to main
 * @argv: array of arguments passed to main
 * @envp: array of environment variables
 *
 * Return: 0 on success, -1 on failure
 */

int main(int ac, char *argv[], char *envp[])
{
	/* Variables for getline() */
	char *line = NULL;
	size_t n = 0;
	int status;
	(void)envp;

	if (ac != 1)
	{
		fprintf(stderr, " %s: 0: cannot open %s: No such file\n", argv[0], argv[1]);
		exit(EXIT_SUCCESS);
	}

	/* Interactive Mode */
	if (isatty(STDIN_FILENO))
	{
		/* Display prompt */
		printf("$ ");

		/* Process command line arguments */
		while (getline(&line, &n, stdin) != -1)
		{
			/* No command is given */
			if (*line == '\n')
			{
				printf("$ ");
				continue;
			}
			/* Check if command is a shell builtin */
			exit_shell(&line);

			status = printenv(line);
			if (status)
			{
				printf("$ ");
				continue;
			}
			/* Processing Command */

			/* Other Command */
			processCmds(line, argv, 1);
		}
		printf("\n");
	}
	/* Non-interactive mode */
	else
		while ((getline(&line, &n, stdin)) != -1)
			processCmds(line, argv, 0);

	/* Free up allocated memory space */
	free(line);
	return (0);
}
