#include "main.h"

/**
 * get_size - calculates the size
 * @format: formatted string
 * @list: arguments to be printed
 *
 * Return: size
 */
int get_size(const char *format, int *list)
{
	int current = *list + 1;
	int size = 0;

	if (format[current] == 'l')
		size = S_LONG;
	else if (format[current] == 'h')
		size = S_SHORT;

	if (size == 0)
		*list = current - 1;
	else
		*list = current;

	return (size);
}
