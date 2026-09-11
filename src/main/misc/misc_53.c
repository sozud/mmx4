// MiscObj, misc_object_update_funcs[53]
// 800D2A74..800D3084
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2A74);

void func_800D2B9C(struct MiscObj* arg0)
{
    if (g_Player.x_pos.i.hi >= 0x6E1) {
        arg0->unk5++;
        func_80036AE4(0x14, 0x40);
        background_objects[0].unk24 = 0x6B0;
        background_objects[0].unk26 = 0x6B0;
        arg0->ext.misc_53.timer = 0x50;
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2C04);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2CA4);

void func_800D2D7C(struct MiscObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->y_vel.val < 0) {
        arg0->y_vel.val = 0;
        arg0->unk5++;
    }
}

void func_800D2DCC(struct MiscObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->on_screen == 0) {
        arg0->unk5++;
    }
}

void func_800D2E1C(struct MiscObj* arg0)
{
    struct EffectObj* effect;

    arg0->ext.misc_53.timer = 0x12C;
    arg0->unk5++;
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 0x41;
        effect->id = 0x1C;
    }
}

void func_800D2E64(struct MiscObj* arg0)
{
    struct EffectObj* effect;
    s16 timer;

    timer = arg0->ext.misc_53.timer - 1;
    arg0->ext.misc_53.timer = timer;
    if (timer == 0) {
        arg0->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 2;
            effect->unk2 = 0xC;
            arg0->ext.misc_53.effect = effect;
        }
    }
}

void func_800D2EDC(struct MiscObj* arg0)
{
    if (arg0->ext.misc_53.effect->active == 0) {
        arg0->unk5++;
        func_8002B560(0x1C, 0);
        arg0->ext.misc_53.timer = 0x1E;
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2F34);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2FC4);

void func_800D301C(struct MiscObj* arg0)
{
    engine_obj.unkF = 1;
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_800D3048(struct MiscObj* arg0)
{
    D_8010F580[arg0->state](arg0);
}

union AnimationStep D_8010F550[3] = {
    { .packed = 0x00010001 },
    { .packed = 0x01010001 },
    { .packed = 0x02FE0001 },
};
union AnimationStep* D_8010F55C[1] = { D_8010F550 };

void (*D_8010F560[8])(struct MiscObj*) = {
    func_800D2B9C,
    func_800D2C04,
    func_800D2CA4,
    func_800D2D7C,
    func_800D2DCC,
    func_800D2E1C,
    func_800D2E64,
    func_800D2EDC,
};
void (*D_8010F580[3])(struct MiscObj*) = {
    func_800D2A74,
    func_800D2FC4,
    func_800D301C,
};
