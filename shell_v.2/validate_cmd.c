#include "shell.h"

/**
 * validateCmd - checks if a command exists
 * @cmd: the command to validate
 * @dirHead: pointer to the the linked list of PATH directories
 * @aliasHead: pointer to the linked list of aliases
 *
 * Return: 1 if cmd exits, 0 if it doesn't exist
 */

char *validateCmd(char **cmd, pdir_t **dirHead, alias **aliasHead)
{
	pdir_t *dirPtr;
	/*struct stat st;*/
	char *filePath;
	alias *aliasPtr;
	char *alias_val1, *alias_val2;

	dirPtr = *dirHead;
	aliasPtr = *aliasHead;

	/* Handle different command format */
	switch (**cmd)
	{
		/* Absolute Path */
		case '/':
		/* Relative Path */
		case '.':
			if (access(*cmd, X_OK) == 0)
				return (*cmd);
			else
				return (NULL);
		default:
			/* Check for command in PATH */
			while (dirPtr)
			{
				filePath = absPath(dirPtr->dir, *cmd);
				if (access(filePath, X_OK) == 0)
					return (filePath);
				dirPtr = dirPtr->next_dir;
				free(filePath);
			}
			/* Check for command in alias */
			alias_val1 = get_alias_val(aliasPtr, *cmd);
			if (alias_val1 != NULL)
			{
				alias_val2 = strdup(alias_val1);
				return (alias_val2);
			}

	}
	return (NULL);
}

/**
 * absPath - creates an absolute path for a command
 * @dir: the absolute path of a directory
 * @fileName: the command/file to create an absolute for
 *
 * Return: an absolute path with the file name
 */

char *absPath(char *dir, char *fileName)
{
	char *fullPath;
	size_t dirLen;
	size_t fileLen;
	size_t fullLen;
	size_t i, j;

	if (dir == NULL)
		return (NULL);

	dirLen = strlen(dir);
	fileLen = strlen(fileName);

	/* Dir with and without '/' ending */
	if (dir[dirLen - 1] != '/')
		fullLen = dirLen + 1 + fileLen + 1;
	else
		fullLen = dirLen + fileLen + 1;

	/* abs path looks like -> */
	/* "/usr/bin" + "/" + "ls" */
	fullPath = (char *)malloc(sizeof(char) * fullLen);

	if (fullPath == NULL) /* Handling malloc fail */
		return (NULL);

	for (i = 0; i < dirLen; i++) /* Writing directory */
		fullPath[i] = dir[i];

	if (dir[i - 1] != '/') /* Writing '/' */
	{
		fullPath[i] = '/';
		++i;
	}

	for (j = 0; j < fileLen; j++) /* Writing filename */
		fullPath[j + i] = fileName[j];
	fullPath[i + j] = '\0';

	return (fullPath);
}
