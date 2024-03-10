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
	char *path_val  = getPATH();
	/* Copy the value to another pointer */
	char *pathValcpy = NULL;
	/* Make a linked list of directories in PATH */
	pdir_t *dirList = NULL;
	(void)envp;

	if  (path_val != NULL)
		pathValcpy = strdup(path_val);
	if (pathValcpy != NULL)
		dirList = makePathList(pathValcpy);

	if (ac == 2)
	{
		_FILE_MODE(argv, envp, &dirList, pathValcpy);
		printf("\n");
	}

	/* Interactive Mode */
	else if (isatty(STDIN_FILENO))
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
	int cmdstatus = 0;
	alias *aliasHead = NULL;

	if ((signal(SIGINT, ctrlC_handler)) == SIG_ERR)
		perror("error");

	while ((line = promptline(line)) != NULL)
	{
		/* Command is a newline or empty string */
		if (isNewline(line) || isEmpty(line))
			continue;

		/* Command is a shell builtin */
		status = isShellBuiltin(&line, status, argv,
				dirHead, pathValcpy, &aliasHead);
		if (status == 0 || status == 2)
		{
			cmdstatus = status;
			continue;
		}

		/* Command is a file or executable */
		else
		{
			status = analyzeCmds(line, cmdstatus, argv, dirHead,
					envp, &aliasHead, pathValcpy);
			cmdstatus = status;
		}

	}
	printf("\n");

	/* Free up allocated memory space */
	free(line);
	free(pathValcpy);
	free_pdir(*dirHead);
	free_alias(aliasHead);
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
	int cmdstatus = 0;
	alias *aliasHead = NULL;

	while ((getline(&line, &n, stdin)) != -1)
	{
		/* Command is a newline or empty string */
		if (isNewline(line) || isEmpty(line))
			continue;
		/* Command is a shell builtin */
		status = isShellBuiltin(&line, status, argv,
				dirHead, pathValcpy, &aliasHead);
		if (status == 0 || status == 2)
		{
			cmdstatus = status;
			continue;
		}
		else
		{
			status = analyzeCmds(line, cmdstatus, argv, dirHead,
					envp, &aliasHead, pathValcpy);
			cmdstatus = status;
		}
	}

	/* Free up allocated memory */
	free(line);
	free(pathValcpy);
	free_pdir(*dirHead);
	free_alias(aliasHead);
	exit(status);
}


/**
 * _FILE_MODE - runs commands in file passed as argument to the shell program
 * @argv: the array of command line arguments
 * @dirHead: pointer to a linkded list of directories in PATH
 * @pathValcpy: copy of directory string in PATH
 * @envp: the array of environment variables
 *
 * Return: 0
 */


int _FILE_MODE(char **argv, char *envp[], pdir_t **dirHead, char *pathValcpy)
{
	char *line = NULL;
	size_t n = 0;
	int status = 0;
	alias *aliasHead = NULL;
	FILE *file_stream;

	file_stream = fopen(argv[1], "r");
	if (file_stream == NULL)
	{
		fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], argv[1]);
		free_pdir(*dirHead);
		free(pathValcpy);
		exit(2);
	}


	while (getline(&line, &n, file_stream) != -1)
        {
		/* Command is a newline or empty string */
		if (isNewline(line) || isEmpty(line))
			continue;

		/* Command is a shell builtin */
		status = isShellBuiltin(&line, status, argv,
				dirHead, pathValcpy, &aliasHead);
		if (status == 0 || status == 2)
			continue;
		
		/* Command is a file or executable */
		else
			status = analyzeCmds(line, status, argv, dirHead,
					envp, &aliasHead, pathValcpy);
		/*if (line != NULL)
		{
			free(line);
			line = NULL;
			n = 0;
		}*/
	}

	/* Free up allocated memory space */
	free(line);
	fclose(file_stream);
	free(pathValcpy);
	free_pdir(*dirHead);
	free_alias(aliasHead);
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

