#include "shell.h"

/**
 * _strdup -Duplique une chaine de cara
 * @str: La chaine de caractÃrs
 * Return: 0
 */

char *_strdup(char *str)
{
    if (str == NULL)
        return NULL;

    size_t len = strlen(str) + 1;

    char *dup_str = malloc(len);
    if (dup_str == NULL)
        return NULL;

    memcpy(dup_str, str, len);

    return dup_str;
}
