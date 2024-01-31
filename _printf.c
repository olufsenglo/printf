#include "main.h"
#include <stdarg.h>
#include <unistd.h>

int _printf(const char *format, ...) {
    int count = 0;
    va_list args;

    va_start(args, format);

    while (*format) {
        if (*format == '%' && *(format + 1) != '\0') {
            format++;
            switch (*format) {
                case 'c': {
                    char c = va_arg(args, int);
                    count += write(1, &c, 1);
                }
                break;
                case 's': {
                    char *str = va_arg(args, char *);
                    count += write(1, str, 1);
                }
                break;
                case '%':
                    count += write(1, "%", 1);
                    break;
                default:
                    count += write(1, "%", 1);
                    count += write(1, format, 1);
            }
        } else {
            count += write(1, format, 1);
        }
        format++;
    }

    va_end(args);

    return count;
}
