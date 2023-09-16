#include "shell.h"

/**
 * string_to_int - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The converted integer or -1 on error.
 */
int string_to_int(char *s)
{
    int result = 0;
    int sign = 1;

    if (*s == '-')
    {
        sign = -1;
        s++;
    }

    while (*s)
    {
        if (*s >= '0' && *s <= '9')
        {
            result = result * 10 + (*s - '0');
            s++;
        }
        else
        {
            return -1; // Error: Non-digit character encountered
        }
    }

    return result * sign;
}

/**
 * print_error_message - Prints an error message.
 * @info: The parameter and return info struct.
 * @error_type: String containing the specified error type.
 */
void print_error_message(info_t *info, char *error_type)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(error_type);
}

/**
 * print_decimal - Prints a decimal (integer) number (base 10).
 * @input: The input number.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_decimal(int input, int fd)
{
    int (*putchar_func)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
    int count = 0;

    if (input < 0)
    {
        putchar_func('-');
        count++;
        input = -input;
    }

    int divisor = 1;
    while (divisor <= input / 10)
        divisor *= 10;

    while (divisor > 0)
    {
        int digit = (input / divisor) % 10;
        putchar_func('0' + digit);
        count++;
        divisor /= 10;
    }

    return count;
}

/**
 * convert_to_string - Converts a number to a string representation.
 * @num: The number to convert.
 * @base: The base for the conversion (e.g., 10 for decimal).
 * @flags: Flags for conversion (e.g., CONVERT_UNSIGNED).
 *
 * Return: The converted string.
 */
char *convert_to_string(long int num, int base, int flags)
{
    static char buffer[50];
    char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
    char sign = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? '-' : 0;
    unsigned long n = (num < 0) ? -num : num;
    char *ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

/**
 * remove_comments_from_string - Replaces the first '#' with '\0'.
 * @str: The string to modify.
 */
void remove_comments_from_string(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '#' && (i == 0 || str[i - 1] == ' '))
        {
            str[i] = '\0';
            break;
        }
    }
}
