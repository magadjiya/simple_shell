#include "shell.h"

/**
 * analyzeCmds - analyses the commands to know how to process them
 * @cmdline: the line of command to process
 * @argv: array of arguments to shell program
 * @dirHead: the head of the path directory linked list
 * @envp: the array of environment variables
 * @aliasHead: pointer to the linked list of aliases
 * @pathValcpy: copy of directory string in PATH
 *
 * Return: 0 on success, -1 on failure
 */

int analyzeCmds(char *cmdline, char **argv, pdir_t **dirHead,
		char *envp[], alias **aliasHead, char *pathValcpy)
{
	int status;
	char **arr;

	/* Analyze commands for special characters */
	if (is_semi(cmdline) != 0)
		status = processCmds_withSemi(cmdline, argv, dirHead,
				envp, aliasHead, pathValcpy);
	else if (is_logical_op(cmdline) != 0)
		status = processCmds_withLogOp(cmdline, argv, dirHead,
				envp, aliasHead, pathValcpy);
	else
	{
		arr = createArgsArr(cmdline);
		status = processCmds(arr, cmdline, argv, dirHead,
				envp, aliasHead, pathValcpy);
	}
	return (status);

}
