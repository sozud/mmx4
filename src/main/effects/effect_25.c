// EffectObj, effect_object_update_funcs[25]
// 800BAF60..800BB1F0
#include "common.h"

s16 D_8010BE8C[2] = { 0x0580, 0x0A40 };

void func_800BAF60(struct EffectObj* arg0)
{
    D_8010BE90[arg0->state](arg0);
}

void func_800BAF9C(struct EffectObj* arg0)
{
    arg0->unk5 = 2;
    arg0->ext.effect_25.unk14 = 3;
    arg0->state++;
    func_800BAFD4(arg0);
}

void func_800BAFD4(struct EffectObj* arg0)
{
    arg0->ext.effect_25.unk15 = arg0->ext.effect_25.unk14;
    func_800BB180(arg0);
    D_8010BE98[arg0->unk5](arg0);
}

void func_800BB028(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BB068(arg0);
    } else {
        func_800BB088(arg0);
    }
}

void func_800BB068(struct EffectObj* arg0)
{
    background_objects[0].unk2E = 0xC0;
    arg0->unk6++;
}

void func_800BB088(struct EffectObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800BB098(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BB0D8(arg0);
    } else {
        func_800BB0F8(arg0);
    }
}

void func_800BB0D8(struct EffectObj* arg0)
{
    background_objects[0].unk2E = 0x80;
    arg0->unk6++;
}

void func_800BB0F8(struct EffectObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800BB108(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800BB148(arg0);
    } else {
        func_800BB168(arg0);
    }
}

void func_800BB148(struct EffectObj* arg0)
{
    background_objects[0].unk2E = 0xC0;
    arg0->unk6++;
}

void func_800BB168(struct EffectObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800BB178(struct EffectObj* arg0)
{
}

void func_800BB180(struct EffectObj* arg0)
{
    s16 player_x = g_Player.x_pos.i.hi;
    s8 offset = 0;
    while (1) {
        if (player_x - D_8010BE8C[offset] < 0) {
            break;
        }
        offset++;
        if (offset >= 2) {
            break;
        }
    }
    arg0->ext.effect_25.unk14 = offset;
    if (offset != arg0->ext.effect_25.unk15) {
        arg0->unk5 = offset;
        arg0->unk6 = 0;
    }
}

void (*D_8010BE90[])(struct EffectObj*) = {
    func_800BAF9C,
    func_800BAFD4,
};

void (*D_8010BE98[4])(struct EffectObj*) = {
    func_800BB028,
    func_800BB098,
    func_800BB108,
    func_800BB178,
};
