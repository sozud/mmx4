// EffectObj, effect_object_update_funcs[12]
// 800B806C..800B84DC
#include "common.h"

u8 D_8010B61C[8] = { 12, 25, 12, 12, 12, 12, 12, 12 };
u8 D_8010B624[8] = { 2, 1, 2, 2, 2, 2, 2, 2 };

void func_800B806C(struct EffectObj* arg0)
{
    D_8010B62C[arg0->state](arg0);
}

void func_800B80A8(struct EffectObj* arg0)
{
    arg0->ext.effect_12.timer = 0x60;
    arg0->ext.effect_12.children[0] = NULL;
    arg0->ext.effect_12.children[1] = NULL;
    arg0->ext.effect_12.children[2] = NULL;
    arg0->ext.effect_12.children[3] = NULL;
    arg0->ext.effect_12.cooldown = 0;
    arg0->ext.effect_12.spawned = 0;
    arg0->ext.effect_12.child_count = (u8)arg0->unk2 >> 4;
    arg0->ext.effect_12.child_id = D_8010B61C[(u8)arg0->unk2 & 0xF];
    arg0->ext.effect_12.child_subtype = D_8010B624[(u8)arg0->unk2 & 0xF];
    arg0->state = 1;
    arg0->unk5 = 0;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_12", func_800B8114);

void func_800B8470(struct EffectObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/effects/effect_12", func_800B8490);

void (*D_8010B62C[])(struct EffectObj*) = {
    func_800B80A8,
    func_800B8114,
    func_800B8470,
};
