#include "shell.h"

/**
 * is_executable - determines if a file is an executable command
 *
 * @file_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(const char *file_path)
{
	struct stat file_info;

	if (!file_path || stat(file_path, &file_info)) {
		return 0;
	}

	if (file_info.st_mode & S_IFREG) {
		return 1;
	}
	return 0;
}

/**
 * duplicate_characters - duplicates characters from a string
 *
 * @source_string: the string to duplicate characters from
 * @start_index: the starting index
 * @stop_index: the stopping index
 *
 * Return: a pointer to a new buffer containing the duplicated characters, or NULL if an error occurs
 */
char *duplicate_characters(const char *source_string, int start_index, int stop_index)
{
	static char buffer[1024];
	int i = start_index;

	while (i < stop_index && source_string[i] != ':') {
		buffer[i - start_index] = source_string[i];
		i++;
	}
	buffer[i - start_index] = 0;
	return (buffer);
}

/**
 * find_executable_path - finds the path to an executable command in the PATH string
 *
 * @info: the info struct (ignored)
 * @path_string: the PATH string
 * @command: the command to find
 *
 * Return: a pointer to the path of the executable command, or NULL if the command is not found
 */
char *find_executable_path(info_t *info, const char *path_string, const char *command)
{
	int current_position = 0;
	char *path;

	if (!path_string) {
		return NULL;
	}

	if ((strlen(command) > 2) && starts_with(command, "./")) {
		if (is_executable(info, command)) {
			return command;
		}
	}

	do {
		if (path_string[current_position] == ':') {
			path = duplicate_characters(path_string, current_position, current_position);
			if (!*path) {
				strcat(path, command);
			} else {
				strcat(path, "/");
				strcat(path, command);
			}

			if (is_executable(info, path)) {
				return path;
			}
		}

		current_position++;
	} while (path_string[current_position]);

	return NULL;
}
