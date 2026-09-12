// EffectObj, effect_object_update_funcs[38]
// 800BD654..800BDE68
#include "common.h"

void func_800BD654(struct EffectObj* arg0)
{
    D_8010C048[arg0->state](arg0);
}

void func_800BD690(struct EffectObj* arg0)
{
    s8 next_state;

    if (engine_obj.substage == 0) {
        arg0->unk2 = (u8)engine_obj.checkpoint;
        func_800BDBD4();
    } else if (engine_obj.checkpoint != 0) {
        next_state = 6;
        goto write_state;
    } else {
        arg0->unk2 = 6;
    }

    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->ext.effect_38.timer = 0;
    next_state = (u8)arg0->state + 1;

write_state:
    arg0->state = next_state;
}

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BD708);

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BD7B0);

void func_800BD890(struct EffectObj* arg0)
{
    arg0->ext.effect_38.timer--;
    if (arg0->ext.effect_38.timer == 0) {
        arg0->ext.effect_38.timer = 0x64;
        arg0->state++;
    }
}

void func_800BD8C4(struct EffectObj* arg0)
{
    if (--arg0->ext.effect_38.timer == 0 && arg0->ext.effect_38.unk16 != 0) {
        func_80036AE4(0x15, 0x40);
        func_800BDB10(arg0);
        arg0->ext.effect_38.timer = 0x64;
        arg0->state++;
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BD938);

void func_800BDA2C(struct EffectObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800BDA4C(void* arg0)
{
    struct MiscObj* obj = find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x22;
        obj->ext.pointer.unk50 = arg0;
        obj->unk2 = 0;
    }
}

void func_800BDA94(void* arg0)
{
    s8 var_s0;
    struct MiscObj* temp_v0;

    var_s0 = 0;
    do {
        temp_v0 = find_free_misc_obj();
        if (temp_v0 != NULL) {
            temp_v0->active = 0x41;
            temp_v0->id = 0x21;
            temp_v0->ext.pointer.unk50 = arg0;
            temp_v0->unk2 = var_s0;
        }
        var_s0 += 1;
    } while (var_s0 < 2U);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BDB10);

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BDBD4);

INCLUDE_ASM("main/nonmatchings/effects/effect_38", func_800BDD08);

void func_800BDDE8(s32 arg0, s32 arg1)
{
    s8 clear_value = 0;
    u32 i = 0;
    s32 count;
    u8* ptr;

    arg0 &= 0xFF;
    arg1 &= 0xFF;
    for (; i < 0x20; i++) {
        if (item_objects[i].id == arg0 && item_objects[i].unk2 == arg1) {
            ptr = (u8*)&item_objects[i];
            count = sizeof(struct ItemObj) - 1;
            do {
                *ptr++ = clear_value;
            } while (count-- != 0);
        }
    }
}

u16 D_8010C02C[14] = {
    0x0190,
    0x0700,
    0,
    0x0300,
    0x0190,
    0x0800,
    0,
    0x0300,
    0x0170,
    0x0C00,
    0,
    0x0300,
    0,
    0x0F78,
};

void (*D_8010C048[])(struct EffectObj*) = {
    func_800BD690,
    func_800BD708,
    func_800BD7B0,
    func_800BD890,
    func_800BD8C4,
    func_800BD938,
    func_800BDA2C,
};
