#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"
int shell_execute(char * * args)
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
			perror("shell");
		exit(EXIT_FAILURE);
	}
	else if (cpid < 0)
		perror("shell")
	else
	{
		waitpid(cpid, & status, WUNTRACED);
	}
	return (1);
}
