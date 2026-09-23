// EffectObj, effect_object_update_funcs[34]
// 800BCE48..800BD1A4
#include "common.h"

void func_800BCE48(struct EffectObj* arg0)
{
    D_8010BFDC[arg0->state](arg0);
}

void func_800BCE84(struct EffectObj* arg0)
{
    if (engine_obj.checkpoint != 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }

    if (g_Player.x_pos.i.hi >= 0x241) {
        arg0->ext.effect_34.unk14 = 0;
        arg0->ext.effect_34.timer = D_8010BFA8[0];
        arg0->state = 1;
    }
}

void func_800BCEE4(struct EffectObj* self)
{
    struct EffectObj* effect;
    u8 index;
    s16 timer;

    timer = self->ext.effect_34.timer - 1;
    self->ext.effect_34.timer = timer;
    if (timer == 0) {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x21;
            effect->unk2 = D_8010BFBC[self->ext.effect_34.unk14];
            effect->x_pos.u.hi = D_8010BFC8[self->ext.effect_34.unk14];
            effect->y_pos.u.hi = 0x270;
            effect->backref = NULL;
            effect->state = 0;
        }

        index = self->ext.effect_34.unk14 + 1;
        self->ext.effect_34.unk14 = index;
        timer = D_8010BFA8[index];
        self->ext.effect_34.timer = timer;
        if (timer == 0) {
            self->state = 2;
        }
    } else if (self->ext.effect_34.unk14 == 1 && !(background_objects[g_Player.bg_offset].unk34 & 0x10)) {
        func_80028B68(8, 4, 2);
    }
}

void func_800BD01C(struct EffectObj* arg0)
{
}

void func_800BD024(struct EffectObj* arg0)
{
    u16* src;
    u16* dst;
    u32 count;

    src = D_8010BFE8;
    count = 0;
    arg0->ext.unk_effect.unk14 = 1;
    arg0->ext.unk_effect.unk15 = 0;
    arg0->state++;
    dst = SP_PALETTE;
    arg0->ext.effect_4.unk16 = 0x20;
    dst += 0x5E0 / 2;
    do {
        *dst++ = *src++;
        count++;
    } while (count < 0x10U);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_34", func_800BD080);

s16 D_8010BFA8[10] = { 2, 2, 2, 0x46, 0x64, 0x46, 0x46, 0x46, 0x46, 0 };

u8 D_8010BFBC[12] = { 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0, 0, 0 };

s16 D_8010BFC8[10] = { 0xC0, 0x140, 0x2A0, 0x1C0, 0x240, 0x300, 0x380, 0x410, 0x4C0, 0 };

void (*D_8010BFDC[])(struct EffectObj*) = {
    func_800BCE84,
    func_800BCEE4,
    func_800BD01C,
};
