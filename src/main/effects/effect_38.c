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

void func_800BD708(struct EffectObj* self)
{
    s8 subtype;

    subtype = self->unk2;
    if (g_Player.x_pos.i.hi >= D_8010C02C[subtype * 2]) {
        if (!(subtype & 1) && engine_obj.substage == 0) {
            func_800BDA4C(self);
            engine_obj.unk10 = 1;
            engine_obj.unk12 = 1;
            engine_obj.unk11 = 1;
            engine_obj.unk13 = 1;
        }
        self->state++;
    }
}

void func_800BD7B0(struct EffectObj* self)
{
    s8 subtype;

    func_800BDBD4();
    subtype = self->unk2;
    if (g_Player.x_pos.i.hi >= D_8010C02C[subtype * 2 + 1] && (subtype != 6 || g_Player.y_pos.i.hi < 0x400)) {
        func_80036AE4(0x14, 0x40);
        func_800BDD08(self);
        if ((engine_obj.checkpoint & 1) || engine_obj.substage != 0) {
            self->ext.effect_38.active = 1;
            self->ext.effect_38.timer = 0xA;
            self->state += 2;
        } else {
            self->ext.effect_38.timer = 0x14;
            self->state++;
        }
    }
}

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
    if (--arg0->ext.effect_38.timer == 0 && arg0->ext.effect_38.active != 0) {
        func_80036AE4(0x15, 0x40);
        func_800BDB10(arg0);
        arg0->ext.effect_38.timer = 0x64;
        arg0->state++;
    }
}

void func_800BD938(struct EffectObj* self)
{
    u8 timer;

    if (self->ext.effect_38.timer == 0x50) {
        func_800BDA94(self);
    }

    timer = self->ext.effect_38.timer - 1;
    self->ext.effect_38.timer = timer;
    if (timer != 0) {
        return;
    }

    switch (self->ext.effect_38.variant) {
    case 0:
        engine_obj.checkpoint++;
        break;
    case 1:
        engine_obj.checkpoint += 2;
        break;
    case 2:
        break;
    default:
        engine_obj.checkpoint += 2;
        break;
    }

    if (engine_obj.checkpoint < 6) {
        engine_obj.unkF = -0x40;
    } else {
        engine_obj.unkF = 0x40;
    }
    self->state++;
}

void func_800BDA2C(struct EffectObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800BDA4C(struct EffectObj* arg0)
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

void func_800BDB10(struct EffectObj* self)
{
    struct MiscObj* misc;
    s8 state;
    u8 subtype;

    if (self->ext.effect_38.active == 0 || (self->unk2 & 1) != 0 || engine_obj.substage != 0) {
        return;
    }
    misc = find_free_misc_obj();
    if (misc == NULL) {
        return;
    }
    misc->active = 0x41;
    misc->id = 0x21;
    misc->ext.misc_7.position = self;
    subtype = self->ext.effect_38.variant;
    switch (subtype) {
    case 0:
        state = 2;
        break;
    case 1:
        state = 3;
        break;
    case 2:
        state = 4;
        break;
    default:
        return;
    }
    misc->unk2 = state;
}

void func_800BDBD4(void)
{
    switch (engine_obj.checkpoint) {
    case 1:
        if (engine_obj.cur_character == 0) {
            func_800BDDE8(2, 4);
            func_800BDDE8(2, 0xF);
            func_800BDDE8(0x1A, 0);
        } else {
            func_800BDDE8(2, 0xC);
            func_800BDDE8(2, 0xF);
        }
        break;
    case 3:
        if (engine_obj.cur_character == 0) {
            func_800BDDE8(2, 4);
            func_800BDDE8(2, 0xC);
            func_800BDDE8(0x1A, 0);
        } else {
            func_800BDDE8(2, 4);
            func_800BDDE8(2, 0xF);
        }
        break;
    case 5:
        if (engine_obj.cur_character == 0) {
            func_800BDDE8(2, 4);
            func_800BDDE8(2, 0xC);
            func_800BDDE8(2, 0xF);
        } else {
            func_800BDDE8(2, 4);
            func_800BDDE8(2, 0xC);
        }
        break;
    }
}

void func_800BDD08(struct EffectObj* self)
{
    u32 i;
    s32 count;
    s8 fill = 0;
    s8* ptr;

    for (i = 0; i < 0x30; i++) {
        ptr = (s8*)&main_objects[i];
        count = sizeof(main_objects[i]) - 1;
        do {
            *ptr++ = fill;
        } while (count-- != 0);
    }

    for (i = 0; i < 0x20; i++) {
        ptr = (s8*)&shot_objects[i];
        count = sizeof(shot_objects[i]) - 1;
        do {
            *ptr++ = fill;
        } while (count-- != 0);
    }

    for (i = 0; i < 0x40; i++) {
        if (misc_objects[i].id < 0x21 || misc_objects[i].id > 0x22) {
            ptr = (s8*)&misc_objects[i];
            count = sizeof(misc_objects[i]) - 1;
            do {
                *ptr++ = fill;
            } while (count-- != 0);
        }
    }
}

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
