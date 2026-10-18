#ifndef MAIN_MAINS_MAIN_57_FROST_WALRUS_H
#define MAIN_MAINS_MAIN_57_FROST_WALRUS_H

void frost_walrus_update(struct MainObj* arg0);

void func_80072418(struct MainObj*);

void frost_walrus_set_floor_tiles(s32 arg0);

void frost_walrus_start_warning(struct MainObj*);
void func_800722A0(struct MainObj*);

void frost_walrus_death_explode(struct MainObj*);

void frost_walrus_intro_approach(struct MainObj*);

void frost_walrus_intro_burst(struct MainObj*);

void frost_walrus_charge_start(struct MainObj*);

void frost_walrus_shards_count(struct MainObj*);
void frost_walrus_shards_fire(struct MainObj*);

void frost_walrus_breath_blow(struct MainObj*);

void frost_walrus_blizzard_blow(struct MainObj*);

void func_80073E80(struct MainObj*);

void frost_walrus_regrow_start(struct MainObj*);

extern u16 frost_walrus_floor_tiles[18];
extern u16 frost_walrus_floor_tiles_rush[20];

extern struct Unk_unk68 frost_walrus_hurt_box;
extern struct Unk_unk68 frost_walrus_charge_hurt_box;
extern struct Unk_unk68 frost_walrus_attack_box;
extern struct Unk_unk68 frost_walrus_charge_attack_box;

#endif
