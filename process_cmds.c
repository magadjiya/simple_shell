#include "shell.h"

/**
 * processCmds - handles the processing of commands passed to the terminal
 * @cmdline: the line of command to process
 * @argv: array of arguments to shell program
 * @dirHead: the head of the path directory linked list
 * @envp: the array of environment variables
 *
 * Return: 0 on success, -1 on failure
 */

int processCmds(char *cmdline, char **argv, pdir_t **dirHead, char *envp[])
{
	char *line, *fullCmd, *new_line;
	char **arr = NULL;
	int status;

	/* Make a copy of the command line */
	line = strdup(cmdline);
	new_line = noWhiteSpaces(line);

	/* Create array of arguments */
	arr = createArgsArr(line);

	/*if (countArgs(arr) != 1)*/
	/*{*/
	/*	fprintf(stderr, "%s: 1: %s: not found\n", argv[0]);*/
	/*	return (0);*/
	/*}*/
	if (arr == NULL)
		return (0);

	/*  Validate the command @ arr[0] */
	fullCmd = validateCmd(&arr[0], dirHead);

	/* Invalid command */
	if (fullCmd == NULL)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", argv[0], arr[0]);
		/*print_error_message(argv, arr);*/
		free(arr[0]);
		free(arr);
		return (127);
	}
	/* Valid command */
	else
		status = executeCmds(cmdline, fullCmd, new_line, arr, dirHead, envp);
	if (*new_line != '/' && *new_line != '.')
		free(fullCmd);
	free(new_line);
	free(line);
	free(arr);
	return (status);
}

/**
 * print_error_message - creates and prints an error message
 * if command is invalid
 * @argv: array of arguments containing name of program
 * @arr: array of cmdlind arguments containing name of command
 *
 * Return: pointer to error message
 */

int print_error_message(char **argv, char **arr)
{
	char errmsg[100];

	strcpy(errmsg, argv[0]);
	strcat(errmsg, ": 1: ");
	strcat(errmsg, arr[0]);
	strcat(errmsg, ": not found\n");

	/*write(STDOUT_FILENO, errmsg, strlen(errmsg));*/
	return (0);
}
