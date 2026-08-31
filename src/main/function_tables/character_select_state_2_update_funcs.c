#include "common.h"

void (*character_select_state_2_update_funcs[])(struct EngineObj*) = {
    character_select_state_2_substate_0,
    character_select_spawn_objects,
};
