#ifndef MAIN_WEAPONS_WEAPON_01_LIGHTNING_WEB_H
#define MAIN_WEAPONS_WEAPON_01_LIGHTNING_WEB_H

void lightning_web_update(struct WeaponObj*);

void lightning_web_charged_update(struct WeaponObj*);

void lightning_web_charged_vanish(struct WeaponObj*);

void func_80093930(struct WeaponObj*);

void lightning_web_charged_vanish(struct WeaponObj*);

void lightning_web_charged_part_fly(struct WeaponObj*);
void lightning_web_charged_part_hold(struct WeaponObj*);

extern struct Unk_unk68 lightning_web_charged_part_box[];

extern struct Unk_unk68 lightning_web_shot_box[];

#endif
