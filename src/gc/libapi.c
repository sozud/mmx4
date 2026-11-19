#include "common.h"
#include "gc/assert.h"

#define NUM_THFUNC 10

static long (*thfunc[NUM_THFUNC])(void);

#line 41
int ChangeTh(long a)
{
    assert(a >= 0 && a < NUM_THFUNC);
    if (thfunc[a] != NULL) {
        thfunc[a]();
    }
    return 1;
}

long OpenTh(long (*func)(void), unsigned long sp, unsigned long gp)
{
    long i;

    for (i = 0; i < NUM_THFUNC; i++) {
        if (thfunc[i] == NULL) {
            thfunc[i] = func;
            return i;
        }
    }
    return -1;
}

#line 79
int CloseTh(long a)
{
    assert(a >= 0 && a < NUM_THFUNC);
    thfunc[a] = NULL;
    return 0;
}

long EnableEvent(long event)
{
    return 0;
}

int EnterCriticalSection(void)
{
    return 0;
}

void ExitCriticalSection(void)
{
}

long OpenEvent(unsigned long desc, long spec, long mode, long (*func)(void))
{
    return 1;
}

long fn_4_D65F8(void)
{
    return 1;
}

void fn_4_D6600(void)
{
}
