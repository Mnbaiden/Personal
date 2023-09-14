#include <stdio.h>
#include <unistd.h>
#include "shell.h"

/**
 * interactive - Check if the shell is in interactive mode.
 * @info: Pointer to a struct containing shell information.
 *
 * Return: 1 if in interactive mode, 0 otherwise.
 */
int interactive(info_t *info)
{
/**
 * Check if STDIN is associated with a terminal and
 * if readfd is less than or equal to 2.
 */
	if (isatty(STDIN_FILENO) && info->readfd <= 2)
		return (1); /* Interactive mode */
	else
		return (0); /* Not in the interactive mode */
}

/**
 * is_delim - Check if a character is a delimiter.
 * @c: The character to be checked
 * @delim: The delimiter string.
 *
 * Return: 1 if true, 0 if false.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1); /* Character is a delimiter */
		delim++;
	}
	return (0); /* character is not a delimiter */
}

/**
 * _isalpha - Check if a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1); /* Character is alphabetic */
	else
		return (0); /* Character is not alphabetic */
}

/**
 * _atoi - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in string, converted number otherwise.
 */
int _atoi(char *s)
{
	int i = 0;
	int sign = 1;
	int flag = 0;
	int output = 0;
	unsigned int result = 0;

	while (s[i] != '\0' && flag != 2)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;

		i++;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
