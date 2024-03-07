#include "shell.h"

char **get_alias(char *cmdline);

/**
 * is_alias - checks if cmdline is "alias" and handles process the command
 * @cmdline: the command line given to the terminal
 * @aliasHead: pointer to list of all aliases in the process
 *
 * Return: 1 if setenv is successful, 0 if not
 */

int is_alias(char *cmdline, alias **aliasHead)
{
	char *linecp;
	int i, status = 0;
	char *alias_name = NULL;
	char *alias_val = NULL;
	char *alias_set = NULL;
	char **alias_arr = NULL;
	char *line = strdup(cmdline);

	linecp = strtok(line, "\n");

	if (strncmp(linecp, "alias", 5) == 0)
	{
		alias_arr = get_alias(linecp);

		if (alias_arr[1] == NULL)
		{
			print_alias_all(aliasHead);
			free(alias_arr);
			free(line);
			return (0);
		}

		for (i = 1; alias_arr[i] != NULL; i++)
		{
			alias_set = alias_arr[i];
			alias_name = get_alias_name(*aliasHead, alias_set);
			alias_val = strtok(alias_set, "=");
			alias_val = strtok(NULL, "=");

			/* Check if alias name exists */
			if (check_alias(*aliasHead, alias_name) == 0)
			{
				/* If alias has value - update the alias */
				if (alias_val != NULL)
				{
					update_alias(aliasHead, alias_name, alias_val);
				}
				else /* Print the alias */
					print_alias(*aliasHead, alias_name);
			}
			else
			{
				/* If alias has a value - define a new alias */
				if (alias_val != NULL)
					*aliasHead = add_alias(aliasHead, alias_name, alias_val);
				else /* Display error message */
				{
					status = 2;
					fprintf(stderr, "alias: %s not found\n", alias_name);
				}
			}
		}
		free(alias_arr);
		free(line);
		return (status);
	}

	free(line);
	return (1);
}


/**
 * get_alias - gets the list of aliases given to the alias command
 * @cmdline: the command line given to the terminal
 *
 * Return: a pointer to a list of aliases
 */

char **get_alias(char *cmdline)
{
	char *line;
	char **arr;
	int i = 0;

	arr = (char **)malloc(sizeof(char *));
	if (arr == NULL)
		return (NULL);

	line = strtok(cmdline, " ");

	while (line)
	{
		arr[i] = line;
		line = strtok(NULL, " ");
		++i;
		arr = (char **)reallocarray(arr, i + 1, sizeof(char *));
		if (arr == NULL)
		{
			free(arr);
			return (NULL);
		}
	}
	arr[i] = NULL;
	return (arr);
}




