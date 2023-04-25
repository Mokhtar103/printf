#include "main.h"

/**
 * print_unsigned - prints an unsigned number
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_unsigned(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	int count = BUFF_SIZE - 2;
	unsigned long int num1 = va_arg(types, unsigned long);

	num1 = convert_size_unsig(num1, size);

	if (num1 == 0)
		buffer[count--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num1 > 0)
	{
		buffer[count--] = (num1 % 10) + '0';
		num1 /= 10;
	}

	count++;

	return (write_unsig(0, count, buffer, flags, width, precision, size));
}

/**
 * print_octal - prints an unsigned number in octal
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_octal(va_list types, char buffer[],
int flags, int width, int precision, int size)
{

	int count = BUFF_SIZE - 2;
	unsigned long int my_num = va_arg(types, unsigned long int);
	unsigned long int init_num = my_num;

	UNUSED(width);

	my_num = convert_size_unsig(my_num, size);

	if (my_num == 0)
		buffer[count--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (my_num > 0)
	{
		buffer[count--] = (my_num % 8) + '0';
		my_num /= 8;
	}

	if (flags & HASH && init_num != 0)
		buffer[count--] = '0';

	count++;

	return (write_unsig(0, count, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - prints an unsigned number in hexadecimal
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
return (print_hexa(types, "0123456789abcdef",
buffer, flags, 'x', width, precision, size));
}

/**
 * print_HEXA - prints an unsigned number in upper hexadecimal
 * @types: arguments
 * @buffer: array of characters to handle print
 * @flags: active flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_HEXA(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
return (print_hexa(types, "0123456789ABCDEF",
buffer, flags, 'X', width, precision, size));
}

/**
 * print_hexa - prints a hexadecimal number in lower or upper
 * @types: arguments
 * @map_to: Array of values to map the number
 * @buffer: array of characters to handle print
 * @flags: flags
 * @flag_ch: flags
 * @width: width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size)
{
	int count = BUFF_SIZE - 2;
	unsigned long int my_num = va_arg(types, unsigned long int);
	unsigned long int init_num = my_num;

	UNUSED(width);

	my_num = convert_size_unsig(my_num, size);

	if (my_num == 0)
		buffer[count--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (my_num > 0)
	{
		buffer[count--] = map_to[my_num % 16];
		my_num /= 16;
	}

	if (flags & HASH && init_num != 0)
	{
		buffer[count--] = flag_ch;
		buffer[count--] = '0';
	}

	count++;

	return (write_unsig(0, count, buffer, flags, width, precision, size));
}
