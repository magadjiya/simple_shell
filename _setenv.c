#include "shell.h"

/**
 * _setenv - a shell builtin to initialize a new environment
 * variable or modify an existing one
 * @varName: the name of the environment variable
 * @val: the value of the environment variable
 *
 * Return: 0 on success, -1 on failure
 */

int _setenv(char *varName, char *val)
{
	char *oldval = NULL;
	int exec_status = 0;

	/* STEP 1 -> Check for NULL */
	if (varName == NULL)
		return (0);

	/* STEP 2 -> Check if varName already exists as an environment variable */
	oldval = getenv(varName);

	if (oldval == NULL) /* Var does not exist */
	{
		exec_status = setenv(varName, val, 0);
		if (exec_status == -1)
			perror("./hsh");
	}
	else /* Var exists */
	{
		exec_status = setenv(varName, val, 1);
		if (exec_status == -1)
			perror("./hsh");
	}

	return (exec_status);
}
