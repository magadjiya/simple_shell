#include "shell.h"

/**
 * main - entry point of the shell terminal
 * @ac: the number of arguments passed to main
 * @argv: array of arguments passed to main
 *
 * Return: 0 on success, -1 on failure
 */

int main(int ac, char *argv[])
{
	/* Get the value of PATH */
	char *path_val = getPATH();
	/* Make a linked list of directories in PATH */
	pdir_t *dirList = makePathList(path_val);

	if (ac != 1)
	{
		fprintf(stderr, " %s: 0: cannot open %s: No such file\n", argv[0], argv[1]);
		exit(EXIT_SUCCESS);
	}

	/* Interactive Mode */
	if (isatty(STDIN_FILENO))
	{
		_INT_MODE(argv, &dirList);
		printf("\n");
	}

	/* Non-interactive mode */
	else
		_NON_INT_MODE(argv, &dirList);

	return (0);
}


/**
 * _INT_MODE - runs commands in interactive mode
 * @argv: the array of command line arguments
 * @dirHead: pointer to a linkded list of directories in PATH
 *
 * Return: 0
 */

int _INT_MODE(char **argv, pdir_t **dirHead)
{
	char *line = NULL;

	while ((line = promptline(line)) != NULL)
	{
		/* Command is a newline */
		if (isNewline(line))
			continue;

		/* Command is a shell builtin */
		/*else if (isShellBuiltin(&line, dirHead))*/
			/*continue;*/

		/* Command is a file or executable */
		else
			processCmds(line, argv, dirHead);
	}

	/* Free up allocated memory space */
	free(line);
	free_pdir(*dirHead);
	return (0);
}

/**
 * _NON_INT_MODE - runs commands in non-interactive mode
 * @argv: the array of command line arguments
 * @dirHead: pointer to a linkded list of directories in PATH
 *
 * Return: 0
 */

int _NON_INT_MODE(char **argv, pdir_t **dirHead)
{
	size_t n = 0;
	char *line = NULL;

	while ((getline(&line, &n, stdin)) != -1)
		processCmds(line, argv, dirHead);

	/* Free up allocated memory */
	free(line);
	free_pdir(*dirHead);

	return (0);
}
