#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * _getline - reads a line from standard input
 * @lineptr: stores the line here
 * @n: number of bytes read
 * @stream: file descriptor to read from
 *
 * Return: n, On success, -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int i, rbytes, fd;
	char buf[1024]; /* Read this at once to avoid many syscalls */

	if (*lineptr == NULL || *n == 0)
	{
		*n = 1; /* allocate for at least one byte */
		*lineptr = malloc(*n * sizeof(char));
		if (*lineptr == NULL)
			return (-1);
	}

	/* read from standard input */
	fd = fileno(stream); /* write _fileno func */
	rbytes = read(fd, buf, sizeof(buf));
	if (rbytes == -1)
		return (-1);

	/* resize as needed */
	*n = rbytes;
	*lineptr = realloc(*lineptr, *n);
	if (*lineptr == NULL)
		return (-1);

	/* store values in lineptr */
	i = 0;
	while (buf[i] != '\n')
	{
		(*lineptr)[i] = buf[i];
		i++;
	}
	(*lineptr)[i] = '\n';

	return (*n);
}
