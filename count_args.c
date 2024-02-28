#include "shell.h"

/**
 * countArgs - counts the number of arguments in  an array
 * @arr: the array of arguments
 *
 * Return: the number of arguments in the array
 */

int countArgs(char **arr)
{
	int i = 0;

	while (arr[i] != NULL)
		++i;
	return (i);
}
