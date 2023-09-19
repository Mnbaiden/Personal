#include "shell.h"

/**
 * _strncpy - Copy a string up to 'n' characters.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The maximum number of characters to copy.
 *
 * Return: The copied string.
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	char *original_dest = dest;

	while (n  > 0 && (*dest++ = *src++))
		n--;

	if (n > 0)
	{
		while (--n > 0)
			*dest++ = '\0';
	}

	return (original_dest);
}


/**
 * _strncat - Concatenate two strings,
 * limiting the number of characters to copy.
 * @dest: The destination string.
 * @src: The source string to concatenate.
 * @n: The maximum number of characters to concatenate.
 *
 * Return: The concatenated string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	char *original_dest = dest;

	while (*dest)
		dest++;

	while (n > 0 && (*dest++ = *src++))
		n--;

	if (n > 0)
		*dest = '\0';

	return (original_dest);
}

/**
 * _strchr - Locate a character in a string.
 * @s: The string to be searched.
 * @c: The character to look for.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 * or NULL if not found.
 */
char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}

	return (NULL);
}
