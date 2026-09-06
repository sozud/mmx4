// VisualObj, visual_object_update_funcs[0]
// 800AEAC0..800AED18
#include "common.h"

void func_800AEAC0(struct VisualObj* arg0)
{
    struct PlayerObj* var_a1;
    if (g_Player.unkDE == 0) {
        var_a1 = &g_Player;
    } else {
        var_a1 = &g_Entity;
    }
    D_8010A1A0[arg0->state](arg0, var_a1);
}

void func_800AEB1C(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    arg0->on_screen = 1;
    arg0->unk38 = 0;
    arg0->unk3C = (void*)((s8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[1]);
    arg0->animation_table = &D_8011BF40;
    arg0->unk40 = 0;
    arg0->unk42 = 0x7804;
    arg0->unk16 = 1;
    func_800AEC9C(arg0, arg1);
    func_80015D60(arg0, 3);
    arg0->state++;
    func_8002B318(arg0, 0x20, 0x20);
}

void func_800AEBA8(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    s32 var_a0 = 0;

    func_80015DC8(arg0);
    if ((*(s32*)&arg1->state & 0xFFFF00) == 0xB00) {
        var_a0 = 1;
    }
    if (arg1->unk5 == 0x34) {
        var_a0 = 1;
    }
    if (var_a0 != 0) {
        func_800AEC9C(arg0, arg1);
    } else {
        func_80015D60(arg0, 4);
        arg0->state++;
    }
    func_8002B318(arg0, 0x20, 0x20);
}

void func_800AEC48(struct VisualObj* arg0, struct PlayerObj* arg1)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step < 0) {
        ZeroObjectState(arg0);
        return;
    }
    func_8002B318(arg0, 0x20, 0x20);
}

void func_800AEC9C(struct Unk* arg0, struct Unk* arg1)
{
    arg0->unk15 = arg1->unk15;
    if (arg0->unk15 == 0) {
        arg0->x_pos.i.hi = arg1->x_pos.i.hi + D_8010A1AC[arg1->unk2].x;
    } else {
        arg0->x_pos.i.hi = arg1->x_pos.i.hi - D_8010A1AC[arg1->unk2].x;
    }
    arg0->y_pos.i.hi = arg1->y_pos.i.hi + D_8010A1AC[arg1->unk2].y;
}

void (*D_8010A1A0[])(struct VisualObj*, struct PlayerObj*) = {
    func_800AEB1C,
    func_800AEBA8,
    func_800AEC48,
};
