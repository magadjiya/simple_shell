#define _GNU_SOURCE
#include "shell.h"

/**
 * getHOME - get the value of the HOME environment variable
 *
 * Return: pointer to the corresponding value string of HOME
 */

char *getHOME(void)
{
	char *varVal;
	char *val = NULL;

	/* Searches the environment variable for PATH */
	varVal = getenv("HOME");
	/* Seperate the variable from the value */
	if (varVal != NULL)
		val = strtok(varVal, "=");
	return (val);
}



