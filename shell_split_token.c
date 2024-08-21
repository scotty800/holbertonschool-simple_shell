#include "shell.h"

/**
 * split_token - Splits an input line into tokens.
 * @input_line: The line of input to split.
 *
 * Uses strtok to split the input line into tokens based on defined delimiters.
 * Allocates memory for the tokens and dynamically adjusts the size of the
 * memory block if needed.
 *
 * Return: An array of tokens (null-terminated).
 */
char **split_token(char *input_line)
{
	char *token;
	char **tokens;
	int buffer = MAX_TOKENS;
	int position = 0;

	tokens = malloc(buffer * sizeof(char *));
	if (tokens == NULL)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(input_line, TOKEN_DELIMITERS);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= buffer)
		{
			buffer += MAX_TOKENS;
			tokens = realloc(tokens, buffer * sizeof(char *));
			if (tokens == NULL)
			{
				fprintf(stderr, "Allocation error\n");
				free(tokens);
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOKEN_DELIMITERS);
	}
	tokens[position] = NULL;

	return (tokens);
}
