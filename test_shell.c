#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define INITIAL_BUFFSIZE 1024
#define MAX_TOKENS 128
#define TOKEN_DELIMITERS " \t\r\n\a"

char *read_line();
char **split_token(char *input_line);
int shell_execute(char **args);
int dash_exit(void);
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
		printf("$ ");

		input_line = read_line();

		if (input_line == NULL || *input_line == '\0')
		{
			free(input_line);
			continue;
		}

		args = split_token(input_line);

		status = shell_execute(args);

		free(input_line);
		free(args);
	}

	return (EXIT_SUCCESS);
}
/**
 * read_line - Reads a line of input from stdin.
 *
 * Allocates memory for the input buffer and dynamically adjusts its size
 * if needed. Reads characters until a newline or EOF is encountered.
 *
 * Return: A pointer to the input buffer.
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
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOKEN_DELIMITERS);
	}
	tokens[position] = NULL;

	return (tokens);
}
/**
 * shell_execute - Executes a command based on user input.
 * @args: An array of command arguments.
 *
 * Forks a child process to execute the command using execvp. If the command
 * is "exit", the shell terminates. Handles errors by printing error messages
 * and waiting for child processes to complete.
 *
 * Return: 1 if the shell should continue running, 0 if it should exit.
 */
int shell_execute(char **args)
{
	pid_t cpid;
	int status;
	char *envp[] = {NULL};

	if (args[0] == NULL)
	{
		return (1);
	}

	if (strcmp(args[0], "exit") == 0)
	{
		dash_exit();
	}

	cpid = fork();

	if (cpid == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			perror("shell");
		}
		exit(EXIT_FAILURE);
	}
	else if (cpid < 0)
	{
		perror("shell");
	}
	else
	{
		waitpid(cpid, &status, WUNTRACED);
	}

	return (1);
}
/**
 * dash_exit - Exits the shell program.
 *
 * This function terminates the shell by calling exit with EXIT_SUCCESS.
 */
int dash_exit(void)
{
	exit(EXIT_SUCCESS);
}
