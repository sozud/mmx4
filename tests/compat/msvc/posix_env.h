#ifndef MMX4_TESTS_MSVC_POSIX_ENV_H
#define MMX4_TESTS_MSVC_POSIX_ENV_H

#include <stdlib.h>

static int setenv(const char* name, const char* value, int overwrite)
{
    if (!overwrite && getenv(name) != NULL)
        return 0;
    return _putenv_s(name, value) == 0 ? 0 : -1;
}

static int unsetenv(const char* name)
{
    return _putenv_s(name, "") == 0 ? 0 : -1;
}

#endif
