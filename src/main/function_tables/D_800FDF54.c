#include "common.h"

void (*spike_sled_state_funcs[])(struct MainObj*) = {
    spike_sled_init,
    spike_sled_run,
    func_8005D4E0,
    spike_sled_despawn,
};
