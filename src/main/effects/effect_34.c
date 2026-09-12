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

INCLUDE_ASM("main/nonmatchings/effects/effect_34", func_800BCEE4);

void func_800BD01C(struct EffectObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/effects/effect_34", func_800BD024);

INCLUDE_ASM("main/nonmatchings/effects/effect_34", func_800BD080);

s16 D_8010BFA8[10] = { 2, 2, 2, 0x46, 0x64, 0x46, 0x46, 0x46, 0x46, 0 };

u8 D_8010BFBC[12] = { 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0, 0, 0 };

s16 D_8010BFC8[10] = { 0xC0, 0x140, 0x2A0, 0x1C0, 0x240, 0x300, 0x380, 0x410, 0x4C0, 0 };

void (*D_8010BFDC[])(struct EffectObj*) = {
    func_800BCE84,
    func_800BCEE4,
    func_800BD01C,
};
