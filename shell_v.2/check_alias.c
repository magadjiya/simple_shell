#include "shell.h"


/**
 * check_alias - checks if an alias exists
 * @aliasHead: the starting position of the linked list of aliases
 * @name: the name of the alias to check
 * Return: 0 on success, -1 on failure
 */

int check_alias(alias *aliasHead, char *name)
{
	alias *tempAlias;

	if (aliasHead == NULL)
		return (-1);

	tempAlias = aliasHead;
	while (tempAlias)
	{
		if (strcmp(name, tempAlias->name) == 0)
			return (0);
		tempAlias = tempAlias->next;
	}

	return (1);
}
