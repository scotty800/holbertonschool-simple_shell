#include "shell.h"

/**
 * prompt_main - Reads a line of input from the user.
 * @input_line: A pointer to a pointer to a
 * buffer where the input will be stored.
 * This function prompts the user with a dollar sign ($), then reads a line
 * of input from stdin using getline. If getline fails, an error message is
 * printed and the program exits.
 */

void prompt_main(char **input_line)
{
	size_t len = 0;
	ssize_t read;
	char *promt = "$ ";

	write(STDIN_FILENO, promt, strlen(promt));
	read = getline(input_line, &len, stdin);

	if (read == -1)
	{
		*input_line = NULL;
		free(*input_line);
		exit(0);
	}
}
