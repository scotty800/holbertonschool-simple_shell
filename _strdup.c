#include "shell.h"

/**
 * _strdup -Duplique une chaine de cara
 * @str: La chaine de caractÃrs
 * Return: 0
 */

char *_strdup(const char *str)
{
	size_t len = strlen(str) + 1;
	char *dup = malloc(len);
	if (str == NULL)
		return NULL;

	if (dup == NULL)
		return NULL;

	memcpy(dup, str, len);
	return (dup);
}
