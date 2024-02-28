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
	char *line = NULL; /* Getline variables */
	size_t n = 0;
	int status;
	char *path_val = getPATH(); 
	pdir_t *dirList = makePathList(path_val);
	(void)envp;

	if (ac != 1)
	{
		fprintf(stderr, " %s: 0: cannot open %s: No such file\n", argv[0], argv[1]);
		exit(EXIT_SUCCESS);
	}

	if (isatty(STDIN_FILENO)) /* Interactive Mode */
	{
		printf("$ ");

		while (getline(&line, &n, stdin) != -1) /* Process cmd arguments */
		{
			if (*line == '\n') /* No command */
			{
				printf("$ ");
				continue;
			}
			exit_shell(&line, &dirList); /* Check if builtin shell command */

			status = printenv(line);
			if (status)
			{
				printf("$ ");
				continue;
			}
			processCmds(line, argv, 1, &dirList); /* Other commamds */
		}
		printf("\n");
	}
	else /* Non-interactive mode */
		while ((getline(&line, &n, stdin)) != -1)
			processCmds(line, argv, 0, &dirList);

	free(line); /* Free up allocated memory space */
	free_pdir(dirList);
	return (0);
}
