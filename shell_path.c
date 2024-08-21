#include "shell.h"
/**
 * shell_path - Locates the full path of a command.
 * @filename: The command name.
 * This function searches for the command in the directories listed in the
 * Return: A pointer to the full path of the command, or NULL if not found.
 */
char *shell_path(char *filename)
{
	char *path, *path_copy, *dir;
	char *path_full = malloc(MAX_PATH);

	path = getenv("PATH");
	path_copy = _strdup(path);
	if (path == NULL || path_copy == NULL || path_full == NULL)
	{
		fprintf(stderr, "ERROR: PATH\n");
		perror("strdup on path");
		perror("malloc");
		free(path_full);
		free(path_copy);
		exit(EXIT_FAILURE);
	}
	for (dir = strtok(path_copy, ":"); dir != NULL; dir = strtok(NULL, ":"))
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
				free(path_full);
				free(path_copy);
				return (NULL);
			}
		}
	
	}
	free(path_copy);
	free(path_full);
	return (NULL);
}
