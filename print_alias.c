#include "shell.h"

/**
 * print_alias - prints an alias
 * @aliasHead: the starting position of the linked list of aliases
 * @name: the name of the alias to print
 *
 * Return: 0 on success, -1 on failure
 */

int print_alias(alias *aliasHead, char *name)
{
	alias *tempAlias;

	if (aliasHead == NULL)
		return (-1);

	tempAlias = aliasHead;
	while (tempAlias)
	{
		if (strcmp(name, tempAlias->name) == 0)
		{
			printf("%s='%s'\n", tempAlias->name, tempAlias->value);
			return (0);
		}
		tempAlias = tempAlias->next;
	}

	return (1);
}
