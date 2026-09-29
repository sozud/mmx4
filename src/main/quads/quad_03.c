// QuadObj, quad_object_update_funcs[3]
// 800D514C..800D526C
#include "common.h"

// boss_warning_quad_main_body
INCLUDE_ASM("main/nonmatchings/quads/quad_03", func_800D514C);

void boss_warning_quad_despawn(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void boss_warning_quad_update(struct QuadObj* arg0)
{
    boss_warning_quad_state_funcs[arg0->state](arg0);
}

u8 boss_warning_quad_blink_levels[16] = { 4, 6, 7, 8, 9, 10, 11, 12, 11, 10, 9, 8, 7, 6, 0, 0 };

void (*boss_warning_quad_step_funcs[])(struct QuadObj*) = {
    boss_warning_quad_open,
    boss_warning_quad_hold,
    boss_warning_quad_close,
};

void (*boss_warning_quad_state_funcs[])(struct QuadObj*) = {
    func_800D4C50,
    func_800D5144,
    boss_warning_quad_despawn,
};
