#include <stddef.h>
#include "test_runtime.h"
void* c_test_memset(void* destination, int value, size_t length)
{
    u8* out = destination;
    size_t i;
    for (i = 0; i < length; ++i)
        out[i] = value;
    return destination;
}
void* c_test_memcpy(void* destination, const void* source, size_t length)
{
    u8* out = destination;
    const u8* in = source;
    size_t i;
    for (i = 0; i < length; ++i)
        out[i] = in[i];
    return destination;
}
