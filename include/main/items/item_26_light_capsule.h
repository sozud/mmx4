#ifndef MAIN_ITEMS_ITEM_26_LIGHT_CAPSULE_H
#define MAIN_ITEMS_ITEM_26_LIGHT_CAPSULE_H

void capsule_glass_update(struct VisualObj*);
void capsule_scan_update(struct VisualObj*);
void capsule_beam_update(struct VisualObj*);
void func_800C6EDC(struct VisualObj*);

void capsule_visual_init(struct VisualObj*, struct PlayerObj*);

void light_capsule_update(struct ItemObj*);

void light_capsule_wait_player(struct ItemObj*);

void light_capsule_spawn_visual(struct ItemObj*, s8, s8);

void func_800C63BC(struct ItemObj*);

#endif
