#ifndef MAIN_EFFECTS_EFFECT_05_TILE_SCANNER_H
#define MAIN_EFFECTS_EFFECT_05_TILE_SCANNER_H

void func_800B60BC(struct EffectObj* arg0);

// tile_scanner_state_funcs
extern void (*tile_scanner_state_funcs[])(struct EffectObj*);

void func_800B64BC(struct EffectObj*);

// tile_scanner_fill_funcs
extern void (*tile_scanner_fill_funcs[])(struct EffectObj*);
void func_800B6660(struct EffectObj*);

#endif
