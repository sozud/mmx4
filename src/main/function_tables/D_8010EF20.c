#include "common.h"

void (*iris_intro_crystal_state_funcs[])(struct MiscObj*) = {
    iris_intro_crystal_run,
    iris_intro_crystal_despawn,
};
