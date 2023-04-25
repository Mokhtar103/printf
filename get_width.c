#include "main.h"

/**
 * get_width - return the width to be printed
 * @format: Formatted string to print the arguments.
 * @args: arguments
 * @list: list of arguments.
 *
 * Return: width.
 */
int get_width(const char *format, int *args, va_list list)
{
	int current;
	int width = 0;

	for (current = *args + 1; format[current] != '\0'; current++)
	{
		if (is_digit(format[current]))
		{
			width *= 10;
			width += format[current] - '0';
		}
		else if (format[current] == '*')
		{
			current++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*args = current - 1;

	return (width);
}
