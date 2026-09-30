// 8002D9BC..8002E420
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

// hitboxes_overlap

s32 func_8002C160(struct CollisionObj* arg0, struct CollisionObj* arg1);

void func_8002C26C(struct CollisionObj* arg0, struct CollisionObj* arg1);

void func_8002C2EC(struct CollisionObj* arg0, struct CollisionObj* arg1);

// megaman falls through floor in intro stage if nopped out
// asm(".rept 81 ; nop ; .endr");
void CollisionRelated(struct PlayerObj* arg0);

void func_8002C760(struct PlayerObj* arg0);

void func_8002C808(struct PlayerObj* arg0);

void func_8002C954(struct PlayerObj* arg0);

void func_8002C99C(struct PlayerObj* arg0);

void func_8002C9E4(struct PlayerObj* arg0);

void func_8002CA18(struct PlayerObj* arg0);

s32 func_8002CAF0(struct PlayerObj* arg0, u8 arg1);

void func_8002CB58(struct PlayerObj* arg0);

s32 func_8002CC34(struct PlayerObj* arg0, u8 arg1);

void func_8002CC98(struct PlayerObj* arg0);

s32 func_8002CD70(struct PlayerObj* arg0, u8 arg1);

void func_8002CDD4(struct PlayerObj* arg0);

s32 func_8002CF98(struct PlayerObj* entity, u8 arg1, s16 arg2, s16 arg3);

s32 func_8002D180(struct PlayerObj* arg0, s16 arg1, s16 arg2, s32 arg3);

s32 func_8002D1F8(struct PlayerObj* arg0, u8 arg1, s32 arg2);

s32 func_8002D25C(struct PlayerObj* arg0);

s32 func_8002D32C(struct PlayerObj* arg0, s16 arg1, s32 arg2);

s32 func_8002D41C(struct PlayerObj* arg0, s32 arg1, s32 arg2);

s32 func_8002D490(struct PlayerObj* arg0);

s32 func_8002D5E4(struct PlayerObj* arg0, s16 arg1);

s32 func_8002D6BC(struct PlayerObj* arg0, u8 arg1);

// get_tile_attribute

u8 func_8002D8B8(struct PlayerObj* arg0);

u8 func_8002D900(struct PlayerObj* arg0);

u8 func_8002D94C(struct PlayerObj* arg0);

u8 func_8002D994(struct PlayerObj* arg0);

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

// damage_player_on_contact
INCLUDE_ASM("main/nonmatchings/1E1BC", func_8002D9BC);
// check_weapon_hits
INCLUDE_ASM("main/nonmatchings/1E1BC", func_8002DD04);

INCLUDE_ASM("main/nonmatchings/1E1BC", func_8002DE30);

INCLUDE_ASM("main/nonmatchings/1E1BC", func_8002DF7C);
void collide_with_players(struct PlayerObj* arg0)
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

INCLUDE_ASM("main/nonmatchings/1E1BC", func_8002E294);
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
