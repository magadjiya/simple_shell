#include "shell.h"

/**
 * is_cd - checks if the command is "cd" and processes the command
 * @cmdline: the command line given to the terminal
 *
 * Return: 0 on success, 1 on failure
 */

int is_cd(char *cmdline)
{
	char *line, *linecp;
	char *home, *pwd, *oldpwd;
	char *dir_arg, *new_dir;

	home = getHOME();
	pwd = getPWD();
	oldpwd = getOLDPWD();
	line = strdup(cmdline);
	linecp = strtok(line, "\n");

	if (strncmp(linecp, "cd", 2) == 0)
	{
		dir_arg = strtok(linecp, " ");
		dir_arg = strtok(NULL, " ");

		if (dir_arg == NULL)
		{
			new_dir = home;
			oldpwd = pwd;
		}
		else
		{
			if (*dir_arg == '-')
			{
				new_dir = oldpwd;
				if (new_dir == NULL)
				{
					/*fprintf(stderr, "./hsh: cd: OLDPWD not set\n");*/
					free(line);
					return (2);
				}
				else
					oldpwd = pwd;
			}
			else
			{
				if (strcmp(dir_arg, pwd) == 0)
				{
					free(line);
					return (0);
				}
				else
				{
					oldpwd = pwd;
					new_dir = dir_arg;
				}
			}
		}
		if (new_dir == NULL) /* Handle empty directory */
		{
			free(line);
			return (0);
		}
		if (chdir(new_dir) == -1) /* Handle non existing directories and directories without permission */
		{
			fprintf(stderr, "./hsh: 1: cd: can't cd to %s\n", new_dir);
			free(line);
			return (0);
		}
		setenv("PWD", new_dir, 1);
		setenv("OLDPWD", oldpwd, 1);
		free(line);
		return (0);
	}
	free(line);
	return (1);
}

/**
 * oldpwd_not_set - prints error message if oldpwd is not set when
 * a user attempts to change to oldpwd and cleans up.
 * @line: a pointer to clean up
 *
 * Return: 2
 */
