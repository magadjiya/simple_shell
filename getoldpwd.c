#define _GNU_SOURCE
#include "shell.h"

/**
 * getOLDPWD - get the value of the OLDPWD environment variable
 *
 * Return: pointer to the corresponding value string of OLDPWD
 */

char *getOLDPWD(void)
{
	char *varVal;
	char *val = NULL;

	/* Searches the environment variable for PATH */
	varVal = getenv("OLDPWD");
	/* Seperate the variable from the value */
	if (varVal != NULL)
		val = strtok(varVal, "=");
	return (val);
}



