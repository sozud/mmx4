// VisualObj, visual_object_update_funcs[7]
// 800AF22C..800AF6A0
#include "common.h"

void water_wake_update(struct VisualObj* arg0)
{
    struct PlayerObj* var_a1;

    var_a1 = !(arg0->unk2 & 2) ? &g_Player : &g_Entity;
    if (arg0->state == 0) {
        water_wake_init(arg0, var_a1);
    } else {
        water_wake_main(arg0, var_a1);
    }
}

void water_wake_init(struct VisualObj* arg0, struct VisualObj* arg1)
{
    arg0->bg_offset = arg1->bg_offset;
    arg0->unk16 = 1;
    arg0->animation_table = &D_8011BF40;
    arg0->unk3C = *((u8)func_8002938C(0x84) + SP_MENU_FRAMES) + (s8*)SP_MENU_FRAMES;
    arg0->unk40 = D_801406A8[(u8)func_8002938C(0x84)] >> 7;
    arg0->unk42 = SOME_COORDINATE_CONVERSION((u8)func_8002938C(0x84));
    arg0->state++;
}

void water_wake_main(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (arg1->hp == 0 || arg1->state == 3) {
        ZeroObjectState(arg0);
        return;
    }
    arg0->unk15 = arg1->unk15;
    if (arg0->unk2 & 1) {
        arg0->x_pos.val = arg1->x_pos.val + FIXED(8);
    } else {
        arg0->x_pos.val = arg1->x_pos.val + FIXED(-8);
    }
    arg0->y_pos.val = arg1->y_pos.val;
    water_wake_step_funcs[arg0->unk5](arg0, arg1);
    if (arg1->active == 0) {
        arg0->on_screen = 0;
    }
    if (func_8002D900(arg1) != 0x24) {
        arg0->on_screen = 0;
    }
    if (arg0->on_screen != 0) {
        is_on_screen(arg0);
    }
}

void water_wake_hidden(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (water_wake_player_idle(arg1) != 0) {
        set_animation(arg0, 0x13);
        arg0->on_screen = 1;
        arg0->unk5 = 1;
    } else if (water_wake_player_moving(arg1) != 0) {
        set_animation(arg0, 0x14);
        arg0->on_screen = 1;
        arg0->unk5 = 2;
    }
}

void water_wake_idle(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (water_wake_player_idle(arg1) != 0) {
        animate_object(arg0);
        arg0->on_screen = 1;
        return;
    }
    if (water_wake_player_moving(arg1) != 0) {
        set_animation(arg0, 0x14);
        arg0->on_screen = 1;
        arg0->unk5 = 2;
        return;
    }
    arg0->on_screen = 0;
    arg0->unk5 = 0;
}

void water_wake_moving(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (water_wake_player_moving(arg1) != 0) {
        animate_object(arg0);
        arg0->on_screen = 1;
        return;
    }
    if (water_wake_player_idle(arg1) != 0) {
        set_animation(arg0, 0x13);
        arg0->on_screen = 1;
        arg0->unk5 = 1;
        return;
    }
    arg0->on_screen = 0;
    arg0->unk5 = 0;
}

s32 water_wake_player_idle(struct PlayerObj* arg0)
{
    u8 mode;

    switch (arg0->unk2) {
    case 0:
        mode = x_water_wake_modes[0][arg0->unk17];
        break;
    default:
        mode = zero_water_wake_modes[0][arg0->unk17];
        break;
    }
    return mode == 1;
}

s32 water_wake_player_moving(struct PlayerObj* arg0)
{
    u8 state;

    if (arg0->unk2 == 0) {
        state = x_water_wake_modes[0][arg0->unk17];
    } else {
        state = zero_water_wake_modes[0][arg0->unk17];
    }

    return state == 2;
}

void (*water_wake_step_funcs[])(struct VisualObj*, struct PlayerObj*) = {
    water_wake_hidden,
    water_wake_idle,
    water_wake_moving,
};
