#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"
/**
 * shell_execute - Executes a shell command.
 * @args: A NULL-terminated array of arguments (command and its options).
 *
 * This function creates a child process using fork() to execute a command
 * provided by the user. If the command is a built-in command like "exit",
 * the corresponding function is called. For other commands, the function
 * tries to execute them using execvp(). The parent process waits for the
 * child process to complete. If fork() fails, an error message is printed.
 *
 * Return: 1 if the shell should continue running, or a different value if
 * the shell should terminate.
 */
int shell_execute(char **args)
{
	pid_t cpid;
	int status;

	if (strcmp(args[0], "exit") == 0)
	{
		return (dash_exit());
	}

	cpid = fork();

	if (cpid == 0)
	{

		if (execvp(args[0], args) < 0)
		{
			perror("shell");
		}
		exit(EXIT_FAILURE);
	} else if (cpid < 0)

	{

		perror("shell");
	} else
	{
		waitpid(cpid, &status, WUNTRACED);
	}

	return (1);
}
