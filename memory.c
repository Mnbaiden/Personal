#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @pntr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **pntr)
{
	if (pntr && *pntr)
	{
		free(*pntr);
		*pntr = NULL;
		return (1);
	}
	return (0);
}
