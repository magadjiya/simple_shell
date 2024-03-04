#include "shell.h"

/**
 * _unsetenv - a shell builtin to remove an environment variable
 * @varName: the name of the environment variable
 *
 * Return: 0 on success, -1 on failure
 */

int _unsetenv(char *varName)
{
	char *oldval = NULL;
	int exec_status = 0;

	/* STEP 1 -> Check for NULL */
	if (varName == NULL)
		return (0);

	/* STEP 2 -> Check if varName already exists as an environment variable */
	oldval = getenv(varName);

	if (oldval == NULL) /* Var does not exist */
		return (0);

	else /* Var exists */
	{
		exec_status = unsetenv(varName);
		if (exec_status == -1)
			perror("./hsh");
	}

	return (exec_status);
}
