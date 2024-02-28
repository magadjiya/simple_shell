#include "shell.h"

/**
 * makePathList - makes linked list of all the directories in the PATH variable
 * @pathVal: the directories of the PATH variable
 *
 * Return: 0 on success, 1 on failure
 */

pdir_t *makePathList(char *pathVal)
{
	char *dir;
	pdir_t *dirHead = NULL;

	dir = strtok(pathVal, ":");
	while (dir)
	{
		dirHead = add_dir_end(&dirHead, dir);
		dir = strtok(NULL, ":");
	}
	return (dirHead);
}

/**
 * add_dir - adds a directory to the front of the linked list
 * @dirHead: the starting position of the linked list
 * @dir: the directory string to add to the linked list
 *
 * Return: pointer to updated list
 */

pdir_t *add_dir(pdir_t **dirHead, char *dir)
{
	pdir_t *newDir;

	if (dirHead == NULL)
		return (NULL);

	newDir = (pdir_t *)malloc(sizeof(pdir_t));
	if (newDir == NULL)
		return (NULL);

	newDir->dir = dir;
	newDir->next_dir = (*dirHead);
	(*dirHead) = newDir;
	return (*dirHead);
}


/**
 * add_dir_end - adds a directory to the end of the linked list
 * @dirHead: the starting position of the linked list
 * @dir: the directory string to add to the linked list
 *
 * Return: pointer to updated list
 */
pdir_t *add_dir_end(pdir_t **dirHead, char *dir)
{
	pdir_t *newDir;
	pdir_t *dirPtr;

	if (dirHead == NULL)
		return (NULL);

	newDir = (pdir_t *)malloc(sizeof(pdir_t));
	if (newDir == NULL)
		return (NULL);

	newDir->dir = dir;
	if (*dirHead == NULL)
	{
		newDir->next_dir = (*dirHead);
		(*dirHead) = newDir;
	}
	else
	{
		dirPtr = *dirHead;
		while (dirPtr->next_dir != NULL)
			dirPtr = dirPtr->next_dir;
		newDir->next_dir = dirPtr->next_dir;
		dirPtr->next_dir = newDir;
	}
	return (*dirHead);
}


/**
 * free_pdir - frees a linked list of type pdir_t
 * @dirHead: the starting position of the linked list
 *
 * Return: nothing
 */

int free_pdir(pdir_t *dirHead)
{
	pdir_t *tempDir;

	if (dirHead == NULL)
		return (-1);

	while (dirHead)
	{
		tempDir = dirHead;
		dirHead = dirHead->next_dir;
		free(tempDir);
	}

	return (0);
}
