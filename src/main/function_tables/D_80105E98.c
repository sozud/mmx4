#include "common.h"

void (*general_intro_funcs[])(struct MainObj*) = {
    general_intro_wait_player,
    func_8008FBCC,
    general_intro_lock_camera,
    general_intro_enter,
    general_intro_land,
    general_intro_dialogue,
    general_intro_fill_health,
    general_intro_finish,
};
