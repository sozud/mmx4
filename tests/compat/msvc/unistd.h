#ifndef MMX4_TESTS_MSVC_UNISTD_H
#define MMX4_TESTS_MSVC_UNISTD_H

#include <direct.h>
#include <io.h>
#include <process.h>
#include <stdlib.h>
#include <string.h>

typedef int pid_t;

#define F_OK 0
#define R_OK 4
#define W_OK 2
#define access _access
#define unlink _unlink
#define rmdir _rmdir

static char* mkdtemp(char* template_path)
{
    _mkdir("/tmp");
    if (_mktemp_s(template_path, strlen(template_path) + 1) != 0)
        return NULL;
    return _mkdir(template_path) == 0 ? template_path : NULL;
}

#endif
