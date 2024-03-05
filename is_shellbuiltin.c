#include "shell.h"

/**
 * isShellBuiltin - checks if the command line is a shell builtin
 * @cmdline: the command line to check
 * @cmdstatus: the status of the last command run
 * @argv: array of arguments with name of program
 * @dirHead: pointer to linked list of directories in PATH
 * @pathValcpy: copy of directory string in PATH
 * @aliasHead: pointer to a list of aliased in the process
 *
 * Return: 0 if line doesn't match any shell builtin, 1 if valid shellbuiltin.
 * It however doesn't return for the "exit" command
 */

int isShellBuiltin(char **cmdline, int cmdstatus, char **argv,
		pdir_t **dirHead, char *pathValcpy, alias **aliasHead)
{
	int status;

	if (is_env(*cmdline) == 1)
		return (0);

	status = is_setenv(*cmdline);
	if (status != 1)
		return (status);

	status = is_unsetenv(*cmdline);
	if (status != 1)
		return (status);

	status = is_alias(*cmdline, aliasHead);
	if (status != 1)
		return (status);

	status = is_exit(cmdline, cmdstatus, argv, dirHead, pathValcpy, aliasHead);
	if (status == 2)
		return (status);

	return (1);
}
