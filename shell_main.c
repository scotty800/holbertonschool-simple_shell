#include "shell.h"

/**
 * main - Entry point of the shell program.
 *
 * The main function continuously prompts the user for input, reads the
 * input line, splits it into tokens, and then executes the command.
 * The loop continues until the `shell_execute` function returns 0.
 *
 * Return: Always EXIT_SUCCESS.
 */
int main(void)
{
	char *input_line = NULL;
	char **args;
	int status = 1;

	while (status)
	{
		prompt_main(&input_line);

		if (input_line == NULL || *input_line == '\0')
		{
			free(input_line);
			input_line = NULL;
			break;
		}

		args = split_token(input_line);

		if (args == NULL || args[0] == NULL)
		{
			free(input_line);
			free(args);
			continue;
		}

		if (_strcmp(args[0], "exit") == 0)
		{
			free(input_line);
			free(args);
			break;
		}
		status = shell_execute(args);
		free(input_line);
		free(args);
	}

	return (EXIT_SUCCESS);
}
