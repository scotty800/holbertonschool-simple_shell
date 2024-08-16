#include "shell.h"
#include <string.h>

/**
 * _strdup -Duplique une chaine de cara
 * @str: La chaine de caractÃrs
 * Return: 0
 */

char *_strdup(const char *str)
{
	size_t len;
	char *dup;
	if (str == NULL)
		return NULL;

	len = strlen(str) + 1;
	dup = malloc(len);

	if (dup == NULL)
		return NULL;

	memcpy(dup, str, len);
	return (dup);
}
