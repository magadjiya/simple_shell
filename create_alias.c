#include "shell.h"

/**
 * addAlias - adds an alias to a list of aliases available to the process
 * @aliasHead: the starting position of the alias list
 * @name: the name of the alias
 * @val: the value of the alias
 *
 * Return: a pointer to an alias type list
 */

alias *add_alias(alias **aliasHead, char *name, char *val)
{
	add_alias_end(aliasHead, name, val);
	return (*aliasHead);
}


/**
 * add_alias_end - adds an alias to the end of the alias list
 * @aliasHead: the starting position of the alias list
 * @name: the name of the alias to add to the alias list
 * @val: the value of the alias to be added
 *
 * Return: pointer to updated list
 */

alias *add_alias_end(alias **aliasHead, char *name, char *val)
{
	alias *newAlias, *aliasPtr;
	char *alias_name, *alias_val;
	int i;

	if (aliasHead == NULL || name == NULL || val == NULL)
		return (NULL);

	newAlias = (alias *)malloc(sizeof(alias));
	if (newAlias == NULL)
		return (NULL);

	alias_name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
	alias_val = (char *)malloc(sizeof(char) * (strlen(val) + 1));
	if (alias_name == NULL || alias_val == NULL)
		return (NULL);
	for (i = 0; name[i] != '\0'; i++)
		alias_name[i] = name[i];
	alias_name[i] = '\0';
	for (i = 0; val[i] != '\0'; i++)
		alias_val[i] = val[i];
	alias_val[i] = '\0';

	newAlias->name = alias_name;
	newAlias->value = alias_val;

	if (*aliasHead == NULL)
	{
		newAlias->next = (*aliasHead);
		(*aliasHead) = newAlias;
	}
	else
	{
		aliasPtr = *aliasHead;
		while (aliasPtr->next != NULL)
			aliasPtr = aliasPtr->next;
		newAlias->next = aliasPtr->next;
		aliasPtr->next = newAlias;
	}
	aliasPtr = *aliasHead;
	return (*aliasHead);
}


/**
 * update_alias - updates the value of an alias
 * @aliasHead: the starting position of the alias list
 * @name: the name of the alias to add to the alias list
 * @val: the value of the alias to be added
 *
 * Return: pointer to updated list
 */

alias *update_alias(alias **aliasHead, char *name, char *val)
{
	alias *aliasPtr;
	char *alias_val = NULL;
	int i;

	if (aliasHead == NULL || name == NULL || val == NULL)
		return (NULL);

	aliasPtr = *aliasHead;

	alias_val = (char *)malloc(sizeof(char) * (strlen(val) + 1));
	if (alias_val == NULL)
		return (NULL);

	for (i = 0; val[i] != '\0'; i++)
		alias_val[i] = val[i];
	alias_val[i] = '\0';

	while (aliasPtr)
	{
		if (aliasPtr->name == name)
		{
			free(aliasPtr->value);
			aliasPtr->value = alias_val;
			return (*aliasHead);
		}
	}
	return (*aliasHead);
}


/**
 * free_alias - frees a linked list of type alias
 * @aliasHead: the starting position of the linked list
 *
 * Return: nothing
 */

int free_alias(alias *aliasHead)
{
	alias *tempAlias;

	if (aliasHead == NULL)
		return (-1);

	while (aliasHead)
	{
		tempAlias = aliasHead;
		aliasHead = aliasHead->next;
		free(tempAlias->name);
		free(tempAlias->value);
		free(tempAlias);
	}

	return (0);
}


