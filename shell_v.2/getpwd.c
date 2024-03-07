#define _GNU_SOURCE
#include "shell.h"

/**
 * getPWD - get the value of the PWD environment variable
 *
 * Return: pointer to the corresponding value string of PWD
 */

char *getPWD(void)
{
	char *varVal;
	char *val = NULL;

	/* Searches the environment variable for PATH */
	varVal = getenv("PWD");
	/* Seperate the variable from the value */
	if (varVal != NULL)
		val = strtok(varVal, "=");
	return (val);
}



