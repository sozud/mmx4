// hitbox and terrain collision
// 8002BB80..8002E420
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
extern struct EffectSpawnData D_800F460C[64];

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

INCLUDE_ASM("main/nonmatchings/collision", func_8002C26C);

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
    arg0->unk79 = 0;

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

void func_8002C760(struct PlayerObj* arg0)
{
    struct Unk_unk68* temp_v1 = arg0->unk68;
    u16 temp_a1 = arg0->x_pos.i.hi;
    u16 temp_v0 = temp_v1->unk0;

    D_8013B7E8 = temp_v1->unk0;
    D_8013B7EC = temp_v1->unk1;
    D_8013B7E0 = temp_v1->unk2;
    D_8013B7E4 = temp_v1->unk3;

    D_8013B7F0 = temp_a1;
    D_8013B7F4 = arg0->y_pos.i.hi;

    if (arg0->unk15 == 0) {
        D_8013B7F8 = temp_a1 + temp_v0;
    } else {
        D_8013B7F8 = temp_a1 - temp_v0;
    }
    D_8013B7FC = D_8013B7F4 + D_8013B7EC;
}

void func_8002C808(struct PlayerObj* arg0)
{
    arg0->unk70 = 0;
    arg0->unk79 = 0;
    if (arg0->unk68 != NULL) {
        func_8002C760(arg0);
        if (func_8002D5E4(arg0, D_8013B7F8 - D_8013B7E0 - 1)) {
            arg0->unk70 |= 2;
        }
        if (func_8002D5E4(arg0, D_8013B7F8 + D_8013B7E0)) {
            arg0->unk70 |= 1;
        }
        if (func_8002D32C(arg0, D_8013B7F4 + D_8013B7EC + D_8013B7E4, 1)) {
            arg0->unk70 |= 8;
        }
        if (func_8002D32C(arg0, D_8013B7F4 + D_8013B7EC - D_8013B7E4 - 1, 0)) {
            arg0->unk70 |= 4;
        }
    }
}

void func_8002C954(struct PlayerObj* arg0)
{
    if ((func_8002D25C(arg0) != 0) && (func_8002D490(arg0) != 0)) {
        func_8002C9E4(arg0);
    }
}

void func_8002C99C(struct PlayerObj* arg0)
{
    if ((func_8002D490(arg0) != 0) && (func_8002D25C(arg0) != 0)) {
        func_8002C9E4(arg0);
    }
}

void func_8002C9E4(struct PlayerObj* arg0)
{
    arg0->x_pos.u.lo = 0;
    arg0->y_pos.u.lo = 0;
    arg0->x_pos.u.hi += D_8013B800;
    arg0->y_pos.u.hi += D_8013B804;
}

void func_8002CA18(struct PlayerObj* arg0)
{
    s16 temp_v0;

    temp_v0 = D_8013B7F8 - D_8013B7E0;
    if ((func_8002CAF0(arg0, func_8002D7E4(arg0, temp_v0, D_8013B7FC)) == 0) && (func_8002CAF0(arg0, func_8002D7E4(arg0, temp_v0, D_8013B7FC - D_8013B7E4)) == 0)) {
        func_8002CAF0(arg0,
            func_8002D7E4(arg0, temp_v0, D_8013B7FC + D_8013B7E4 - 1));
    }
}

s32 func_8002CAF0(struct PlayerObj* arg0, u8 arg1)
{
    switch (arg1) {
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3E:
    case 0x3F:
        D_8013B7DC |= 2;
        D_8013B800 = 0x10 - arg0->unk6C;
        return -1;
    default:
        return 0;
    }
}

void func_8002CB58(struct PlayerObj* arg0)
{
    s16 temp_v0;

    temp_v0 = (D_8013B7F8 + D_8013B7E0) - 1;
    if ((func_8002CC34(arg0, func_8002D7E4(arg0, temp_v0, D_8013B7FC)) == 0) && (func_8002CC34(arg0, func_8002D7E4(arg0, temp_v0, D_8013B7FC - D_8013B7E4)) == 0)) {
        func_8002CC34(arg0,
            func_8002D7E4(arg0, temp_v0, D_8013B7FC + D_8013B7E4 - 1));
    }
}

s32 func_8002CC34(struct PlayerObj* arg0, u8 arg1)
{
    switch (arg1) {
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3E:
    case 0x3F:
        D_8013B7DC |= 1;
        D_8013B800 = ~arg0->unk6C;
        return -1;
    default:
        return 0;
    }
}

void func_8002CC98(struct PlayerObj* arg0)
{
    s16 temp_v0;

    temp_v0 = D_8013B7FC - D_8013B7E4;
    if ((func_8002CD70(arg0, func_8002D7E4(arg0, D_8013B7F8, temp_v0)) == 0) && (func_8002CD70(arg0, func_8002D7E4(arg0, D_8013B7F8 - D_8013B7E0, temp_v0)) == 0)) {
        func_8002CD70(arg0,
            func_8002D7E4(arg0, D_8013B7F8 + D_8013B7E0 - 1, temp_v0));
    }
}

s32 func_8002CD70(struct PlayerObj* arg0, u8 arg1)
{
    switch (arg1) {
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3E:
    case 0x3F:
        D_8013B7DC |= 4;
        D_8013B804 = 0x10 - arg0->unk6E;
        return -1;
        return 0; // permuter discovered this works!
    default:
#ifdef MMX4_PC
        return 0;
#endif
        // return 0; // this does not work
    }
}

void func_8002CDD4(struct PlayerObj* arg0)
{
    u8 temp_s3;
    u8 temp_s4;
    u8 temp_s5;
    u8 temp_v0_4;
    s32 var_s0;
    s16 temp_v0 = D_8013B7FC + D_8013B7E4;

    temp_s3 = func_8002D7E4(arg0, D_8013B7F8 - D_8013B7E0, temp_v0);
    temp_s4 = func_8002D7E4(arg0, D_8013B7F8 + D_8013B7E0 - 1, temp_v0);
    temp_s5 = func_8002D7E4(arg0, D_8013B7F8, temp_v0);

    if (func_8002CF98(arg0, temp_s5, D_8013B7F8, temp_v0) == 0) {
        if (arg0->unk67 == 0) {
            var_s0 = 0;
            if (temp_s3 > 0 && temp_s3 < 0x20) {
                var_s0 = 1;
            }
            if (temp_s4 > 0 && temp_s4 < 0x20) {
                var_s0 = 1;
            }

            temp_v0_4 = func_8002D7E4(arg0, D_8013B7F8, (temp_v0 + 0x10));
            if (temp_v0_4 > 0 && temp_v0_4 < 0x20) {
                var_s0 = 1;
            }

            if (var_s0) {
                arg0->y_pos.i.hi += 0x10;
                if (func_8002CF98(arg0, temp_v0_4, D_8013B7F8, temp_v0 + 0x10)) {
                    return;
                }
            }
        }

        if (func_8002D1F8(arg0, temp_s3, temp_v0) == 0) {
            func_8002D1F8(arg0, temp_s4, temp_v0);
        }
    }
}

s32 func_8002CF98(struct PlayerObj* entity, u8 arg1, s16 arg2, s16 arg3)
{
    s32 flag;
    s16 var_a0;
    u32 temp_v1;
    s16 var_v0;

    flag = 0;
    if (arg1 == 0x10) {
        flag = 1;
        entity->y_pos.i.hi -= 0x10;
        arg1 = func_8002D7E4(entity, arg2, arg3 - 0x10);
    }

    switch (arg1) {
    case 0x9 ... 0xC:
    case 0x19 ... 0x1C:
        var_a0 = arg2 & 0xF;
        temp_v1 = arg1 & 0xF;
        if (temp_v1 == 0xA) {
            var_a0 |= 0x10;
        }
        if (temp_v1 == 0xC) {
            var_a0 += 0x10;
        }
        if (temp_v1 >= 0xB) {
            var_v0 = var_a0 / 2;
        } else {
            var_v0 = 0xF - var_a0 / 2;
        }
        return func_8002D180(entity, arg3, var_v0, flag);
    case 0x1 ... 0x8:
    case 0x11 ... 0x18:
        var_a0 = arg2 & 0xF;
        temp_v1 = arg1 & 0xF;
        if (temp_v1 == 2) {
            var_a0 |= 0x10;
        }
        if (temp_v1 == 6) {
            var_a0 += 0x10;
        }
        if (temp_v1 == 3) {
            var_a0 += 0x20;
        }
        if (temp_v1 == 7) {
            var_a0 += 0x20;
        }
        if (temp_v1 == 4) {
            var_a0 += 0x30;
        }
        if (temp_v1 == 8) {
            var_a0 += 0x30;
        }
        if (temp_v1 >= 5) {
            var_v0 = var_a0 / 4;
        } else {
            var_v0 = 0xF - var_a0 / 4;
        }
        return func_8002D180(entity, arg3, var_v0, flag);
    case 0x21:
    case 0x22:
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3E:
    case 0x3F:
        D_8013B7DC |= 8;
        D_8013B804 = -entity->unk6E;
        return -1;
    case 0:
    default:
        return 0;
    }
}

s32 func_8002D180(struct PlayerObj* arg0, s16 arg1, s16 arg2, s32 arg3)
{
    D_8013B7D8 = 1;

    if (arg0->unk67 != 0) {
        if (arg3 == 0) {
            if ((arg1 & 0xF) < arg2) {
                return 0;
            }
        }
    }

    arg0->unk70 = 8;
    arg0->y_pos.i.lo = 0;
    arg0->y_pos.i.hi -= arg1 - (arg2 + (arg1 & ~0xF));
    return -1;
}

s32 func_8002D1F8(struct PlayerObj* arg0, u8 arg1, s32 arg2)
{
    switch (arg1) {
    case 0x21:
    case 0x22:
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3C:
    case 0x3E:
    case 0x3F:
        D_8013B7DC |= 8;
        D_8013B804 = -arg0->unk6E;
        return -1;
    default:
        return 0;
    }
}

s32 func_8002D25C(struct PlayerObj* arg0)
{
    s16 arg1;
    s32 arg2;

    if (D_8013B7DC & 4) {
        arg2 = 0;
        arg1 = D_8013B7F4 + D_8013B804 + D_8013B7EC - D_8013B7E4;
    } else {
        arg2 = 1;
        arg1 = D_8013B7F4 + D_8013B804 + D_8013B7EC + D_8013B7E4 - 1;
    }

    if (func_8002D32C(arg0, arg1, arg2) == 0) {
        arg0->y_pos.i.lo = 0;
        arg0->y_pos.i.hi += D_8013B804;
        return 0;
    } else {
        return -1;
    }
}

s32 func_8002D32C(struct PlayerObj* arg0, s16 arg1, s32 arg2)
{
    if (func_8002D41C(arg0, func_8002D724(arg0, D_8013B7F8, arg1), arg2) == 0) {
        if (func_8002D41C(arg0, func_8002D724(arg0, D_8013B7F8 - D_8013B7E0, arg1), arg2) == 0) {
            if (func_8002D41C(arg0, func_8002D724(arg0, D_8013B7F8 + D_8013B7E0 - 1, arg1), arg2) == 0) {
                return 0;
            }
        }
    }
    return -1;
}

s32 func_8002D41C(struct PlayerObj* arg0, s32 arg1, s32 arg2)
{
    if (arg2 == 0) {
        switch (arg1 & 0xFF) {
        case 0x3E:
        case 0x3F:
            arg0->unk79 = 1;
            return -1;
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3C:
            return -1;
        default:
            return 0;
        }
    } else {
        switch (arg1 & 0xFF) {
        case 0x3E:
        case 0x3F:
            arg0->unk79 = 1;
            return -1;
        case 0x21:
        case 0x22:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3C:
            return -1;
        default:
            return 0;
        }
    }
}

s32 func_8002D490(struct PlayerObj* arg0)
{
    s16 var_v0_2;

    if (D_8013B7DC & 1) {
        if (arg0->unk15 != 0) {
            var_v0_2 = (D_8013B7E0 + (D_8013B7E8 + (D_8013B7F0 + D_8013B800))) - 1;
        } else {
            var_v0_2 = (D_8013B7E0 + ((D_8013B7F0 + D_8013B800) - D_8013B7E8)) - 1;
        }
    } else {
        if (arg0->unk15 != 0) {
            var_v0_2 = (D_8013B7E8 + (D_8013B7F0 + D_8013B800)) - D_8013B7E0;
        } else {
            var_v0_2 = ((D_8013B7F0 + D_8013B800) - D_8013B7E8) - D_8013B7E0;
        }
    }

    if (func_8002D5E4(arg0, var_v0_2) != 0) {
        return -1;
    }
    arg0->x_pos.i.lo = 0;
    arg0->x_pos.i.hi += D_8013B800;
    return 0;
}

s32 func_8002D5E4(struct PlayerObj* arg0, s16 arg1)
{
    if (func_8002D6BC(arg0, func_8002D724(arg0, arg1, D_8013B7FC - D_8013B7E4)) == 0) {
        if (func_8002D6BC(arg0, func_8002D724(arg0, arg1, D_8013B7FC)) == 0) {
            if (func_8002D6BC(arg0, func_8002D724(arg0, arg1, D_8013B7FC + D_8013B7E4 - 1)) == 0) {
                return 0;
            }
        }
    }
    return -1;
}

s32 func_8002D6BC(struct PlayerObj* arg0, u8 arg1)
{
    switch (arg1) {
    case 0x38:
    case 0x3A:
    case 0x3C:
        arg0->unk4A = 1;
        return -1;
    case 0x39:
        arg0->unk4A = 0;
        return -1;
    case 0x3E:
    case 0x3F:
        arg0->unk4A = 0;
        arg0->unk79 = 1;
        return -1;
    default:
        return 0;
    }
}

INCLUDE_ASM("main/nonmatchings/collision", func_8002D724);

INCLUDE_ASM("main/nonmatchings/collision", func_8002D7E4);

u8 func_8002D8B8(struct PlayerObj* arg0)
{
    struct Unk_unk68* temp_v1 = arg0->unk68;
    return func_8002D724(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi + temp_v1->unk1 - temp_v1->unk3);
}

u8 func_8002D900(struct PlayerObj* arg0)
{
    s16 x = arg0->x_pos.i.hi;
#ifdef MMX4_PC
    s16 y = arg0->y_pos.i.hi - 1;

    if (arg0->unk68 != NULL) {
        y += arg0->unk68->unk1 + arg0->unk68->unk3;
    }
#else
    s16 y = arg0->y_pos.i.hi + arg0->unk68->unk1 + arg0->unk68->unk3 - 1;
#endif

    return func_8002D724(arg0, x, y);
}

u8 func_8002D94C(struct PlayerObj* arg0)
{
    struct Unk_unk68* temp_v1 = arg0->unk68;
    return func_8002D724(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi + temp_v1->unk1 + temp_v1->unk3);
}

#ifdef VERSION_JP
u8 func_8002D994(struct PlayerObj* arg0)
{
    return func_8002D724(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi);
}
#else
u8 func_8002D994(struct PlayerObj* arg0)
{
    return func_8002D724(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi);
}
#endif

INCLUDE_ASM("main/nonmatchings/collision", func_8002D9BC);

INCLUDE_ASM("main/nonmatchings/collision", func_8002DD04);

INCLUDE_ASM("main/nonmatchings/collision", func_8002DE30);

INCLUDE_ASM("main/nonmatchings/collision", func_8002DF7C);

void func_8002E184(struct PlayerObj* arg0)
{
    if (arg0->unk68 != NULL) {
        func_8002E294(arg0, &g_Player);
        if (arg0->unk76 > 0) {
            func_8002E380(MOVING_OBJECT(arg0), MOVING_OBJECT(&g_Player), arg0->unk72);
        }
        func_8002C36C(arg0, &g_Player, 0);
        if (g_Entity.active != 0) {
            func_8002E294(arg0, &g_Entity);
            if (arg0->unk77 > 0) {
                func_8002E380(MOVING_OBJECT(arg0), MOVING_OBJECT(&g_Entity), arg0->unk73);
            }
            func_8002C36C(arg0, &g_Entity, 1);
        }
        if (qux_object.active != 0) {
            func_8002E294(arg0, (struct PlayerObj*)&qux_object);
            if (arg0->unk78 > 0) {
                func_8002E380(MOVING_OBJECT(arg0), MOVING_OBJECT(&qux_object), arg0->unk74);
            }
            func_8002C36C(arg0, (struct PlayerObj*)&qux_object, 2);
        }
    }
}

INCLUDE_ASM("main/nonmatchings/collision", func_8002E294);

void func_8002E380(struct MovingObj* arg0, struct MovingObj* arg1, u8 arg2)
{
    s32 delta;
    s32 direction;
    u16 target_hi;
    u16 target_prev_hi;
    u16 target_prev_hi_y;

    delta = arg0->x_pos.val - arg0->unk18.val;
    if (delta != 0) {
        direction = 1;
        if (delta > 0) {
            direction = 2;
        }
        if (!(direction & arg2)) {
            target_hi = arg1->x_pos.u.hi;
            target_prev_hi = arg1->unk18.u.hi;
            arg1->x_pos.i.hi = (target_hi - target_prev_hi) + (arg0->x_pos.u.hi - (arg0->unk18.u.hi - target_prev_hi));
        }
    }
    delta = arg0->y_pos.val - arg0->unk1C.val;
    if (delta > 0) {
        target_hi = arg1->y_pos.u.hi;
        target_prev_hi_y = arg1->unk1C.u.hi;
        arg1->y_pos.i.hi = (target_hi - target_prev_hi_y) + (arg0->y_pos.u.hi - (arg0->unk1C.u.hi - target_prev_hi_y));
    }
}

struct EffectSpawnData D_800F460C[64] = {
    { 0x03, 0x00, 0x01, 0x00, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x03, 0x00, 0x01, 0x00, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x03, 0x00, 0x01, 0x01, 0x0C },
    { 0x03, 0x00, 0x01, 0x00, 0x0C },
    { 0x03, 0x00, 0x01, 0x01, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x03, 0x00, 0x01, 0x00, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x03, 0x00, 0x00, 0x00, 0x0C },
    { 0x04, 0x00, 0x01, 0x01, 0x0C },
    { 0x03, 0x00, 0x01, 0x01, 0x0C },
    { 0x04, 0x00, 0x01, 0x00, 0x0C },
    { 0x04, 0x00, 0x00, 0x00, 0x0C },
    { 0x04, 0x00, 0x00, 0x00, 0x0C },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x07, 0x01, 0x00, 0x00, 0x00 },
    { 0x06, 0x01, 0x00, 0x00, 0x00 },
    { 0x07, 0x01, 0x00, 0x00, 0x00 },
    { 0x07, 0x01, 0x00, 0x00, 0x00 },
    { 0x07, 0x01, 0x00, 0x00, 0x00 },
    { 0x06, 0x01, 0x00, 0x00, 0x00 },
    { 0x07, 0x01, 0x00, 0x00, 0x00 },
    { 0x07, 0x01, 0x00, 0x00, 0x00 },
    { 0x0A, 0x01, 0x00, 0x00, 0x00 },
    { 0x0B, 0x01, 0x00, 0x00, 0x00 },
    { 0x07, 0x01, 0x00, 0x00, 0x00 },
    { 0x07, 0x01, 0x00, 0x00, 0x00 },
    { 0x07, 0x01, 0x01, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x0C, 0x02, 0x01, 0x01, 0x0C },
    { 0x0C, 0x02, 0x01, 0x01, 0x0C },
    { 0x0C, 0x04, 0x00, 0x00, 0x00 },
    { 0x0C, 0x02, 0x01, 0x00, 0x09 },
    { 0x0C, 0x02, 0x01, 0x00, 0x09 },
    { 0x0C, 0x03, 0x00, 0x00, 0x08 },
    { 0x0C, 0x03, 0x00, 0x00, 0x08 },
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
};
