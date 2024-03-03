#define _GNU_SOURCE
#include "shell.h"

/**
 * getPATH - get the value of the PATH environment variable
 *
 * Return: pointer to the corresponding value string of PATH
 */

char *getPATH(void)
{
	char *varVal;
	char *val = NULL;

	/* Searches the environment variable for PATH */
	varVal = getenv("PATH");
	/* Seperate the variable from the value */
	if (varVal != NULL)
		val = strtok(varVal, "=");
	return (val);
}



