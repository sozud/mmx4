// EffectObj, effect_object_update_funcs[8]
// 800B7078..800B75C8
#include "common.h"

void func_800B7078(struct EffectObj* arg0)
{
    D_8010B4D8[arg0->state](arg0);
}

void func_800B70B4(struct EffectObj* arg0)
{
    arg0->unk5 = 4;
    arg0->ext.unk_effect.unk14 = 5;
    arg0->state++;
    func_800B70EC(arg0);
}

void func_800B70EC(struct EffectObj* arg0)
{
    arg0->ext.unk_effect.unk15 = arg0->ext.unk_effect.unk14;
    func_800B7528(arg0);
    D_8010B4E0[arg0->unk5](arg0);
}

void func_800B7140(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B7180(arg0);
    } else {
        func_800B71A8();
    }
}

void func_800B7180(struct EffectObj* arg0)
{
    arg0->unk6++;
    background_objects[0].unk4 = 2;
    arg0->ext.effect_8.unk16 = 0;
    arg0->ext.effect_8.unk18 = 0;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_08", func_800B71A8);

void func_800B72C4(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B7304(arg0);
    } else {
        func_800B7318(arg0);
    }
}

void func_800B7304(struct EffectObj* arg0)
{
    arg0->unk6++;
}

void func_800B7318(struct EffectObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void func_800B7328(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B7368(arg0);
    } else {
        func_800B7394(arg0);
    }
}

void func_800B7368(struct EffectObj* arg0)
{
    background_objects[1].unk4 = 1;
    background_objects[2].unk4 = 3;
    arg0->unk6++;
}

void func_800B7394(struct EffectObj* arg0)
{
    if (g_Player.x_pos.i.hi >= 0xDD0) {
        engine_obj.checkpoint = 2;
        engine_obj.unkF = -0x40;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_800B73D4(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B7414(arg0);
    } else {
        func_800B7440(arg0);
    }
}

void func_800B7414(struct EffectObj* arg0)
{
    background_objects[1].unk4 = 6;
    background_objects[2].unk4 = 1;
    arg0->unk6++;
}

void func_800B7440(struct EffectObj* arg0)
{
    if (g_Player.x_pos.i.hi < 0x1709) {
        engine_obj.checkpoint = 3;
        engine_obj.unkF = -0x40;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_800B7480(struct EffectObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_800B74C0(arg0);
    } else {
        func_800B74EC(arg0);
    }
}

void func_800B74C0(struct EffectObj* arg0)
{
    background_objects[1].unk4 = 1;
    background_objects[2].unk4 = 3;
    arg0->unk6++;
}

void func_800B74EC(struct EffectObj* arg0)
{
    if (g_Player.x_pos.i.hi < 0x112D) {
        engine_obj.unkF = 0x40;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_800B7520(struct EffectObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/effects/effect_08", func_800B7528);

s16 D_8010B4D0[4] = { 0x0760, 0x0808, 0x1700, 0 };

void (*D_8010B4D8[])(struct EffectObj*) = {
    func_800B70B4,
    func_800B70EC,
};

void (*D_8010B4E0[6])(struct EffectObj*) = {
    func_800B7140,
    func_800B72C4,
    func_800B7328,
    func_800B73D4,
    func_800B7480,
    func_800B7520,
};
