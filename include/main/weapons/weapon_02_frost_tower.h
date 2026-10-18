#ifndef MAIN_WEAPONS_WEAPON_02_FROST_TOWER_H
#define MAIN_WEAPONS_WEAPON_02_FROST_TOWER_H

void frost_tower_update(struct WeaponObj*);

void frost_tower_charged_update(struct WeaponObj*);

void frost_shard_update(struct MiscObj* arg0);

void frost_sparkle_update(struct MiscObj* arg0);

void func_80093D78(struct WeaponObj*);

void frost_tower_spawn_shard(struct WeaponObj*);

void func_80094280(struct WeaponObj*);
void func_800942E8(struct WeaponObj*);

void func_800944B8(struct WeaponObj*);

void frost_tower_hide(struct WeaponObj*);

#endif
