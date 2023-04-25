#include "main.h"


/**
 * print_char - prints a char
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_char(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

return (handle_write_char(c, buffer,
flags, width, precision, size));
}

/**
 * print_string - prints a string
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_string(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	int length = 0, count;
	char *my_string = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (my_string == NULL)
	{
		my_string = "(null)";
		if (precision >= 6)
			my_string = "      ";
	}

	while (my_string[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & MINUS)
		{
			write(1, &my_string[0], length);
			for (count = width - length; count > 0; count--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (count = width - length; count > 0; count--)
				write(1, " ", 1);
			write(1, &my_string[0], length);
			return (width);
		}
	}

	return (write(1, my_string, length));
}
/**
 * print_percent - prints a percent sign
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_percent(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * print_int - print an integer
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active the flags
 * @width: width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_int(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	int count = BUFF_SIZE - 2;
	int isNegative = 0;
	long int num1 = va_arg(types, long int);
	unsigned long int num2;

	num1 = convert_size_number(num1, size);

	if (num1 == 0)
		buffer[count--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num2 = (unsigned long int)num1;

	if (num1 < 0)
	{
		num2 = (unsigned long int)((-1) * num1);
		isNegative = 1;
	}

	while (num2 > 0)
	{
		buffer[count--] = (num2 % 10) + '0';
		num2 /= 10;
	}

	count++;

return (write_number(isNegative, count,
buffer, flags, width, precision, size));
}

/**
 * print_binary - prints a binary number
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of characters printed.
 */
int print_binary(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	unsigned int n, m, k, sum;
	unsigned int ch[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648;
	ch[0] = n / m;
	for (k = 1; k < 32; k++)
	{
		m /= 2;
		ch[k] = (n / m) % 2;
	}
	for (k = 0, sum = 0, count = 0; k < 32; k++)
	{
		sum += ch[k];
		if (sum || k == 31)
		{
			char x = '0' + ch[k];

			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
