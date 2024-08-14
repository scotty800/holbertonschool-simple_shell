#include "shell.h"
#define MAX_TOKENS 128
#define TOKEN_DELIMITERS " \t\r\n\a"
/**
 * split_token - Splits a line of input into an array of tokens.
 * @input_line: The input string to be tokenized.
 *
 * This function takes an input string and splits it into an array of tokens
 * based on specified delimiters (space, tab, carriage return, newline, and
 * alert). The function dynamically allocates memory for the tokens array and
 * resizes it as needed. If memory allocation fails at any point, the program
 * prints an error message and exits.
 *
 * Return: A null-terminated array of strings (tokens).
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
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOKEN_DELIMITERS);
	}
	tokens[position] = NULL;

	return (tokens);
}
