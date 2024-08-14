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
int dash_exit();

int main(void)
{
	char *input_line = NULL;
	char **args;
	int status = 1;

	while (status)
	{
		printf("$ ");

		input_line = read_line();

		if (input_line == NULL || *input_line == '\0') {
			free(input_line);
			continue;
		}

		args = split_token(input_line);

		status = shell_execute(args);

		free(input_line);
		free(args);
	}

	return EXIT_SUCCESS;
}

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
			return buffer;
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

char **split_token(char *input_line)
{
	char *token;
	char **tokens;
	int buffer = MAX_TOKENS;
	int position = 0;

	tokens = malloc(buffer * sizeof(char*));
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
			tokens = realloc(tokens, buffer * sizeof(char*));
			if (tokens == NULL)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, TOKEN_DELIMITERS);
	}
	tokens[position] = NULL;

	return tokens;
}

int shell_execute(char **args)
{
	pid_t cpid;
	int status;

	if (args[0] == NULL)
	{
		return 1;
	}

	if (strcmp(args[0], "exit") == 0)
	{
		dash_exit();
	}

	cpid = fork();

	if (cpid == 0)
	{
		if (execvp(args[0], args) < 0)
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

	return 1;
}

int dash_exit()
{
	exit(EXIT_SUCCESS);
}
