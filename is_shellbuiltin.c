#include "shell.h"

/**
 * isShellBuiltin - checks if the command line is a shell builtin
 * @cmdline: the command line to check
 * @dirHead: pointer to linked list of directories in PATH
 *
 * Return: 0 if line doesn't match any shell builtin, 1 if valid shellbuiltin.
 * It however doesn't return for the "exit" command
 */

int isShellBuiltin(char **cmdline, pdir_t **dirHead)
{
	int TRUE = 1;
	int FALSE = 0;

	if (is_env(*cmdline) == 1)
	{
		/*free(*cmdline);*/
		return (TRUE);
	}
	else
		is_exit(cmdline, dirHead);

	return (FALSE);
}
