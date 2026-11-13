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

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8002C36C(struct PlayerObj* arg0, struct PlayerObj* arg1, s32 slot);
s32 func_8002BB80(struct MainObj* obj0, struct MainObj* obj1);
s32 func_8002BD58(struct MainObj* obj0, struct MainObj* obj1, s16* out_x, s16* out_y);
s32 func_8002BD58(struct MainObj*, struct MainObj*, s16*, s16*);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/collision", func_8002BB80);
#else
#define HITBOX(p) ((const struct Unk_unk68*)(p))
s32 func_8002BB80(struct MainObj* obj0, struct MainObj* obj1)
{
    const struct Unk_unk68* box0;
    const struct Unk_unk68* box1;
    s32 w0;
    s32 w1;
    s32 sum;
    s32 x0;
    s32 x1;
    s32 dist;
    s32 overlap;

    if (obj1->invincibility_timer != 0) {
        return 0;
    }
    box0 = HITBOX(obj0->attack_box);
    if (box0 == NULL) {
        return 0;
    }
    box1 = HITBOX(obj1->hurt_box);
    if (box1 == NULL) {
        return 0;
    }
    sum = box0->unk2 + box1->unk2;
    w0 = box0->unk2;
    w1 = box1->unk2;
    if (obj0->unk15 & PLAYER_FACING_RIGHT) {
        x0 = obj0->x_pos.i.hi - HITBOX(obj0->attack_box)->unk0;
    } else {
        x0 = obj0->x_pos.i.hi + HITBOX(obj0->attack_box)->unk0;
    }
    if (obj1->unk15 & PLAYER_FACING_RIGHT) {
        x1 = obj1->x_pos.i.hi - HITBOX(obj1->hurt_box)->unk0;
    } else {
        x1 = obj1->x_pos.i.hi + HITBOX(obj1->hurt_box)->unk0;
    }
    dist = ABS(x1, x0);
    if (x1 < x0) {
        if (obj0->unk15 & PLAYER_FACING_RIGHT) {
            if (obj1->unk15 & PLAYER_FACING_RIGHT) {
                overlap = dist < w0;
            } else {
                overlap = dist < sum;
            }
        } else if (obj1->unk15 & PLAYER_FACING_RIGHT) {
            return 0;
        } else {
            overlap = dist < w1;
        }
    } else if (obj0->unk15 & PLAYER_FACING_RIGHT) {
        if (!(obj1->unk15 & PLAYER_FACING_RIGHT)) {
            return 0;
        }
        overlap = dist < w1;
    } else if (obj1->unk15 & PLAYER_FACING_RIGHT) {
        overlap = dist < sum;
    } else {
        overlap = dist < w0;
    }
    if (overlap == 0) {
        return 0;
    }

    x0 = obj0->y_pos.i.hi + HITBOX(obj0->attack_box)->unk1;
    x1 = obj1->y_pos.i.hi + HITBOX(obj1->hurt_box)->unk1;
    dist = ABS(x1, x0);
    if (x1 < x0) {
        if (dist < HITBOX(obj1->hurt_box)->unk3) {
            return 1;
        }
    } else if (dist < HITBOX(obj0->attack_box)->unk3) {
        return 1;
    }
    return 0;
}
#endif

s32 func_8002BD58(struct MainObj* arg0, struct MainObj* arg1, s16* arg2, s16* arg3)
{
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0;
    u16 temp_t0;
    u8 temp_t1;
    u8 temp_t2;

    if (arg1->invincibility_timer != 0 || arg0->attack_box == 0 || arg1->hurt_box == 0) {
        return 0;
    }

    temp_t0 = ((const struct Unk_unk68*)arg0->attack_box)->unk2 + ((const struct Unk_unk68*)arg1->hurt_box)->unk2;
    temp_t1 = ((const struct Unk_unk68*)arg0->attack_box)->unk2;
    temp_t2 = ((const struct Unk_unk68*)arg1->hurt_box)->unk2;
    if (arg0->unk15 & 0x40) {
        var_a2 = arg0->x_pos.i.hi - ((const struct Unk_unk68*)arg0->attack_box)->unk0;
    } else {
        var_a2 = arg0->x_pos.i.hi + ((const struct Unk_unk68*)arg0->attack_box)->unk0;
    }
    if (arg1->unk15 & 0x40) {
        var_a0 = arg1->x_pos.i.hi - ((const struct Unk_unk68*)arg1->hurt_box)->unk0;
    } else {
        var_a0 = arg1->x_pos.i.hi + ((const struct Unk_unk68*)arg1->hurt_box)->unk0;
    }
    var_a1 = var_a0 - var_a2;
    if (var_a1 < 0) {
        var_a1 = var_a2 - var_a0;
    }
    if (var_a0 < var_a2) {
        if (arg0->unk15 & 0x40) {
            if (arg1->unk15 & 0x40) {
                if (var_a1 < temp_t1) {
                    if (var_a2 >= var_a0 && temp_t1 >= (temp_t2 + var_a1)) {
                        *arg2 = var_a0 - (temp_t2 / 2);
                    } else {
                        *arg2 = var_a0 + ((temp_t1 - var_a1) / 2);
                    }
                    goto dummy;
                }
                return 0;
            }
            if (var_a1 < temp_t0) {
                if (var_a0 >= (var_a2 - temp_t1)) {
                    if (temp_t2 < var_a1) {
                        *arg2 = var_a0 + (temp_t2 / 2);
                        goto dummy;
                    }
                }

                if (((temp_t2 + var_a0) >= var_a2) && temp_t1 < var_a1) {
                    *arg2 = var_a2 - (temp_t1 / 2);
                } else {
                    if ((var_a2 - temp_t1) < var_a0) {
                        *arg2 = var_a0 + (var_a1 / 2);
                    } else {
                        *arg2 = (var_a2 - temp_t1) + ((temp_t2 + var_a0 - (var_a2 - temp_t1)) / 2);
                    }
                }
                goto dummy;
            }
            return 0;
        }

        if (!(arg1->unk15 & 0x40)) {
            if (var_a1 < temp_t2) {
                if (var_a2 >= var_a0 && temp_t2 >= (var_a1 + temp_t1)) {
                    *arg2 = var_a2 + (temp_t1 / 2);
                } else {
                    *arg2 = var_a2 + ((temp_t2 - var_a1) / 2);
                }
                goto dummy;
            }
        }
        return 0;
    }

    if (arg0->unk15 & 0x40) {
        if (arg1->unk15 & 0x40) {
            if (var_a1 < temp_t2) {
                if (temp_t2 >= (var_a1 + temp_t1)) {
                    *arg2 = var_a2 - (temp_t1 / 2);
                } else {
                    *arg2 = var_a2 - ((temp_t2 - var_a1) / 2);
                }
                goto dummy;
            }
        }
        return 0;
    }

    if (arg1->unk15 & 0x40) {
        if (var_a1 < temp_t0) {
            if (temp_t1 < var_a1) {
                *arg2 = var_a2 + (temp_t1 / 2);
            } else {
                if (temp_t2 < var_a1) {
                    *arg2 = var_a0 - (temp_t2 / 2);
                } else {
                    *arg2 = var_a0 - ((var_a0 - var_a2) / 2);
                }
            }
            goto dummy;
        }
        return 0;
    }

    if (var_a1 >= temp_t1) {
        return 0;
    }

    if (temp_t1 >= (var_a1 + temp_t2)) {
        *arg2 = var_a0 + (temp_t2 / 2);
    }

    *arg2 = var_a0 + ((temp_t1 - var_a1) / 2);

dummy:
    temp_t1 = ((const struct Unk_unk68*)arg0->attack_box)->unk3;
    temp_t2 = ((const struct Unk_unk68*)arg1->hurt_box)->unk3;
    var_a2 = arg0->y_pos.i.hi + ((const struct Unk_unk68*)arg0->attack_box)->unk1;
    var_a0 = arg1->y_pos.i.hi + ((const struct Unk_unk68*)arg1->hurt_box)->unk1;
    var_a1 = var_a0 - var_a2;
    if (var_a1 < 0) {
        var_a1 = var_a2 - var_a0;
    }

    if (var_a0 < var_a2) {
        if (var_a1 >= temp_t2) {
            return 0;
        }

        if (var_a2 >= var_a0 && temp_t2 >= (var_a1 + temp_t1)) {
            *arg3 = var_a2 + (temp_t1 / 2);
        } else {
            *arg3 = var_a2 + ((temp_t2 - var_a1) / 2);
        }
    } else {
        if (var_a1 >= temp_t1) {
            return 0;
        }

        if (temp_t1 >= (var_a1 + temp_t2)) {
            *arg3 = var_a0 + (temp_t2 / 2);
        } else {
            *arg3 = var_a0 + ((temp_t1 - var_a1) / 2);
        }
    }

    return 1;
}

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
    center0 = arg0->y_pos.i.hi + bounds0->unk1;
    bounds1 = arg1->collision_bounds;
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

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8002C36C(struct PlayerObj* arg0, struct PlayerObj* arg1, s32 slot)
{
    struct Unk_unk68* bounds0 = arg0->unk68;
    struct Unk_unk68* bounds1 = arg1->unk68;
    s16 x0, y0, x1, y1, dx, dy;
    u8 flags;

#ifndef MMX4_SATURN
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
#endif
    x0 = arg0->x_pos.i.hi + bounds0->unk0;
    y0 = arg0->y_pos.i.hi + bounds0->unk1;
    x1 = arg1->x_pos.i.hi + bounds1->unk0;
    y1 = arg1->y_pos.i.hi + bounds1->unk1;
    dx = x0 >= x1 ? x0 - x1 : x1 - x0;
    dy = y0 >= y1 ? y0 - y1 : y1 - y0;
    flags = 0;

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
void func_8002C36C(struct PlayerObj* arg0, struct PlayerObj* arg1, s32 slot)
{
    s16 x0, x1, y0, y1;
    s16 d;
    s32 flags;
    struct PlayerObj* self;
    struct PlayerObj* other;

    self = arg0;
    flags = 0;
    other = arg1;
    x0 = self->x_pos.i.hi + self->unk68->unk0;
    y0 = self->y_pos.i.hi + self->unk68->unk1;
    x1 = other->x_pos.i.hi + other->unk68->unk0;
    y1 = other->y_pos.i.hi + other->unk68->unk1;

    d = ABS(y0, y1);
    if (d == (s16)(self->unk68->unk3 + other->unk68->unk3)) {
        d = ABS(x0, x1);
        if (d < (s16)(self->unk68->unk2 + other->unk68->unk2)) {
            flags |= y0 < y1 ? 4 : 8;
        }
    }
    d = ABS(x0, x1);
    if (d == (s16)(self->unk68->unk2 + other->unk68->unk2)) {
        d = ABS(y0, y1);
        if (d < (s16)(self->unk68->unk3 + other->unk68->unk3)) {
            flags |= x0 < x1 ? 2 : 1;
            other->wall_climbable = self->unk75;
        }
    }

    switch ((u32)slot) {
    case 0:
        self->unk72 = flags;
        break;
    case 1:
        self->unk73 = flags;
        break;
    case 2:
        self->unk74 = flags;
        break;
    }
    other->unk71 |= flags;

    if (flags & 0xB) {
        switch ((u32)slot) {
        case 0:
            self->unk76 = 1;
            break;
        case 1:
            self->unk77 = 1;
            break;
        case 2:
            self->unk78 = 1;
            break;
        }
    } else {
        switch ((u32)slot) {
        case 0:
            self->unk76 = 0;
            break;
        case 1:
            self->unk77 = 0;
            break;
        case 2:
            self->unk78 = 0;
            break;
        }
    }
}
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
