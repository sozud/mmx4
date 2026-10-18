#ifndef MAIN_EFFECTS_EFFECT_28_FORTRESS_COLLAPSE_H
#define MAIN_EFFECTS_EFFECT_28_FORTRESS_COLLAPSE_H

void fortress_collapse_update(struct EffectObj* arg0);

void func_800BBD88(struct EffectObj*);

// fortress_collapse_flash_funcs
extern void (*fortress_collapse_flash_funcs[])(struct EffectObj*);

void fortress_collapse_spawn_random_explosion(struct EffectObj*);

#endif
