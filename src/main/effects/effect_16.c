// EffectObj, effect_object_update_funcs[16]
// 800B8F5C..800B9100
#include "common.h"

void func_800B8F5C(struct EffectObj* arg0)
{
    D_8010B6F4[arg0->state](arg0);
}

void func_800B8F98(struct EffectObj* arg0)
{
    s32 index;
    u16 value;

    arg0->ext.effect_16.saved_background_2A = background_objects[0].unk2A;
    index = arg0->unk2;
    arg0->ext.effect_16.saved_background_28 = background_objects[0].unk28;
    background_objects[0].unk26 = D_8010B700[index].primary;
    value = D_8010B700[arg0->unk2].primary;
    background_objects[0].unk47 = 6;
    background_objects[0].unk30 = 0;
    background_objects[0].unk32 = 0x140;
    background_objects[0].pad51[0] = 0;
    background_objects[0].unk24 = value;
    arg0->state++;
}

void func_800B902C(struct EffectObj* arg0)
{
    if (background_objects[0].x_pos.i.hi >= *(s16*)&D_8010B700[arg0->unk2].primary) {
        arg0->state++;
    }
}

void func_800B9070(struct EffectObj* arg0)
{
    u16 unk6;

    background_objects[0].unk24 = D_8010B700[arg0->unk2].secondary;
    background_objects[0].unk2A = arg0->ext.effect_16.saved_background_2A;
    unk6 = arg0->ext.effect_16.saved_background_28;
    background_objects[0].pad51[0] = 1;
    background_objects[0].unk30 = 0xA0;
    background_objects[0].unk32 = 0xA0;
    background_objects[0].unk47 = 2;
    background_objects[0].unk48 = 8;
    background_objects[0].unk28 = unk6;
    func_8002B108(OBJECT_HEADER(arg0));
}

void (*D_8010B6F4[])(struct EffectObj*) = {
    func_800B8F98,
    func_800B902C,
    func_800B9070,
};

struct Effect16Coordinate D_8010B700[2] = {
    { 0x7000, 0x7100 },
    { 0x4000, 0x4150 },
};
