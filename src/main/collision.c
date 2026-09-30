// hitbox and terrain collision
// 8002BB80..8002C760
#include "common.h"

void func_8002C99C(struct PlayerObj* arg0);
s32 func_8002D6BC(struct PlayerObj* arg0, u8 arg1);
s32 func_8002CAF0(struct PlayerObj* arg0, u8 arg1);
s32 func_8002CC34(struct PlayerObj* arg0, u8 arg1);
s32 func_8002CD70(struct PlayerObj* arg0, u8 arg1);
void func_8002CA18(struct PlayerObj* arg0);
void func_8002CB58(struct PlayerObj* arg0);
void func_8002CC98(struct PlayerObj* arg0);
struct EffectSpawnData {
    u8 visual_id;
    s8 effect_type;
    s8 set_facing;
    s8 keep_facing;
    u8 animation_id;
};

// hitboxes_overlap
INCLUDE_ASM("main/nonmatchings/collision", func_8002BB80);

INCLUDE_ASM("main/nonmatchings/collision", func_8002BD58);

s32 func_8002C160(struct CollisionObj* arg0, struct CollisionObj* arg1)
{
    s16 center0;
    s16 center1;
    s16 distance;
    struct Unk_unk68* bounds0;
    struct Unk_unk68* bounds1;
    struct Unk_unk68* initial_bounds0;
    struct Unk_unk68* initial_bounds1;
    struct CollisionObj* object1;
    struct CollisionObj* object0;

    object0 = arg0;
    object1 = arg1;
    initial_bounds0 = object0->collision_bounds;
    if (initial_bounds0 == NULL) {
        return 0;
    }
    initial_bounds1 = object1->collision_bounds;
    if (initial_bounds1 == NULL) {
        return 0;
    }

    center0 = object0->x_pos.i.hi + initial_bounds0->unk0;
    center1 = object1->x_pos.i.hi + initial_bounds1->unk0;
    if ((center0 - center1) >= 0) {
        distance = center0 - center1;
    } else {
        distance = center1 - center0;
    }

    bounds0 = object0->collision_bounds;
    bounds1 = object1->collision_bounds;
    if (distance >= bounds0->unk2 + bounds1->unk2) {
        return 0;
    }

    center0 = object0->y_pos.i.hi + bounds0->unk1;
    center1 = object1->y_pos.i.hi + bounds1->unk1;
    if ((center0 - center1) >= 0) {
        distance = center0 - center1;
    } else {
        distance = center1 - center0;
    }
    return distance < object0->collision_bounds->unk3 + object1->collision_bounds->unk3;
}

void func_8002C26C(struct CollisionObj* arg0, struct CollisionObj* arg1)
{
    s16 center0;
    s16 center1;
    struct Unk_unk68* bounds1;
    struct Unk_unk68* bounds0;

    bounds0 = arg0->collision_bounds;
    bounds1 = arg1->collision_bounds;
    center0 = arg0->x_pos.i.hi + bounds0->unk0;
    center1 = arg1->x_pos.i.hi + bounds1->unk0;
    if (center0 > center1) {
        center0 -= bounds0->unk2;
        center1 += bounds1->unk2;
    } else {
        center0 += bounds0->unk2;
        center1 -= bounds1->unk2;
    }
    arg1->unk6C = center0 - center1;
}

void func_8002C2EC(struct CollisionObj* arg0, struct CollisionObj* arg1)
{
    s16 center0;
    s16 center1;
    struct Unk_unk68* bounds1;
    struct Unk_unk68* bounds0;

    bounds0 = arg0->collision_bounds;
    bounds1 = arg1->collision_bounds;
    center0 = arg0->y_pos.i.hi + bounds0->unk1;
    center1 = arg1->y_pos.i.hi + bounds1->unk1;
    if (center0 > center1) {
        center0 = center0 - bounds0->unk3;
        center1 = bounds1->unk3 + center1;
    } else {
        center0 = bounds0->unk3 + center0;
        center1 = center1 - bounds1->unk3;
    }
    arg1->unk6E = center0 - center1;
}

INCLUDE_ASM("main/nonmatchings/collision", func_8002C36C);

// megaman falls through floor in intro stage if nopped out
// asm(".rept 81 ; nop ; .endr");
void CollisionRelated(struct PlayerObj* arg0) // was func_8002C614
{
    s32 temp_v1;

    arg0->unk70 = 0;
    arg0->touching_spikes = 0;

    if (arg0->unk68 != NULL) {
        func_8002C760(arg0);
        temp_v1 = arg0->x_pos.val - arg0->unk18.val;
        D_8013B7D8 = 0;
        D_8013B7DC = 0;

        if (temp_v1 != 0) {
            if (temp_v1 > 0) {
                func_8002CB58(arg0);
            } else {
                func_8002CA18(arg0);
            }
        }

        if (arg0->y_pos.val - arg0->unk1C.val >= 0) {
            func_8002CDD4(arg0);
            if (D_8013B7D8 != 0) {
                return;
            }
        } else {
            func_8002CC98(arg0);
        }

        if (D_8013B7DC & 0xC) {
            if ((D_8013B7DC & 3) != 0) {
                if ((D_8013B7DC & 4) || (D_8013B804 >= -8)) {
                    func_8002C954(arg0);
                } else {
                    func_8002C99C(arg0);
                }
            } else {
                func_8002D25C(arg0);
            }
        } else if ((D_8013B7DC & 3) != 0) {
            func_8002D490(arg0);
        }

        func_8002C808(arg0);
    }
}

// get_tile_attribute

// damage_player_on_contact

// check_weapon_hits
