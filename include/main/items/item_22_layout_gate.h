#ifndef MAIN_ITEMS_ITEM_22_LAYOUT_GATE_H
#define MAIN_ITEMS_ITEM_22_LAYOUT_GATE_H

void layout_gate_update(struct ItemObj*);

void layout_gate_spawn_alarm(struct ItemObj*);

extern s32 layout_gate_unused[4];
void layout_gate_check_layout(struct ItemObj*);
void layout_gate_apply_layout(struct ItemObj*);
void func_800C5994(struct ItemObj*, u8);

#endif
