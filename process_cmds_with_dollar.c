#include "shell.h"
int count_digit(int i);
/**
 * processCmds_withDollar - handles the processing of commands
 * containing the command replacement operator $
 * @cmdline: the line of command to process
 * @cmdstatus: the status of the last command run
 * @argv: array of arguments to shell program
 * @dirHead: the head of the path directory linked list
 * @envp: the array of environment variables
 * @aliasHead: pointer to the linked list of aliases
 * @pathValcpy: copy of directory string in PATH
 *
 * Return: 0 on success, -1 on failure
 */

int processCmds_withDollar(char *cmdline, int cmdstatus, char **argv, pdir_t **dirHead,
		char *envp[], alias **aliasHead, char *pathValcpy)
{
	char *cmdcpy;
	char *arg = NULL;
	char *fullarg = NULL;
	char fullCmd[1024];
	char **arr = NULL;
	size_t cmdlen = strlen(cmdline);
	size_t h = 0, i = 0, j = 0, k = 0, l, m = 0;
	int status = 0;

	cmdcpy = strdup(cmdline);
	cmdcpy[cmdlen - 1] = '\0';

	while (cmdcpy[h] != '\0')
	{
		i = 0;
		while (cmdcpy[h + i] != '$' && cmdcpy[h + i] != '\0')
			i++;
		for (j = 0; j < i; j++)
			fullCmd[j + m] = cmdcpy[h + j];
		i++;
		k = 0;
		while (cmdcpy[h + i + k] != ' ' && cmdcpy[h + i + k] != '\0')
			k++;
		if (k == 0)
			fullCmd[j + m]  = cmdcpy[h + j];
		arg = (char *)malloc(sizeof(char) * (k + 1));
		for (j = 0; j < k; j++)
			arg[j] = cmdcpy[h + i + j];
		arg[j] = '\0';
		fullarg = expand_var(arg, cmdstatus);
		--i;
		if (fullarg == NULL)
		{
			if (k == 0)
				fullCmd[i + m + 1] = '\0';
			else
				fullCmd[i + m] = '\0';
		}
		else
		{
			for (j = 0; fullarg[j] != '\0'; j++)
				continue;
			l = j;
			for (j = 0; j < l; j++)
				fullCmd[i + j + m] = fullarg[j];
			fullCmd[i + j + m]  = '\0';
		}
		if (k == 0)
			m = m + i + j + 1;
		else
			m = m + i + j;
		++i;
		i = i + k;
		h = h + i;
		if (arg[0] == '?' || arg[0] == '$')
			free(fullarg);
		free(arg);
		arg = NULL;
	}
	arr = createArgsArr(fullCmd);
	status = processCmds(arr, cmdline, argv, dirHead,
			envp, aliasHead, pathValcpy);
	free(cmdcpy);
	return (status);
}


/**
 * expand_var - expands the variable pointed to by the $ character
 * @c: the string of character that determines the expansion
 * @cmdstatus: the status of the last executed command
 *
 * Return: expanded string
 */

char *expand_var(char c[], int cmdstatus)
{
	char *fullCmd = NULL;
	char *env = NULL;
	pid_t pid = getpid();

	if (c[0] == '\0')
		return (NULL);

	if (strcmp(c, "?") == 0)
	{
		fullCmd = int_to_str(cmdstatus);
		return (fullCmd);
	}
	else if (strcmp(c, "$") == 0)
	{
		fullCmd = int_to_str(pid);
		return (fullCmd);
	}
	else
	{
		env = getenv(c);
		if (env != NULL)
			return (env);
		return (NULL);
	}
}

/**
 * int_to_str - converts an integer to a string of characters
 * @i: the integer number
 *
 * Return: the string value of the integer
 */

char *int_to_str(int i)
{
	/*char unit[2];
	char hun[4];*/
	int count = 0;
	/*char strcmd[10];*/
	char *s;
	/* Converts the integer value to string */
	/*if (i >= 0 || i <= 2)
	{
		sprintf(unit, "%d", i);
		unit[1] = '\0';
		str = unit;
	}
	else if (i == 127)
	{
		sprintf(hun, "%d", i);
		hun[3] = '\0';
		str = hun;
	}*/
	count = count_digit(i);
	s = (char *)malloc(sizeof(char) * (count + 1));
	sprintf(s, "%d", i);
	/*strcmd[count] = '\0';*/
	/*str = strcmd;*/
	s[count] = '\0';
	return (s);
}

int count_digit(int i)
{
	int j = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		i /= 10;
		++j;
	}
	return (j);
}

