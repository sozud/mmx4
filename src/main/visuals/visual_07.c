// VisualObj, visual_object_update_funcs[7]
// 800AF22C..800AF6A0
#include "common.h"

void func_800AF22C(struct VisualObj* arg0)
{
    struct PlayerObj* var_a1 = &g_Entity;
    if (!(arg0->base.unk2 & 2)) {
        var_a1 = &g_Player;
    }
    if (arg0->base.state == 0) {
        func_800AF28C(arg0, var_a1);
    } else {
        func_800AF388(arg0, var_a1);
    }
}

void func_800AF28C(struct VisualObj* arg0, struct VisualObj* arg1)
{
    arg0->base.bg_offset = arg1->base.bg_offset;
    arg0->base.unk16 = 1;
    arg0->unk30 = &D_8011BF40;
    arg0->unk3C = *((u8)func_8002938C(0x84) + SP_MENU_FRAMES) + (s8*)SP_MENU_FRAMES;
    arg0->unk40 = D_801406A8[(u8)func_8002938C(0x84)] >> 7;
    arg0->unk42 = (((u8)func_8002938C(0x84) * 4) + 24) % 16 | ((((u8)func_8002938C(0x84) + 6) / 4) + 480) * 64;
    arg0->base.state++;
}

void func_800AF388(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (arg1->unk5C == 0 || arg1->base.state == 3) {
        ZeroObjectState(arg0);
        return;
    }
    arg0->base.unk15 = arg1->base.unk15;
    if (arg0->base.unk2 & 1) {
        arg0->base.x_pos.val = arg1->base.x_pos.val + FIXED(8);
    } else {
        arg0->base.x_pos.val = arg1->base.x_pos.val + FIXED(-8);
    }
    arg0->base.y_pos.val = arg1->base.y_pos.val;
    D_8010A1C8[arg0->base.unk5](arg0, arg1);
    if (arg1->base.active == 0) {
        arg0->base.on_screen = 0;
    }
    if (func_8002D900(arg1) != 0x24) {
        arg0->base.on_screen = 0;
    }
    if (arg0->base.on_screen != 0) {
        is_on_screen(arg0);
    }
}

void func_800AF488(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (func_800AF610(arg1) != 0) {
        func_80015D60(arg0, 0x13);
        arg0->base.on_screen = 1;
        arg0->base.unk5 = 1;
    } else if (func_800AF658(arg1) != 0) {
        func_80015D60(arg0, 0x14);
        arg0->base.on_screen = 1;
        arg0->base.unk5 = 2;
    }
}

void func_800AF504(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (func_800AF610(arg1) != 0) {
        func_80015DC8(arg0);
        arg0->base.on_screen = 1;
        return;
    }
    if (func_800AF658(arg1) != 0) {
        func_80015D60(arg0, 0x14);
        arg0->base.on_screen = 1;
        arg0->base.unk5 = 2;
        return;
    }
    arg0->base.on_screen = 0;
    arg0->base.unk5 = 0;
}

void func_800AF58C(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    if (func_800AF658(arg1) != 0) {
        func_80015DC8(arg0);
        arg0->base.on_screen = 1;
        return;
    }
    if (func_800AF610(arg1) != 0) {
        func_80015D60(arg0, 0x13);
        arg0->base.on_screen = 1;
        arg0->base.unk5 = 1;
        return;
    }
    arg0->base.on_screen = 0;
    arg0->base.unk5 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_07", func_800AF610);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_07", func_800AF658);

void (*D_8010A1C8[])(struct VisualObj*, struct PlayerObj*) = {
    func_800AF488,
    func_800AF504,
    func_800AF58C,
};
