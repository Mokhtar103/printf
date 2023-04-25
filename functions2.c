#include "main.h"

/**
 * print_pointer - prints the value of a pointer
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_pointer(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	char add_c = 0, padding = ' ';
	int index = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_address;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_address = (unsigned long)address;

	while (num_address > 0)
	{
		buffer[index--] = map_to[num_address % 16];
		num_address /= 16;
		length++;
	}

	if ((flags & ZERO) && !(flags & MINUS))
		padding = '0';
	if (flags & PLUS)
		add_c = '+', length++;
	else if (flags & SPACE)
		add_c = ' ', length++;

	index++;

return (write_pointer(buffer, index,
length, width, flags, padding, add_c, padd_start));
}

/**
 * print_non_printable - prints ascii codes in hexa of non printable chars
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	int count = 0, off_set = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[count] != '\0')
	{
		if (is_printable(str[count]))
			buffer[count + off_set] = str[count];
		else
			off_set += append_hexa_code(str[count], buffer, count + off_set);

		count++;
	}

	buffer[count + off_set] = '\0';

	return (write(1, buffer, count + off_set));
}

/**
 * print_reverse - prints the reverse of a string.
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of characters printed
 */

int print_reverse(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	char *to_str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	to_str = va_arg(types, char *);

	if (to_str == NULL)
	{
		UNUSED(precision);

		to_str = ")Null(";
	}
	for (i = 0; to_str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char c = to_str[i];

		write(1, &c, 1);
		count++;
	}
	return (count);
}

/**
 * print_rot13 - Print a string in rot13.
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of characters printed
 */
int print_rot13(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	char c;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in_to[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out_of[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in_to[j]; j++)
		{
			if (in_to[j] == str[i])
			{
				c = out_of[j];
				write(1, &c, 1);
				count++;
				break;
			}
		}
		if (!in_to[j])
		{
			c = str[i];
			write(1, &c, 1);
			count++;
		}
	}
	return (count);
}
