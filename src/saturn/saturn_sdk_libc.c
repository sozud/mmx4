#include <stdarg.h>
#include <stddef.h>

void* memcpy(void* destination, const void* source, size_t length)
{
    unsigned char* out = destination;
    const unsigned char* in = source;
    if (out == in)
        return destination;
    if (out < in) {
        for (size_t i = 0; i < length; ++i)
            out[i] = in[i];
    } else {
        for (size_t i = length; i != 0; --i)
            out[i - 1] = in[i - 1];
    }
    return destination;
}

char* strcpy(char* dest, const char* src)
{
    char* d = dest;
    while ((*d++ = *src++) != '\0')
        ;
    return dest;
}

static char* format_number(char* out, unsigned long value, unsigned base, int width, char pad, int upper, int negative)
{
    static const char digits_upper[] = "0123456789ABCDEF";
    static const char digits_lower[] = "0123456789abcdef";
    const char* digits = upper ? digits_upper : digits_lower;
    char scratch[12];
    int count = 0;

    do {
        scratch[count++] = digits[value % base];
        value /= base;
    } while (value != 0);
    if (negative)
        scratch[count++] = '-';
    while (width-- > count)
        *out++ = pad;
    while (count > 0)
        *out++ = scratch[--count];
    return out;
}

int vsprintf(char* out, const char* format, va_list args)
{
    char* start = out;
    const char* cursor;

    for (cursor = format; *cursor != 0; cursor++) {
        char pad = ' ';
        int width = 0;
        long value;

        if (*cursor != '%') {
            *out++ = *cursor;
            continue;
        }
        cursor++;
        if (*cursor == '0') {
            pad = '0';
            cursor++;
        }
        while (*cursor >= '0' && *cursor <= '9')
            width = width * 10 + (*cursor++ - '0');
        if (*cursor == 'l')
            cursor++;
        switch (*cursor) {
        case 'X':
            out = format_number(out, va_arg(args, unsigned long), 16, width, pad, 1, 0);
            break;
        case 'x':
            out = format_number(out, va_arg(args, unsigned long), 16, width, pad, 0, 0);
            break;
        case 'u':
            out = format_number(out, va_arg(args, unsigned long), 10, width, pad, 0, 0);
            break;
        case 'd':
            value = va_arg(args, long);
            out = format_number(out, value < 0 ? -value : value, 10, width, pad, 0, value < 0);
            break;
        case 'c':
            *out++ = (char)va_arg(args, int);
            break;
        case 's': {
            const char* string = va_arg(args, const char*);
            while (*string != 0)
                *out++ = *string++;
            break;
        }
        case 0:
            cursor--;
            break;
        default:
            *out++ = *cursor;
            break;
        }
    }
    *out = 0;
    return out - start;
}

int memcmp(const void* a, const void* b, size_t n)
{
    const unsigned char* x = a;
    const unsigned char* y = b;
    for (; n != 0; n--, x++, y++) {
        if (*x != *y)
            return *x - *y;
    }
    return 0;
}

void* memset(void* destination, int value, size_t length)
{
    unsigned char* out = destination;
    for (size_t i = 0; i < length; ++i) {
        out[i] = (unsigned char)value;
    }
    return destination;
}

size_t strlen(const char* s)
{
    size_t n = 0;

    while (*s++ != '\0')
        n++;
    return n;
}

int strncmp(const char* a, const char* b, size_t n)
{
    for (; n != 0; n--, a++, b++) {
        if (*a != *b)
            return (unsigned char)*a - (unsigned char)*b;
        if (*a == '\0')
            break;
    }
    return 0;
}

char* strncpy(char* dest, const char* src, size_t n)
{
    char* d = dest;
    for (; n != 0 && *src != '\0'; n--)
        *d++ = *src++;
    for (; n != 0; n--)
        *d++ = '\0';
    return dest;
}
