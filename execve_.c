#include "shell.h"

int main(int ac, char *argv[])
{
	(void)ac;
	(void)argv;
	char *argarr[4] = {"/bin/ls", "-lpzkfad", "/home/danlinux/ALX/simple_shell", NULL};
	char *line;
	size_t n = 0, nbytes;
	savecmd_t *argarr2 = NULL;
	int i;
	(void) argarr;


	printf("$: ");

	nbytes = getline(&line, &n, stdin);
	while (nbytes)
	{
		line[nbytes - 1] = '\0'; /* line = strtok(line, "\n"); */
		/* line -> "/bin/ls -l" */
		/* FROM */
		/* argarr = {"/bin/ls -l", NULL} */
		/* TO */
		/* argarr = {"/bin/ls", "-l", NULL} */

		line = strtok(line, " ");
		/* line --> /bin/ls */
		while (line != NULL)
		{

			line = strtok(NULL, " ");
			/* line --> -l */
		}

				
		/* line --> "/bin/ls" */
		i = execve(argarr2[0], argarr2, NULL);
		if (i == -1)
			break;
	}
	return (0);
}

