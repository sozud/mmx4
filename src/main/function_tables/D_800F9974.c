#include "common.h"

void (*background_dragon_state_funcs[])(struct MainObj*) = {
    func_80040644,
    func_80040838,
    background_dragon_cleanup,
};
