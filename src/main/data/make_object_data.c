#include "common.h"

struct ObjectHeader* (*g_MakeObjectFuncs[8])() = {
    find_free_main_obj,
    find_free_weapon_obj,
    find_free_visual_obj,
    find_free_effect_obj,
    find_free_item_obj,
    find_free_misc_obj,
    find_free_quad_obj,
    find_free_layer_obj,
};
