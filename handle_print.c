#include "main.h"
/**
 * handle_print - prints an argument depending on its type
 * @fmt: formatted string to print the arguments.
 * @list: arguments list
 * @index: index
 * @buffer: array of characters to handle print.
 * @flags: calculates the flag
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: one or two
 */
int handle_print(const char *fmt, int *index, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknown_length = 0, chars_printed = -1;
	fmt_t format_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_HEXA}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13}, {'\0', NULL}
	};
	for (i = 0; format_types[i].fmt != '\0'; i++)
		if (fmt[*index] == format_types[i].fmt)
			return (format_types[i].f(list, buffer, flags, width, precision, size));

	if (format_types[i].fmt == '\0')
	{
		if (fmt[*index] == '\0')
			return (-1);
		unknown_length += write(1, "%%", 1);
		if (fmt[*index - 1] == ' ')
			unknown_length += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (fmt[*index] != ' ' && fmt[*index] != '%')
				--(*index);
			if (fmt[*index] == ' ')
				--(*index);
			return (1);
		}
		unknown_length += write(1, &fmt[*index], 1);
		return (unknown_length);
	}
	return (chars_printed);
}
