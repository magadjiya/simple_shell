#include "shell.h"

/**
 * main - entry point of the shell terminal
 * @ac: the number of arguments passed to main
 * @argv: array of arguments passed to main
 * @envp: the environment variables of the process
 *
 * Return: 0 on success, -1 on failure
 */

int main(int ac, char *argv[], char *envp[])
{
	/* Get the value of PATH */
	char *path_val = getPATH();
	/* Copy the value to another pointer */
	char *pathValcpy = NULL;
	/* Make a linked list of directories in PATH */
	pdir_t *dirList = NULL;
	(void)envp;

	if  (path_val != NULL)
		pathValcpy = strdup(path_val);
	if (pathValcpy != NULL)
		dirList = makePathList(pathValcpy);

	/*unsetenv("PATH");*/
	if (ac != 1)
	{
		fprintf(stderr, " %s: 0: cannot open %s: No such file\n", argv[0], argv[1]);
		exit(EXIT_SUCCESS);
	}

	/* Interactive Mode */
	if (isatty(STDIN_FILENO))
	{
		_INT_MODE(argv, envp, &dirList, pathValcpy);
		printf("\n");
	}

	/* Non-interactive mode */
	else
		_NON_INT_MODE(argv, envp, &dirList, pathValcpy);

	return (0);
}


/**
 * _INT_MODE - runs commands in interactive mode
 * @argv: the array of command line arguments
 * @dirHead: pointer to a linkded list of directories in PATH
 * @pathValcpy: copy of directory string in PATH
 * @envp: the array of environment variables
 *
 * Return: 0
 */

int _INT_MODE(char **argv, char *envp[], pdir_t **dirHead, char *pathValcpy)
{
	char *line = NULL;
	int status = 0;

	if ((signal(SIGINT, ctrlC_handler)) == SIG_ERR)
		perror("error");

	while ((line = promptline(line)) != NULL)
	{
		/* Command is a newline or empty string */
		if (isNewline(line) || isEmpty(line))
			continue;

		/* Command is a shell builtin */
		status = isShellBuiltin(&line, status, argv, dirHead, pathValcpy, envp);
		if (status == 0 || status == 2)
			continue;

		/* Command is a file or executable */
		else
			status = processCmds(line, argv, dirHead, envp);

	}
	printf("\n");
	/*write(STDOUT_FILENO, "\n", 1);*/

	/* Free up allocated memory space */
	free(line);
	free(pathValcpy);
	free_pdir(*dirHead);
	exit(status);
}

/**
 * _NON_INT_MODE - runs commands in non-interactive mode
 * @argv: the array of command line arguments
 * @dirHead: pointer to a linkded list of directories in PATH
 * @pathValcpy: copy of directory string in PATH
 * @envp: the array of environment variables
 *
 * Return: 0
 */

int _NON_INT_MODE(char **argv, char *envp[],
		pdir_t **dirHead, char *pathValcpy)
{
	size_t n = 0;
	char *line = NULL;
	int status = 0;

	while ((getline(&line, &n, stdin)) != -1)
	{
		/* Command is a newline or empty string */
		if (isNewline(line) || isEmpty(line))
			continue;
		/* Command is a shell builtin */
		status = isShellBuiltin(&line, status, argv, dirHead, pathValcpy, envp);
		if (status == 0 || status == 2)
			continue;
		else
			status = processCmds(line, argv, dirHead, envp);
	}

	/* Free up allocated memory */
	free(line);
	free(pathValcpy);
	free_pdir(*dirHead);
	exit(status);
}


/**
 * ctrlC_handler - handles the ctrl + C signal
 * @signum: signal number
 *
 * Return: nothing
 */

void ctrlC_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n$ ");
		/*write(STDOUT_FILENO, "\n$ ", 3);*/
		fflush(stdout);
	}
}

