#include "main.h"

/**
 * is_printable - checks of the character can be printed
 * @z: Char to be checked
 *
 * Return: 1 if z can be printed, 0 otherwise
 */
int is_printable(char z)
{
	if (z >= 32 && z < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - append ASCII in hexadecimal code to buffer
 * @buffer: Array of characters
 * @index: index
 * @ascii_code: ASCII code
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int index)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[index++] = '\\';
	buffer[index++] = 'x';

	buffer[index++] = map_to[ascii_code / 16];
	buffer[index] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - checks if character is a digit
 * @z: character to be checked
 *
 * Return: 1 if z is a digit, 0 otherwise
 */
int is_digit(char z)
{
	if (z >= '0' && z <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - casts a num to a specific size
 * @number: num to be casted
 * @size: number indicate the type to be casted
 *
 * Return: casted number
 */
long int convert_size_number(long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((short)number);

	return ((int)number);
}

/**
 * convert_size_unsig - casts an unsigned num to a size
 * @number: unsigned num to be casted
 * @size: number indicate the type to be casted
 *
 * Return: casted unsigned num
 */
long int convert_size_unsig(unsigned long int number, int size)
{
	if (size == S_LONG)
		return (number);
	else if (size == S_SHORT)
		return ((unsigned short)number);

	return ((unsigned int)number);
}
