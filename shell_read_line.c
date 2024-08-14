#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"
#define INITIAL_BUFFSIZE 1024
/**
 * read_line - Reads a line of input from standard input.
 *
 * This function reads characters from standard input until a newline or EOF
 * is encountered. It dynamically allocates memory to store the input line,
 * resizing the buffer as needed. If an allocation error occurs, an error
 * message is printed, and the program exits.
 *
 * Return: A pointer to the null-terminated string containing the input line.
 */
char *read_line()
{
	int buffsize = INITIAL_BUFFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * buffsize);
	int c;

	if (!buffer)
	{
		fprintf(stderr, "dash: Allocation error\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		c = getchar();

		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			return (buffer);
		}

		else
		{
			buffer[position] = c;
		}
		position++;

		if (position >= buffsize)
		{
			buffsize += INITIAL_BUFFSIZE;
			buffer = realloc(buffer, buffsize);
			if (!buffer)
			{
				fprintf(stderr, "dash: Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

