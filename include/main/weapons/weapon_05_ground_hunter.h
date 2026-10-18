#ifndef MAIN_WEAPONS_WEAPON_05_GROUND_HUNTER_H
#define MAIN_WEAPONS_WEAPON_05_GROUND_HUNTER_H

void ground_hunter_update(struct WeaponObj*);

void ground_hunter_charged_update(struct WeaponObj*);

void ground_hunter_start_burst(struct WeaponObj*);

void func_80095E3C(struct WeaponObj*);

void func_80096060(struct WeaponObj*);
void ground_hunter_charged_shot_fly(struct WeaponObj*);

extern struct Unk_unk68 ground_hunter_terrain_box[];

#endif
