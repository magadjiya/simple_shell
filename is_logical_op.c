#include "shell.h"

/**
 * is_logical_op - checks if cmdline has a logical && or || operator
 * @cmdline: the command line given to the terminal
 *
 * Return: the number of &&, or 0
 */

int is_logical_op(char *cmdline)
{
	int count = 0;

	count = is_logical_and(cmdline);
	if (count > 0)
		return (count);
	count = is_logical_or(cmdline);
	if (count > 0)
		return (count);

	return (count);
}
