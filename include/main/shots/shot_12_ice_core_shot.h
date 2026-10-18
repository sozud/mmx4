#ifndef MAIN_SHOTS_SHOT_12_ICE_CORE_SHOT_H
#define MAIN_SHOTS_SHOT_12_ICE_CORE_SHOT_H

struct Shot12CollisionData {
    u16 masks[10];
#ifdef MMX4_WIN32
    u8 pad14[4];
#endif
    u8 effect_id;
    u8 animation[15];
};

void ice_core_shot_update(struct ShotObj*);

void func_8009B85C(struct ShotObj*);

void func_8009BA6C(struct ShotObj*);

extern struct Shot12CollisionData ice_core_shard_data;

extern u8 ice_core_shard_debris[4];

#endif
