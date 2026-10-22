// hitbox and terrain collision
// 8002BB80..8002C760
#include "common.h"
#include "main/1CF60.h"
#include "main/collision.h"

void func_8002C760(struct PlayerObj* arg0);
void func_8002C954(struct PlayerObj* arg0);
void func_8002CDD4(struct PlayerObj* arg0);

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
#ifdef MMX4_PC
void func_8002C36C(struct PlayerObj* arg0, struct PlayerObj* arg1, s32 slot);
s32 func_8002BB80(struct MainObj* obj0, struct MainObj* obj1);
s32 func_8002BD58(struct MainObj* obj0, struct MainObj* obj1, s16* out_x, s16* out_y);
s32 func_8002BD58(struct MainObj*, struct MainObj*, s16*, s16*);
#endif

#ifdef MMX4_PC
// src/main/collision.c

s32 func_8002BB80(struct MainObj* obj0, struct MainObj* obj1)
{
    const struct Unk_unk68* box0;
    const struct Unk_unk68* box1;
    s32 flip0;
    s32 flip1;
    s32 sum;
    s32 t1;
    s32 t2;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 overlap;

    if (obj1->invincibility_timer != 0) {
        return 0;
    }
    box0 = (const struct Unk_unk68*)obj0->attack_box;
    if (box0 == NULL) {
        return 0;
    }
    box1 = (const struct Unk_unk68*)obj1->hurt_box;
    if (box1 == NULL) {
        return 0;
    }

    flip0 = (u8)obj0->unk15 & 0x40;
    flip1 = (u8)obj1->unk15 & 0x40;
    t1 = box0->unk2;
    t2 = box1->unk2;
    sum = t1 + t2;
    a2 = flip0 ? obj0->x_pos.i.hi - box0->unk0 : obj0->x_pos.i.hi + box0->unk0;
    a0 = flip1 ? obj1->x_pos.i.hi - box1->unk0 : obj1->x_pos.i.hi + box1->unk0;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }

    if (a0 < a2) {
        if (flip0) {
            overlap = flip1 ? a1 < t1 : a1 < sum;
        } else if (flip1) {
            return 0;
        } else {
            overlap = a1 < t2;
        }
    } else if (flip0) {
        if (!flip1) {
            return 0;
        }
        overlap = a1 < t2;
    } else {
        overlap = flip1 ? a1 < sum : a1 < t1;
    }
    if (overlap == 0) {
        return 0;
    }

    a2 = obj0->y_pos.i.hi + box0->unk1;
    a0 = obj1->y_pos.i.hi + box1->unk1;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }
    if (a0 < a2) {
        return a1 < box1->unk3;
    }
    return a1 < box0->unk3;
}
#else
INCLUDE_ASM("main/nonmatchings/collision", func_8002BB80);
#endif

#ifdef MMX4_PC
s32 func_8002BD58(struct MainObj* obj0, struct MainObj* obj1, s16* out_x,
    s16* out_y)
{
    const struct Unk_unk68* box0;
    const struct Unk_unk68* box1;
    s32 flip0;
    s32 flip1;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 sum;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 result;

    if (obj1->invincibility_timer != 0) {
        return 0;
    }
    box0 = (const struct Unk_unk68*)obj0->attack_box;
    if (box0 == NULL) {
        return 0;
    }
    box1 = (const struct Unk_unk68*)obj1->hurt_box;
    if (box1 == NULL) {
        return 0;
    }

    flip0 = (u8)obj0->unk15 & 0x40;
    flip1 = (u8)obj1->unk15 & 0x40;
    t1 = box0->unk2;
    t2 = box1->unk2;
    sum = t1 + t2;
    a2 = flip0 ? obj0->x_pos.i.hi - box0->unk0 : obj0->x_pos.i.hi + box0->unk0;
    a0 = flip1 ? obj1->x_pos.i.hi - box1->unk0 : obj1->x_pos.i.hi + box1->unk0;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }

    if (a0 < a2) {
        if (flip0 && flip1) {
            if (!(a1 < t1)) {
                return 0;
            }
            if (a2 < a0 || t1 < t2 + a1) {
                result = a0 + (t1 - a1) / 2;
            } else {
                result = a0 - (t2 >> 1);
            }
        } else if (flip0) {
            if (!(a1 < sum)) {
                return 0;
            }
            if (!(a0 < a2 - t1) && t2 < a1) {
                result = a0 + (t2 >> 1);
            } else if (!(t2 + a0 < a2) && t1 < a1) {
                result = a2 - (t1 >> 1);
            } else {
                t0 = a2 - t1;
                if (t0 < a0) {
                    result = a0 + a1 / 2;
                } else {
                    result = t0 + ((t2 + a0) - t0) / 2;
                }
            }
        } else if (flip1) {
            return 0;
        } else {
            if (!(a1 < t2)) {
                return 0;
            }
            if (a2 < a0 || t2 < a1 + t1) {
                result = a2 + (t2 - a1) / 2;
            } else {
                result = (t1 >> 1) + a2;
            }
        }
    } else if (flip0) {
        if (!flip1 || !(a1 < t2)) {
            return 0;
        }
        if (t2 < a1 + t1) {
            result = a2 - (t2 - a1) / 2;
        } else {
            result = a2 - (t1 >> 1);
        }
    } else if (flip1) {
        if (!(a1 < sum)) {
            return 0;
        }
        if (t1 < a1) {
            result = (t1 >> 1) + a2;
        } else if (t2 < a1) {
            result = a0 - (t2 >> 1);
        } else {
            result = a0 - (a0 - a2) / 2;
        }
    } else {
        if (!(a1 < t1)) {
            return 0;
        }
        result = a0 + (t1 - a1) / 2;
    }
    *out_x = (s16)result;

    t1 = box0->unk3;
    t2 = box1->unk3;
    a2 = obj0->y_pos.i.hi + box0->unk1;
    a0 = obj1->y_pos.i.hi + box1->unk1;
    a1 = a0 - a2;
    if (a1 < 0) {
        a1 = a2 - a0;
    }
    if (a0 < a2) {
        if (!(a1 < t2)) {
            return 0;
        }
        if (a2 < a0 || t2 < a1 + t1) {
            result = a2 + (t2 - a1) / 2;
        } else {
            result = (t1 >> 1) + a2;
        }
    } else {
        if (!(a1 < t1)) {
            return 0;
        }
        if (t1 < a1 + t2) {
            result = a0 + (t1 - a1) / 2;
        } else {
            result = a0 + (t2 >> 1);
        }
    }
    *out_y = (s16)result;
    return 1;
}
#else
INCLUDE_ASM("main/nonmatchings/collision", func_8002BD58);
#endif

s32 func_8002C160(struct CollisionObj* arg0, struct CollisionObj* arg1)
{
    s16 center0;
    s16 center1;
    s16 distance;
    struct Unk_unk68* bounds0;
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
    distance = (center0 - center1) > -1 ? center0 - center1 : center1 - center0;

    bounds0 = object0->collision_bounds;
    if (distance >= bounds0->unk2 + object1->collision_bounds->unk2) {
        return 0;
    }

    center0 = object0->y_pos.i.hi + bounds0->unk1;
    center1 = object1->y_pos.i.hi + object1->collision_bounds->unk1;
    distance = (center0 - center1) > -1 ? center0 - center1 : center1 - center0;
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

#ifdef MMX4_PC
void func_8002C36C(struct PlayerObj* arg0, struct PlayerObj* arg1, s32 slot)
{
    struct Unk_unk68* bounds0 = arg0->unk68;
    struct Unk_unk68* bounds1 = arg1->unk68;
    if (bounds0 == NULL || bounds1 == NULL) {
        if (slot == 0) {
            arg0->unk72 = 0;
            arg0->unk76 = 0;
        } else if (slot == 1) {
            arg0->unk73 = 0;
            arg0->unk77 = 0;
        } else if (slot == 2) {
            arg0->unk74 = 0;
            arg0->unk78 = 0;
        }
        return;
    }
    s16 x0 = arg0->x_pos.i.hi + bounds0->unk0;
    s16 y0 = arg0->y_pos.i.hi + bounds0->unk1;
    s16 x1 = arg1->x_pos.i.hi + bounds1->unk0;
    s16 y1 = arg1->y_pos.i.hi + bounds1->unk1;
    s16 dx = x0 >= x1 ? x0 - x1 : x1 - x0;
    s16 dy = y0 >= y1 ? y0 - y1 : y1 - y0;
    u8 flags = 0;

    if (dy == bounds0->unk3 + bounds1->unk3 && dx < bounds0->unk2 + bounds1->unk2) {
        flags |= y0 < y1 ? 4 : 8;
    }
    if (dx == bounds0->unk2 + bounds1->unk2 && dy < bounds0->unk3 + bounds1->unk3) {
        flags |= x0 < x1 ? 2 : 1;
        arg1->wall_climbable = arg0->unk75;
    }

    if (slot == 0)
        arg0->unk72 = flags;
    else if (slot == 1)
        arg0->unk73 = flags;
    else if (slot == 2)
        arg0->unk74 = flags;
    arg1->unk71 |= flags;

    if (slot == 0)
        arg0->unk76 = (flags & 0xB) != 0;
    else if (slot == 1)
        arg0->unk77 = (flags & 0xB) != 0;
    else if (slot == 2)
        arg0->unk78 = (flags & 0xB) != 0;
}
#else
INCLUDE_ASM("main/nonmatchings/collision", func_8002C36C);
#endif

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
