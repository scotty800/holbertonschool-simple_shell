#include "shell.h"

/**
 * read_line - Reads a line of input from stdin.
 *
 * Allocates memory for the input buffer and dynamically adjusts its size
 * if needed. Reads characters until a newline or EOF is encountered.
 *
 * Return: A pointer to the input buffer.
 */
char *read_line(void)
{
	int buffsize = INITIAL_BUFFSIZE;
	int position = 0;
	char *buffer = malloc(sizeof(char) * buffsize);
	char *new_buffer;
	int c;

	if (buffer == NULL)
	{
		fprintf(stderr, "dash: Allocation error\n");
		free(buffer);
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
			new_buffer = realloc(buffer, buffsize);
			if (new_buffer == NULL)
			{
				fprintf(stderr, "dash: Allocation error\n");
				free(new_buffer);
				exit(EXIT_FAILURE);
			}
			buffer = new_buffer;
		}
	}
}
