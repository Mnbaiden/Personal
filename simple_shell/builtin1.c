#include "shell.h"

/**
 * _myhistory - displays the history list, one command per line, preceded
 *              by line numbers starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
    list_t *node = info->history;
    int line_number = 0;

    while (node != NULL)
    {
        printf("%d %s\n", line_number++, node->str);
        node = node->next;
    }

    return (0);
}

/**
 * unset_alias - removes an alias from the alias list.
 * @info: parameter struct
 * @alias: the alias string to remove
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *alias)
{
    return (delete_node_at_index(&(info->alias),
             get_node_index(info->alias, node_starts_with(info->alias, alias, -1))));
}

/**
 * set_alias - adds or updates an alias in the alias list.
 * @info: parameter struct
 * @alias: the alias string to set
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *alias)
{
    unset_alias(info, alias);
    return (add_node_end(&(info->alias), alias, 0) == NULL);
}

/**
 * print_alias - prints an alias string.
 * @node: the alias node to print
 *
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
    char *p;

    if (node)
    {
        p = _strchr(node->str, '=');
        if (p)
        {
            *p = '\0';
            printf("%s '%s'\n", node->str, p + 1);
            *p = '=';
            return (0);
        }
    }
    return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments. Used to maintain
 *        a constant function prototype.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
    int i;
    char *p;

    if (info->argc == 1)
    {
        list_t *node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return (0);
    }

    for (i = 1; info->argv[i]; i++)
    {
        p = _strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return (0);
}
