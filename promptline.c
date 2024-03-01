#include "shell.h"

/**
 * promptline - displays a "$" sign and waits for user command.
 * Stores the command in a buffer
 * @line: the command line argument
 *
 * Return: pointer to the buffer containing commandline or NULL
 */

char *promptline(char *line)
{
	size_t n =  0;
	char *new_line;

	if (line != NULL)
	{
		free(line);
		line = NULL;
	}

	/*printf("$ ");*/
	write(STDOUT_FILENO, "$ ", 2);
	if ((getline(&line, &n, stdin)) == -1)
	{
		free(line);
		return (NULL);
	}

	new_line = noWhiteSpaces(line);
	if (new_line != line)
		free(line);
	return (new_line);
}

/**
 * noWhiteSpaces - removes any whitespaces before a command
 * @line: the command passed to the terminal
 * Return: the modified command if any whitespaces
 */
char *noWhiteSpaces(char *line)
{
	int i, j, rlen, len;
	char *rline;

	len = strlen(line);
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
		{
			rlen = len - i;
			rline = malloc((rlen + 1) * sizeof(char));
			/* Handle malloc fail */
			if (rline == NULL)
			{
				/*free(rline);*/
				return (NULL);
			}

			j = 0;
			/* Write all the characters from the next non-space character */
			while (line[i] != '\0')
			{
				rline[j] = line[i];
				j++;
				i++;
			}
			rline[j] = '\0';
			return (rline);
		}
		i++;
	}

	return (line);
}
