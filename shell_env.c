#include "shell.h"

/**
 * shell_env - Prints the current environment variables.
 * Return: Always 1 (to continue executing the shell).
 */

int shell_env(void)
{
	int index = 0;
	char **env = environ;

	for (index = 0; env[index] != NULL; index++)
	{
		printf("%s\n", env[index]);
	}
	return (1);
}
