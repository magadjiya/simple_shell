#include "shell.h"


/**
 * get_alias_name - checks for an alias and in an alias
 * set and return only the name
 * @aliasHead: the starting position of the linked list of aliases
 * @alias_set: the name and value of the alias to check
 * Return: 0 on success, -1 on failure
 */

char *get_alias_name(alias *aliasHead, char *alias_set)
{
	char *alias_cp = strdup(alias_set);
	char *alias_name;
	alias *tempAlias;

	alias_name = strtok(alias_cp, "=");
	tempAlias = aliasHead;

	while (tempAlias)
	{
		if (strcmp(alias_name, tempAlias->name) == 0)
		{
			free(alias_cp);
			return (tempAlias->name);
		}
		tempAlias = tempAlias->next;
	}
	free(alias_cp);
	return (alias_set);
}

/**
 * get_alias_val - checks if an alias exists
 * @aliasHead: the starting position of the linked list of aliases
 * @name: the name of the alias to check
 * Return: 0 on success, -1 on failure
 */

char *get_alias_val(alias *aliasHead, char *name)
{
	alias *tempAlias;
	char *alias_val;

	if (aliasHead == NULL)
		return (NULL);

	tempAlias = aliasHead;
	while (tempAlias)
	{
		if (strcmp(name, tempAlias->name) == 0)
		{
			alias_val = tempAlias->value;

			if (check_alias(aliasHead, alias_val) == 0)
			{
				name = alias_val;
				tempAlias = aliasHead;
				continue;
			}
			else
				return (tempAlias->value);
		}
		else
			tempAlias = tempAlias->next;
	}

	return (NULL);
}
