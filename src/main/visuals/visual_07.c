// VisualObj, visual_object_update_funcs[7]
// 800AF22C..800AF6A0
#include "common.h"

void func_800AF22C(struct VisualObj* arg0)
{
    struct PlayerObj* var_a1 = &g_Entity;
    if (!(arg0->unk2 & 2)) {
        var_a1 = &g_Player;
    }
    if (arg0->state == 0) {
        func_800AF28C(arg0, var_a1);
    } else {
        func_800AF388(arg0, var_a1);
    }
}

void func_800AF28C(struct VisualObj* arg0, struct VisualObj* arg1)
{
    arg0->bg_offset = arg1->bg_offset;
    arg0->unk16 = 1;
    arg0->animation_table = &D_8011BF40;
    arg0->unk3C = *((u8)func_8002938C(0x84) + SP_MENU_FRAMES) + (s8*)SP_MENU_FRAMES;
    arg0->unk40 = D_801406A8[(u8)func_8002938C(0x84)] >> 7;
    arg0->unk42 = (((u8)func_8002938C(0x84) * 4) + 24) % 16 | ((((u8)func_8002938C(0x84) + 6) / 4) + 480) * 64;
    arg0->state++;
}

void func_800AF388(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (arg1->unk5C == 0 || arg1->state == 3) {
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
    D_8010A1C8[arg0->unk5](arg0, arg1);
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

void func_800AF488(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (func_800AF610(arg1) != 0) {
        func_80015D60(arg0, 0x13);
        arg0->on_screen = 1;
        arg0->unk5 = 1;
    } else if (func_800AF658(arg1) != 0) {
        func_80015D60(arg0, 0x14);
        arg0->on_screen = 1;
        arg0->unk5 = 2;
    }
}

void func_800AF504(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (func_800AF610(arg1) != 0) {
        func_80015DC8(arg0);
        arg0->on_screen = 1;
        return;
    }
    if (func_800AF658(arg1) != 0) {
        func_80015D60(arg0, 0x14);
        arg0->on_screen = 1;
        arg0->unk5 = 2;
        return;
    }
    arg0->on_screen = 0;
    arg0->unk5 = 0;
}

void func_800AF58C(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (func_800AF658(arg1) != 0) {
        func_80015DC8(arg0);
        arg0->on_screen = 1;
        return;
    }
    if (func_800AF610(arg1) != 0) {
        func_80015D60(arg0, 0x13);
        arg0->on_screen = 1;
        arg0->unk5 = 1;
        return;
    }
    arg0->on_screen = 0;
    arg0->unk5 = 0;
}

s32 func_800AF610(struct PlayerObj* arg0)
{
    if (arg0->unk2 != 0) {
        return D_8010A104[0][arg0->unk17] == 1;
    }
    return D_8010A074[0][arg0->unk17] == 1;
}

s32 func_800AF658(struct PlayerObj* arg0)
{
    u8 state;

    if (arg0->unk2 == 0) {
        state = D_8010A074[0][arg0->unk17];
    } else {
        state = D_8010A104[0][arg0->unk17];
    }

    return state == 2;
}

void (*D_8010A1C8[])(struct VisualObj*, struct PlayerObj*) = {
    func_800AF488,
    func_800AF504,
    func_800AF58C,
};
