#include "shell.h"

/**
 * validateCmd - checks if a command exists
 * @cmd: the command to validate
 *
 * Return: 1 if cmd exits, 0 if it doesn't exist
 */

char *validateCmd(char *cmd)
{
	char *path_val;
	pdir_t *dirList, *tempDir;
	struct stat st;
	char *filePath;

	path_val = getPATH(); /* Access the PATH variable */
	/* Create a linked list of the directories in PATH */
	dirList = makePathList(path_val);

	/* Handle different command format */
	switch (*cmd)
	{
		/* Absolute Path */
		case '/':
		/* Relative Path */
		case '.':
			free_pdir(dirList);
			if (lstat(cmd, &st) == 0)
				return (cmd);
			else
				return (NULL);
		default:
			while (dirList)
			{
				filePath = absPath(dirList->dir, cmd);
				printf("filepath %s\n", filePath);
				if (lstat(filePath, &st) == 0)
				{

					free_pdir(dirList);
					return (filePath);
				}
				tempDir = dirList;
				dirList = dirList->next_dir;
				free(tempDir);
				free(filePath);
			}
	}
	free_pdir(dirList);
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
