#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
    list_t *node = info->env;

    while (node)
    {
        printf("%s\n", node->str);
        node = node->next;
    }

    return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value or NULL if not found
 */
char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;

    while (node)
    {
        if (starts_with(node->str, name))
            return strchr(node->str, '=') + 1;
        node = node->next;
    }

    return NULL;
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 0 on success, 1 on error
 */
int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return 1;
    }

    if (setenv(info->argv[1], info->argv[2], 1) == 0)
    {
        // Update the internal environment list
        char *env_str = malloc(strlen(info->argv[1]) + strlen(info->argv[2]) + 2);
        if (env_str)
        {
            sprintf(env_str, "%s=%s", info->argv[1], info->argv[2]);
            add_node_end(&(info->env), env_str, 0);
            return 0;
        }
    }

    return 1;
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 0 on success, 1 on error
 */
int _myunsetenv(info_t *info)
{
    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return 1;
    }

    for (int i = 1; i < info->argc; i++)
    {
        if (unsetenv(info->argv[i]) == 0)
        {
            // Update the internal environment list
            delete_node_at_index(&(info->env),
                                 get_node_index(info->env, node_starts_with(info->env, info->argv[i], '=')));
        }
    }

    return 0;
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 0 on success, 1 on error
 */
int populate_env_list(info_t *info)
{
    for (size_t i = 0; environ[i]; i++)
    {
        add_node_end(&(info->env), environ[i], 0);
    }
    return 0;
}
