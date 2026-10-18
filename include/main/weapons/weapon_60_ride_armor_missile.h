#ifndef MAIN_WEAPONS_WEAPON_60_RIDE_ARMOR_MISSILE_H
#define MAIN_WEAPONS_WEAPON_60_RIDE_ARMOR_MISSILE_H

struct Weapon60SpawnOffset {
    s16 x;
    s16 y;
};

void ride_armor_missile_update(struct WeaponObj*);

void func_80098F88(struct WeaponObj*);
void func_80099118(struct WeaponObj*);

extern u8 ride_armor_missile_hit_box[4];
extern struct Weapon60SpawnOffset ride_armor_missile_offsets[3];

#endif
