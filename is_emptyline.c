#include "shell.h"

/**
 * isEmpty - checks if command line is empty
 * @line: the line
 * Return: 1, if empty, 0 if not
 */
int isEmpty(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);

	/* "{}{}{}{}/bin/ls{}{}{}{}/bin/ls... */

}
