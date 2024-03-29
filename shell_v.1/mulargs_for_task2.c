#include "shell.h"

/**
 * processCmds - handles the processing of commands passed to the terminal
 * @cmdline: the line of command to process
 * @argv: array of arguments to shell program
 * @mode: the mode of the shell (interactive or non-interactive)
 * @dirHead: the head of the path directory linked list
 *
 * Return: 0 on success, -1 on failure
 */

int processCmds(char *cmdline, char **argv, int mode, pdir_t **dirHead)
{
	char *line, *fullCmd, *cmd;
	char **arr = NULL;
	int i;
	pid_t p;
	int wstatus;

	line = strdup(cmdline); /* Make a copy of the command line */
	fullCmd = strtok(line, "\n"); /* Strip the newline character */
	cmd = strtok(fullCmd, " "); /* Get the first argument */

	/* Allocate memory to array for storing the argument */
	arr = (char **)malloc(sizeof(char *) * 1);
	if (arr == NULL)
		return (-1);

	/* Get other arguments (if there are) and store them in the argument array */
	i = 0;
	while (cmd) /* --> Initiate loop <-- */
	{
		arr[i] = cmd; /* Store the argument into the array */
		cmd = strtok(NULL, " "); /* Get the next argument */
		++i;
		/* Resize the argument array to accomodate the next argument */
		arr = (char **)reallocarray(arr, i + 1, sizeof(char *));
		if (arr == NULL)
			return (-1);
	}
	arr[i] = NULL;

	/* Initiate Task 3 - Validate the command @ arr[0] */
	if ((fullCmd = validateCmd(arr[0], dirHead)) == NULL) /* Invalid command */
		printf("%s: 1: %s: not found\n", argv[0], arr[0]);
	else /* Valid command */
	{
		p = fork(); /* Create a child process to execute command */
		if (p == -1) /* Handle failure to create child process */
			return (-1);
		else if (p == 0)  /* Handle program within the child process */
		{
			/* Handle execve fail */
			if ((execve(fullCmd, arr, NULL)) == -1)
			{
				/* Display error message */
				printf("%s: 1: No such file or directory\n", argv[0]);
				/* free up allocated memory spaces in child process */
				free(arr);
				free(line);
				free(cmdline);
				/* Terminate child process */
				exit(1);
			}
		}
		/* Handle the program in the parent process */
		else
			/* Wait for termination of child process */
			wait(&wstatus);
	}
	/* Display prompt only in interactive mode */
	if (mode == 1)
		printf("$ ");

	free(arr);
	free(line);
	if (line != fullCmd)
		free(fullCmd);
	return (0);
}
