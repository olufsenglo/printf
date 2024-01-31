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
*count += write(1, str, 1);
}

/**
* print_integer - Helper function to print an integer.
* @count: Pointer to the count of characters printed.
* @args: Variable argument list.
*/
static void print_integer(int *count, va_list args)
{
int num = va_arg(args, int);
// Assuming a reasonable buffer size for simplicity
char buffer[12];  // Buffer for integer to string conversion
int length = 0;

// Convert integer to string
length = sprintf(buffer, "%d", num);

// Write the string to standard output
*count += write(1, buffer, length);
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
switch (*format)
{
case 'c':
print_char(&count, args);
break;
case 's':
print_string(&count, args);
break;
case 'd':
case 'i':
print_integer(&count, args);
break;
case '%':
count += write(1, "%", 1);
break;
default:
count += write(1, "%", 1);
count += write(1, format, 1);
}
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
