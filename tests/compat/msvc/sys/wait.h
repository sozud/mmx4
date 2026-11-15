#ifndef MMX4_TESTS_MSVC_SYS_WAIT_H
#define MMX4_TESTS_MSVC_SYS_WAIT_H

#include "../unistd.h"

#define WIFEXITED(status) 1
#define WEXITSTATUS(status) (status)

static pid_t fork(void) { return -1; }
static pid_t waitpid(pid_t pid, int* status, int options)
{
    (void)pid;
    (void)status;
    (void)options;
    return -1;
}

#endif
