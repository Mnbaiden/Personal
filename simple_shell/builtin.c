#include "shell.h"

/**
 * _myexit - Exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Exits with a given exit status (0) if info->argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	if (info->argv[1])
	{
		int exit_status = _erratoi(info->argv[1]);

		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exit_status;
	}
	else
	{
		info->err_num = -1;
	}
	return (-2);
}
/**
 * _mycd - Changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constarnt function prottotype
 * Return: Always 0
 */
int _mycd(info_t *info)
{
	char *dir = NULL;
	char buffer[1024];

	char *current_dir = getcwd(buffer, sizeof(buffer));

	if (!current_dir)
	{
		_puts("TODO: >>getcwd failure emsg here<<\n");
		return (1);
	}
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		dir = _getenv(info, "OLDPWD=");
		if (!dir)
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
	}
	else
	{
		dir = info->argv[1];
	}
	int chdir_ret = chdir(dir ? dir : "/");

	if (chdir_ret == -1)
	{
		print_error(info, "cannot cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	return (0);
}
/**
 * _myhelp - displays help info
 * @info: Structure containing potential argumnts. used to
 * maintain constant function prototype
 * Return: Always 0
 */

int _myhelp(info_t *info)
{
	_puts("The Help call is active, Function is not yet carried out");
	return (0);
}
