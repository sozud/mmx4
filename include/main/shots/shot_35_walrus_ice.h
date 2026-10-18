#ifndef MAIN_SHOTS_SHOT_35_WALRUS_ICE_H
#define MAIN_SHOTS_SHOT_35_WALRUS_ICE_H

void walrus_ice_update(struct ShotObj*);

extern struct Unk_unk68 walrus_ice_lob_terrain_box;
extern struct Unk_unk68 walrus_ice_icicle_hurt_box;
extern struct Unk_unk68 walrus_ice_icicle_attack_box;

void walrus_ice_lob(struct ShotObj*);

void func_800A241C(struct ShotObj*);

void func_800A25EC(struct ShotObj*);

void walrus_ice_icicle_wait_drop(struct ShotObj*);

void walrus_ice_ball_main(struct ShotObj*);

void walrus_ice_chunk_main(struct ShotObj*);

#endif
