// EffectObj, effect_object_update_funcs[42]
// 800BE2C4..800BE57C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/effects/effect_42", func_800BE2C4);

void func_800BE30C(struct EffectObj* arg0)
{
    arg0->ext.effect_42.owner.main->ext.main_73.effect_state = 1;
    arg0->unk5++;
}

void func_800BE32C(struct EffectObj* arg0)
{
    if (g_Player.unkBC == 0) {
        arg0->ext.effect_42.owner.player->unk8C = 0;
        arg0->unk5++;
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_42", func_800BE364);

void func_800BE434(struct EffectObj* arg0)
{
    s32 count;
    s32 match;
    u32 i;

    count = 0;
    i = 0;
    match = 3;
    do {
        if (arg0->ext.effect_42.owner.main->ext.main_73_parts.parts[i]->unk5 == match) {
            count += 1;
        }
        i += 1;
    } while (i < 3U);
    if (count == 3) {
        arg0->unk5 = (u8)arg0->unk5 + 1;
        arg0->ext.effect_42.owner.main->ext.main_73_parts.effect_state = 3;
        arg0->ext.effect_42.timer = 0xC8;
    }
}

void func_800BE4A8(struct EffectObj* arg0)
{
    u8 timer;

    timer = arg0->ext.effect_42.timer - 1;
    arg0->ext.effect_42.timer = timer;
    if (timer == 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void func_800BE4D4(struct EffectObj* arg0)
{
    D_8010C100[arg0->unk5](arg0);
}

void func_800BE510(struct EffectObj* arg0)
{
    if (g_Player.unkBC == 0) {
        arg0->ext.effect_42.owner.main->ext.main_73.effect_state = 0;
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void func_800BE540(struct EffectObj* arg0)
{
    D_8010C114[arg0->state](arg0);
}

void (*D_8010C100[5])(struct EffectObj*) = {
    func_800BE30C,
    func_800BE32C,
    func_800BE364,
    func_800BE434,
    func_800BE4A8,
};

void (*D_8010C114[])(struct EffectObj*) = {
    func_800BE2C4,
    func_800BE4D4,
    func_800BE510,
};
