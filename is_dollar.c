#include "shell.h"

/**
 * is_dollar - checks if cmdline has a command replacement $ operator
 * @cmdline: the command line given to the terminal
 *
 * Return: the number of $, or 0
 */

int is_dollar(char *cmdline)
{
	int i = 0;
	int count = 0;

	for (i = 0; cmdline[i] != '\0'; i++)
	{
		if (cmdline[i] == '$')
			++count;
	}
	return (count);
}
