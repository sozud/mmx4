#ifndef MAIN_EFFECTS_EFFECT_03_PALETTE_ANIMATOR_H
#define MAIN_EFFECTS_EFFECT_03_PALETTE_ANIMATOR_H

struct PaletteAnimatorTarget {
    u8 palette;
    u8 count;
};

void palette_animator_update(struct EffectObj* arg0);

void func_800B5D04(struct EffectObj*);

#endif
