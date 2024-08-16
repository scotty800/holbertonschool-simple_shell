#include "shell.h"


#define INITIAL_BUFFSIZE 1024
#define MAX_TOKENS 128
#define TOKEN_DELIMITERS " \t\r\n\a"
#define MAX_PATH 256

char *read_line(void);
char **split_token(char *input_line);
int shell_execute(char **args);
int dash_exit(void);
char *shell_path(char *filename);
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
			new_buffer = realloc(buffer, buffsize * sizeof(char));
			if (!new_buffer)
			{
				free(buffer);
				fprintf(stderr, "dash: Allocation error\n");
				exit(EXIT_FAILURE);
			}
			buffer = new_buffer;
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
 * shell_path - Locates the full path of a command.
 * @filename: The command name.
 * This function searches for the command in the directories listed in the
 * PATH environment variable. If found, it returns the full path of the
 * command; otherwise, it returns NULL.
 * Return: A pointer to the full path of the command, or NULL if not found.
 */
char *shell_path(char *filename)
{
	char *path;
	char *path_copy;
	char *dir;
	char *path_full = malloc(MAX_PATH);

	if (path_full == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	path = getenv("PATH");
	if (path == NULL)
	{
		fprintf(stderr, "ERROR: PATH\n");
		free(path_full);
		return (NULL);
	}

	path_copy = _strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup on path");
		free(path_full);
		exit(EXIT_FAILURE);
	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		path_full[0] = '\0';

		_strcat(path_full, dir);
		_strcat(path_full, "/");
		_strcat(path_full, filename);

		if (access(path_full, F_OK) == 0)
		{
			if (access(path_full, X_OK) == 0)
			{
				free(path_copy);
				return (path_full);
			}
			else
			{
				fprintf(stderr, "shell: permission refusée : %s\n", path_full);
				free(path_copy);
				free(path_full);
				return (NULL);
			}
		}

		dir = strtok(NULL, ":");
	}

	free(path_copy);
	free(path_full);
	return (NULL);
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
	char *cmd_path = NULL;

	if (args[0] == NULL)
	{
		return (1);
	}

	if (_strcmp(args[0], "exit") == 0)
	{
		return (0);
	}

	if (args[0][0] == '/' || args[0][0] == '.')
	{
		cmd_path = args[0];
	}
	else
	{

		cmd_path = shell_path(args[0]);
		if (cmd_path == NULL)
		{
			fprintf(stderr, "shell: commande introuvable : %s\n", args[0]);
			return (1);
		}
	}

	if (cmd_path == NULL)
	{
		fprintf(stderr, "shell commande introuvable: %s\n", args[0]);
		return (1);
	}

	cpid = fork();

	if (cpid == 0)
	{
		if (execve(cmd_path, args, envp) == -1)
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
	if (cmd_path != args[0])
	{

		free(cmd_path);
	}

	return (1);
}

/**
 * dash_exit - Exits the shell program.
 * This function terminates the shell by calling exit with EXIT_SUCCESS.
 * Return: exit_SUCCESS
 */
int dash_exit(void)
{
	exit(EXIT_SUCCESS);
}

