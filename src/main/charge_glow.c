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
        func_80015D60(arg0, arg0->unk2 + 8);
        arg0->state++;
    }
}

void func_800AE790(struct BazObj* arg0, struct PlayerObj* arg1)
{
    if ((arg1->charge_state[0] == PLAYER_CHARGE_NONE) && (arg1->charge_state[1] == PLAYER_CHARGE_NONE)) {
        arg0->on_screen = 0;
        arg0->state = 0;
    } else {
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
}
