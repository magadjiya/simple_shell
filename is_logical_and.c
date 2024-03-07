#include "shell.h"

/**
 * is_logical_and - checks if cmdline has a logical && operator
 * @cmdline: the command line given to the terminal
 *
 * Return: the number of &&, or 0
 */

int is_logical_and(char *cmdline)
{
	int i = 0;
	int count = 0;

	for (i = 0; cmdline[i] != '\0'; i++)
	{
		if (cmdline[i] == '&' && cmdline[i + 1] == '&')
			++count;
	}
	return (count);
}
