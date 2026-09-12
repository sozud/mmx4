#include "common.h"

void (*spike_marl_step_funcs[])(struct MainObj*) = {
    (void (*)(struct MainObj*))func_8009216C,
    spike_marl_resume_step,
    spike_marl_patrol,
    spike_marl_turn,
    spike_marl_curl,
    spike_marl_roll,
    spike_marl_fall,
    spike_marl_uncurl,
    spike_marl_roll_entry,
};
