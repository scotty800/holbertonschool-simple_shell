#include "shell.h"
#define MAX_PATH 256

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
		fprintf(stderr, "ERREUR : PATH non défini\n");
		return NULL;
	}

	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup de path");
		free(path_full);
		exit(EXIT_FAILURE);

	}

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		path_full[0] = '\0';

		strcat(path_full, dir);
		strcat(path_full, "/");
		strcat(path_full, filename);

		if (access(path_full, X_OK) == 0)
		{
			free(path_copy);
			return path_full;
		}

		dir = strtok(NULL, ":");
	}

	free(path_copy);
	free(path_full);
	return NULL;

}

