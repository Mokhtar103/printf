#include "main.h"

/**
 * get_flags - returns the flag to be printed
 * @format: formatted string to print the arguments
 * @args: arguments
 * Return: flags
 */
int get_flags(const char *format, int *args)
{

	int i, current;
	int flags = 0;
	const char char_flags[] = {'-', '+', '0', '#', ' ', '\0'};
	const int arr_flags[] = {MINUS, PLUS, ZERO, HASH, SPACE, 0};

	for (current = *args + 1; format[current] != '\0'; current++)
	{
		for (i = 0; char_flags[i] != '\0'; i++)
			if (format[current] == char_flags[i])
			{
				flags |= arr_flags[i];
				break;
			}

		if (char_flags[i] == 0)
			break;
	}

	*args = current - 1;

	return (flags);
}

