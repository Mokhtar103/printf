#include "main.h"

/**
 * handle_write_char - prints string
 * @c: char
 * @buffer: array of characters to handle print
 * @flags: calculates the flag
 * @width: width
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & ZERO)
		padding = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padding;

		if (flags & MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - prints a number
 * @isNegative: check if the num is negative
 * @index: index
 * @buffer: array of characters to handle print
 * @flags: calculates the flag
 * @width: width
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: number of characters printed
 */
int write_number(int isNegative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char padding = ' ', add_char = 0;

	UNUSED(size);

	if ((flags & ZERO) && !(flags & MINUS))
		padding = '0';
	if (isNegative)
		add_char = '-';
	else if (flags & PLUS)
		add_char = '+';
	else if (flags & SPACE)
		add_char = ' ';

	return (write_num(index, buffer, flags, width, precision,
		length, padding, add_char));
}

/**
 * write_num - prints a number using buffer
 * @index: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @pre: Precision specifier
 * @length: Number length
 * @padding: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int index, char buffer[],
	int flags, int width, int pre, int length, char padding, char extra_c)
{
	int i, pad_start = 1;

	if (pre == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0);
	if (pre == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = padding = ' ';
	if (pre > 0 && pre < length)
		padding = ' ';
	while (pre > length)
		buffer[--index] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flags & MINUS && padding == ' ')
		{
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & MINUS) && padding == ' ')
		{
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & MINUS) && padding == '0')
		{
			if (extra_c)
				buffer[--pad_start] = extra_c;
			return (write(1, &buffer[pad_start], i - pad_start) +
				write(1, &buffer[index], length - (1 - pad_start)));
		}
	}
	if (extra_c)
		buffer[--index] = extra_c;
	return (write(1, &buffer[index], length));
}
/**
 * write_unsgnd - print an unsigned number
 * @isNegative: check if the num is negative
 * @index: index
 * @buffer: array of characters
 * @flags: flags specifier
 * @width: width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: number of printed characters
 */
int write_unsig(int isNegative, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1, i = 0;
	char padding = ' ';

	UNUSED(isNegative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2
	&& buffer[index] == '0')
		return (0);
	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & ZERO) && !(flags & MINUS))
		padding = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padding;

		buffer[i] = '\0';

		if (flags & MINUS)
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

/**
 * write_pointer - prints a memory address
 * @buffer: array of characters
 * @index: index
 * @length: the length
 * @width: width specifier
 * @flags: flags specifier
 * @padding: character represent padding
 * @extra_c: character represent extra char
 * @pad_start: index at which padding should start
 *
 * Return: number of printed character
 */
int write_pointer(char buffer[], int index, int length,
	int width, int flags, char padding, char extra_c, int pad_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flags & MINUS && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & MINUS) && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_c)
				buffer[--index] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & MINUS) && padding == '0')
		{
			if (extra_c)
				buffer[--pad_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[pad_start], i - pad_start) +
				write(1, &buffer[index], length - (1 - pad_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extra_c)
		buffer[--index] = extra_c;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}
