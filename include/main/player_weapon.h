#ifndef MAIN_PLAYER_WEAPON_H
#define MAIN_PLAYER_WEAPON_H

struct PlayerShotTiming {
    u8 pose_time;
    u8 cooldown;
};

union PlayerChargeData {
    struct {
        s8 animation_indices[6];
        s8 initial_thresholds[3];
        s8 linked_thresholds[15];
    } charge;
    struct {
        s8 health_divisors[18];
        s8 alignment_padding[6];
    } hud;
    s8 shot_costs[24];
};

enum {
    PLAYER_CHARGE_NONE,
    PLAYER_CHARGE_PARTIAL,
    PLAYER_CHARGE_FULL,
};

void player_fire_weapon(struct PlayerObj*);
void player_fire_weapon(struct PlayerObj*);
void player_fire_none(struct PlayerObj*);
void player_fire_weapon(struct PlayerObj*);
void player_fire_none(struct PlayerObj*);
void player_fire_weapon(struct PlayerObj*);
void player_fire_none(struct PlayerObj*);
void player_fire_none(struct PlayerObj*);
void func_80037C28(struct PlayerObj*);
void player_fire_charged_buster(struct PlayerObj*);
void player_fire_lightning_web_charged(struct PlayerObj*);
void player_fire_none(struct PlayerObj*);
void player_fire_none(struct PlayerObj*);
void player_fire_none(struct PlayerObj*);
void player_fire_weapon(struct PlayerObj*);
void player_fire_weapon(struct PlayerObj*);
void player_fire_none(struct PlayerObj*);
void func_80037C28(struct PlayerObj*);
void player_fire_charged_buster(struct PlayerObj*);
void player_fire_weapon(struct PlayerObj*);
void player_fire_charged_buster(struct PlayerObj*);

#ifdef MMX4_PC
extern s32 player_charge_released (struct PlayerObj *arg0);

extern void player_update_weapon (struct PlayerObj *arg0);

extern void player_check_special_button (struct PlayerObj *arg0);

extern void player_update_charge (struct PlayerObj *arg0);
extern void player_charge_shoot_button (struct PlayerObj *arg0);
extern void player_charge_special_button (struct PlayerObj *arg0);

extern void player_reset_charge (struct PlayerObj *arg0);

extern void func_80038568 (struct PlayerObj *arg0, s32 arg1);
#endif

extern union PlayerChargeData player_weapon_energy;

void func_80037484(struct PlayerObj*, s32);

void player_reset_weapon(struct PlayerObj*);

s32 player_check_shoot_ladder(struct PlayerObj*);

s32 player_check_shoot(struct PlayerObj* self);

void player_equip_weapon(struct PlayerObj* self);

void player_reset_charge_and_weapon(struct PlayerObj* self);

void player_set_animation_shooting(struct PlayerObj* self, s32 animation);

void player_update_shot_types(struct PlayerObj* self);

#endif
