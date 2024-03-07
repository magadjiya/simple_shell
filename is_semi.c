#include "shell.h"

/**
 * is_semi - checks if cmdline has a semicolon
 * @cmdline: the command line given to the terminal
 *
 * Return: the number of semicolons, or 0
 */

int is_semi(char *cmdline)
{
	int i = 0;
	int count = 0;

	for (i = 0; cmdline[i] != '\0'; i++)
	{
		if (cmdline[i] == ';')
			++count;
	}
	return (count);
}
