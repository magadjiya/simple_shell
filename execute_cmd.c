#include "shell.h"

/**
 * executeCmds - executes a command given
 * @cmdline: the command line to be freed if fails
 * @cmd: the line of command to execute
 * @arr: array of arguments to execute
 * @dirHead: pointer to linked list of directories in PATH
 *
 * Return: 0 on success, -1 on failure
 */

int executeCmds(char *cmdline, char *cmd, char **arr, pdir_t **dirHead)
{
	int wstatus;
	pid_t p;
	char **env = environ;

	/* Create child process to execute command */
	p = fork();

	if (p == -1)
		return (-1);
	else if (p == 0)
	{
		/* Execute command and handle failed execution */
		if ((execve(cmd, arr, env)) == -1)
		{
			perror(arr[0]);
			/* free up allocated memory spaces in child process */
			if (arr[0] != cmd)
				free(cmd);
			free(arr[0]);
			free(arr);
			free(cmdline);
			free_pdir(*dirHead);
			exit(0);
		}
	}
	else /* Handle the program in the parent process */
		wait(&wstatus);

	return (0);
}



