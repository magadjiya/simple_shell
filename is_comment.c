#include "shell.h"

/**
 * is_comment - checks if cmdline has a # character
 * @cmdline: the command line given to the terminal
 *
 * Return: the number of #, or 0
 */

int is_comment(char *cmdline)
{
	int i = 0;
	int count = 0;

	for (i = 0; cmdline[i] != '\0'; i++)
	{
		if (i == 0)
		{
			if (cmdline[i] == '#' && cmdline[i + 1] == ' ')
				++count;
		}
		else if (i > 0)
		{
			if (cmdline[i] == '#' && cmdline[i - 1] == ' ')
				++count;
		}
	}
	return (count);
}
