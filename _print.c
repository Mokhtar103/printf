#include "main.h"


void print_buffer(char buffer[], int *buff_index);

/**
 * _printf - produces output according to a format
 * @format: character string
 * @...: list of arguments
 * Return: integer
 */
int _printf(const char *format, ...)
{
	int count, all_printed = 0, chars_printed = 0;
	int flags, width, precision, size, buff_index = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (count = 0; format && format[count] != '\0'; count++)
	{
		if (format[count] != '%')
		{
			buffer[buff_index++] = format[count];
			if (buff_index == BUFF_SIZE)
				print_buffer(buffer, &buff_index);
			chars_printed++;
		}
		else
		{
			print_buffer(buffer, &buff_index);
			flags = get_flags(format, &count);
			width = get_width(format, &count, list);
			precision = get_precision(format, &count, list);
			size = get_size(format, &count);
			++count;
			all_printed = handle_print(format, &count,
			 list, buffer, flags, width, precision, size);
			if (all_printed == -1)
				return (-1);
			chars_printed += all_printed;
		}
	}

	print_buffer(buffer, &buff_index);

	va_end(list);

	return (chars_printed);
}

/**
 * print_buffer - Prints the contents of the buffer
 * @buffer: array of characters
 * @buffer_index: represent the length of buffer
 */
void print_buffer(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer[0], *buffer_index);

	*buffer_index = 0;
}
