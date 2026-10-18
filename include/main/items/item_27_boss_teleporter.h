#ifndef MAIN_ITEMS_ITEM_27_BOSS_TELEPORTER_H
#define MAIN_ITEMS_ITEM_27_BOSS_TELEPORTER_H

void boss_teleporter_update(struct ItemObj*);

void func_800C71C0(struct ItemObj*);

s8 func_800C7970(struct ItemObj*, struct PlayerObj*);

void boss_teleporter_wait_bosses_cleared(struct ItemObj*);

void boss_teleporter_warp_start(struct ItemObj*);

#endif
