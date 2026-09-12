#include "common.h"

#ifndef VERSION_JP
u8 D_800F9E50[] = { 6, 7, 8, 9, 10, 11, 12, 0 };
#endif

void (*spike_marl_state_funcs[])(struct MainObj*) = {
    func_80043390,
    spike_marl_run,
    spike_marl_cleanup,
};
