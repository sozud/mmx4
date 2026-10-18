#ifndef MAIN_LAYERS_LAYER_05_AIRSHIP_BOB_H
#define MAIN_LAYERS_LAYER_05_AIRSHIP_BOB_H

void airship_bob_update(struct LayerObj*);

void func_800DA2D4(struct LayerObj*);
void func_800DA358(struct LayerObj*);

// airship_bob_section_funcs
extern void (*airship_bob_section_funcs[])(struct LayerObj*);

#endif
