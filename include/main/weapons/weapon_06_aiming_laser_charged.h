#ifndef MAIN_WEAPONS_WEAPON_06_AIMING_LASER_CHARGED_H
#define MAIN_WEAPONS_WEAPON_06_AIMING_LASER_CHARGED_H

void func_800961B0(struct WeaponObj*);

void aiming_laser_charged_update(struct WeaponObj*);

void aiming_laser_reticle_init(struct WeaponObj*, struct PlayerObj*);
void aiming_laser_reticle_place(struct WeaponObj*, struct PlayerObj*);
s32 aiming_laser_try_lock_on(struct WeaponObj*, struct PlayerObj*, struct MainObj*);

// aiming_laser_marker_state_funcs
extern void (*aiming_laser_marker_state_funcs[])(struct WeaponObj*);

void aiming_laser_marker_wait_fire(struct WeaponObj*, struct PlayerObj*, struct PlayerObj*);

void aiming_laser_charged_init(struct WeaponObj*);
void func_80096B54(struct WeaponObj*);

extern struct Unk_unk68 aiming_laser_marker_box[];

void aiming_laser_charged_aim(struct WeaponObj*, struct PlayerObj*);

#endif
