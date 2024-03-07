#include "shell.h"

/**
 * isNewline - checks if the command is just a newline character
 * @line: the command line
 *
 * Return: 1 if TRUE, 0 if FALSE
 */

int isNewline(char *line)
{
	/* No command - jusy newline */
	if (*line == '\n')
	{
		/*free(line);*/
		return (1);
	}
	return (0);
}
