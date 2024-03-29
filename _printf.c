#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
* print_char - Helper function to print a character.
* @count: Pointer to the count of characters printed.
* @args: Variable argument list.
*/
static void print_char(int *count, va_list args)
{
char c = va_arg(args, int);
*count += write(1, &c, 1);
}

/**
* print_string - Helper function to print a string.
* @count: Pointer to the count of characters printed.
* @args: Variable argument list.
*/
static void print_string(int *count, va_list args)
{
char *str = va_arg(args, char *);
int i = 0;

while (str[i])
{
*count += write(1, &str[i], 1);
i++;
}
}

/**
 * print_integer - Helper function to print an integer.
 * @count: Pointer to the count of characters printed.
 * @args: Variable argument list.
 * @base: Base for conversion (e.g., 10 for decimal, 16 for hexadecimal).
 * @is_unsigned: Flag to indicate whether the integer is unsigned.
 */
static void print_integer(int *count, va_list args,
		int base, unsigned int is_unsigned)
{
char buffer[12];
int i, length;
unsigned int num;

if (is_unsigned)
num = va_arg(args, unsigned int);
else
num = va_arg(args, int);

length = 0;

do {
if (num % base < 10)
buffer[length++] = num % base + '0';
else
buffer[length++] = num % base - 10 + 'a';
num /= base;
} while (num != 0);

for (i = 0; i < length / 2; i++)
{
char temp = buffer[i];
buffer[i] = buffer[length - i - 1];
buffer[length - i - 1] = temp;
}

*count += write(1, buffer, length);
}

/**
* print_reversed_string - Helper function to print a reversed string.
* @count: Pointer to the count of characters printed.
* @args: Variable argument list.
*/
static void print_reversed_string(int *count, va_list args)
{
char *str = va_arg(args, char *);
int length = 0;
int i;

while (str[length])
length++;

for (i = length - 1; i >= 0; i--)
*count += write(1, &str[i], 1);
}

/**
* handle_conversion - Helper function to handle format conversion specifiers.
* @count: Pointer to the count of characters printed.
* @args: Variable argument list.
* @format: Current format specifier.
*/
static void handle_conversion(int *count, va_list args, const char *format)
{
switch (*format)
{
case 'c':
print_char(count, args);
break;
case 's':
print_string(count, args);
break;
case 'd':
case 'i':
print_integer(count, args, 10, 0);
break;
case 'u':
print_integer(count, args, 10, 1);
break;
case 'o':
print_integer(count, args, 8, 1);
break;
case 'x':
print_integer(count, args, 16, 1);
break;
case 'X':
print_integer(count, args, 16, 1);
break;
case 'r':
print_reversed_string(count, args);
break;
case '%':
*count += write(1, "%", 1);
break;
default:
*count += write(1, "%", 1);
*count += write(1, format, 1);
}
}

/**
* _printf - Custom printf function.
* @format: Format string.
*
* Return: Number of characters printed (excluding null byte).
*/
int _printf(const char *format, ...)
{
int count = 0;
va_list args;

va_start(args, format);

while (*format)
{
if (*format == '%' && *(format + 1) != '\0')
{
format++;
handle_conversion(&count, args, format);
}
else
{
count += write(1, format, 1);
}
format++;
}

va_end(args);

return (count);
}
