// EffectObj, effect_object_update_funcs[36]
// 800BD1E4..800BD384
#include "common.h"

void func_800BD1E4(struct EffectObj* arg0)
{
    struct EffectObj* spawned;

    spawned = find_free_effect_obj();
    if (spawned != NULL) {
        spawned->active = 1;
        spawned->id = 2;
        spawned->unk2 = 0xC;
        arg0->ext.effect_36.spawned_effect = spawned;
        arg0->state = 1;
    }
    arg0->ext.effect_36.timer = 0x1E;
}

void func_800BD23C(struct EffectObj* arg0)
{
    struct EffectObj* spawned = arg0->ext.effect_36.spawned_effect;
    if ((spawned->active == 0) || (spawned->id != 2)) {
        arg0->state = 2;
        g_Player.unk61 = 0x78;
    }
}

INCLUDE_ASM("main/nonmatchings/effects/effect_36", func_800BD280);

void func_800BD31C(struct EffectObj* arg0)
{
    engine_obj.unkF = 0x40;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800BD348(struct EffectObj* arg0)
{
    D_8010C008[arg0->state](arg0);
}

u16 D_8010BFE8[16] = {
    0,
    0xFFFF,
    0xAB3F,
    0x829F,
    0x81FF,
    0x815F,
    0x80DD,
    0x84D8,
    0x84B4,
    0x8470,
    0xAB3F,
    0x829F,
    0x81FF,
    0x815F,
    0x80DD,
    0x84D4,
};

void (*D_8010C008[])(struct EffectObj*) = {
    func_800BD1E4,
    func_800BD23C,
    func_800BD280,
    func_800BD31C,
};
