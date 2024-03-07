#include "shell.h"

/**
 * print_alias_all - prints all the aliases in the alias list
 * @aliasHead: the starting position of the linked list of aliases
 * Return: 0 on success, -1 on failure
 */

int print_alias_all(alias **aliasHead)
{
	alias *tempAlias;

	if (aliasHead == NULL)
		return (-1);

	tempAlias = *aliasHead;
	while (tempAlias)
	{
		printf("%s='%s'\n", tempAlias->name, tempAlias->value);
		tempAlias = tempAlias->next;
	}

	return (1);
}
