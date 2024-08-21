#include "shell.h"

/**
 * shell_execute - Executes a command based on user input.
 * @args: An array of command arguments Forks a child process to execute
 * is "exit", the shell terminates. Handles errors by printing error messages
 * Return: 1 if the shell should continue running, 0 if it should exit.
 */
int shell_execute(char **args)
{
	pid_t cpid;
	int status;
	char *envp[] = {NULL};
	char *cmd_path = NULL;

	cpid = fork();
	if (cpid < 0)
	{
		perror("shell");
		return (1);
	}

	if (cpid == 0)
	{
		if (args[0] == NULL)
			exit(EXIT_FAILURE);

		if (_strcmp(args[0], "exit") == 0)
			exit(EXIT_SUCCESS);

		if (args[0][0] == '/' || args[0][0] == '.')
		{
			cmd_path = _strdup(args[0]);
			if (cmd_path == NULL)
			{
				perror("shell");
				free(cmd_path);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			cmd_path = shell_path(args[0]);
			if (cmd_path == NULL)
			{
				fprintf(stderr, "shell: commande introuvable : %s\n", args[0]);
				exit(EXIT_FAILURE);
			}
		}

		if (execve(cmd_path, args, envp) == -1)
		{
			perror("shell");
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(cpid, &status, WUNTRACED);
	}

	if (cmd_path != NULL && cmd_path != args[0])
	{
		free(cmd_path);
	}

	return (1);
}
