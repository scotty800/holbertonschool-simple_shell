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
	char *cmd_path = NULL;

	if (_strcmp(args[0], "exit") == 0)
		return (dash_exit());
	if (_strcmp(args[0], "env") == 0)
		return (shell_env());
	if (args[0][0] == '/' || args[0][0] == '.')
		cmd_path = args[0];
	else
	{
		cmd_path = shell_path(args[0]);
		if (cmd_path == NULL)
		{
			fprintf(stderr, "shell: commande introuvable : %s\n", args[0]);
			exit(127);
			return (1);
		}
	}
	cpid = fork();
	if (cpid == 0)
	{
		if (execve(cmd_path, args, environ) < 0)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (cpid < 0)
	{
		perror("shell");
		return (1);
	}
	else
	{
		if (waitpid(cpid, &status, WUNTRACED) == -1)
			perror("waitpid");
	}
	return (1);
}
