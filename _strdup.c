#include "shell.h"

/**
 * _strdup -Duplique une chaine de cara
 * @str: La chaine de caractÃrs
 * Return: 0
 */

char *_strdup(char *str)
{
	size_t len = strlen(str) + 1;
	char *dup;

	if (str == NULL)
		return (NULL);

	dup = malloc(len);
	if (dup == NULL)
		return (NULL);

	memcpy(dup, str, len);

	return (dup);
}
