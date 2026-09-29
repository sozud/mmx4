// BazObj, baz_objects
// 800AE6B4..800AE7DC
#include "common.h"

void func_800AE6B4(struct BazObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->y_pos.val = g_Player.y_pos.val;

    if (arg0->state == 0) {
        func_800AE714(arg0, ptr);

    } else {
        func_800AE790(arg0, ptr);
    }
}

void func_800AE714(struct BazObj* arg0, struct PlayerObj* arg1)
{
    PlayerChargeState charge_state = arg0->unk2 == 0 ? PLAYER_CHARGE_FULL : PLAYER_CHARGE_PARTIAL;

    if (arg1->charge_state[0] == charge_state || arg1->charge_state[1] == charge_state) {
        arg0->on_screen = 1;
        set_animation(arg0, arg0->unk2 + 8);
        arg0->state++;
    }
}

void func_800AE790(struct BazObj* arg0, struct PlayerObj* arg1)
{
    if ((arg1->charge_state[0] == PLAYER_CHARGE_NONE) && (arg1->charge_state[1] == PLAYER_CHARGE_NONE)) {
        arg0->on_screen = 0;
        arg0->state = 0;
    } else {
        animate_object(ANIMATED_OBJECT(arg0));
    }
}

u8 x_water_wake_modes[9][16] = {
    { 0, 0, 1, 1, 0, 1, 1, 2, 2, 2, 0, 0, 1, 0, 0, 0 },
    { 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 2, 0, 2, 0, 0, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 1, 0, 1, 1, 2, 2, 2, 0, 0, 1, 0, 0, 0 },
    { 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

u8 zero_water_wake_modes[9][16] = {
    { 0, 0, 1, 1, 0, 1, 1, 2, 2, 2, 0, 0, 1, 0, 0, 0 },
    { 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 2, 0, 2, 0, 0, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 2 },
    { 2, 0, 1, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
