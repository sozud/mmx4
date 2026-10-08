// 8002D9BC..8002E420
#include "common.h"

void func_8002E380(struct MovingObj* arg0, struct MovingObj* arg1, u8 arg2);

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
ret_u8 func_8002D9BC(void* object)
{
    struct PlayerObj* player;
    struct RideArmorObj* ride;
    struct ShotObj* shot;
    s8 ride_hp;
    s8 damage_type;
    s8 remaining_hp;
    s8 hp_flags;
    u32 damage;
    u8 contact_damage;
    u8 energy;
    shot = object;
    player = &g_Player;
    if (g_Player.spike_immune != 0) {
        return 0;
    }
    if (g_Player.ride_state < 0) {
        ride = &qux_object;
        if (ride->unk5C & 0x80) {
            return 0;
        }
        if (((u8)ride->unk85) != 0) {
            return 0;
        }
        if (func_8002BB80((struct MainObj*)shot, (struct MainObj*)ride) == 0) {
            return 0;
        }
        ride->unk63 = 0;
        ride->unk86 = 0;
        ride_hp = shot->unk60;
        ride->unk63 = ride_hp >= 5 ? 2 : 1;
        ride_hp = ride->unk5C - shot->unk60;
        ride->unk5C = ride_hp;
        if (ride_hp > 0) {
            ride_hp |= 0x80;
        } else {
            ride_hp = -0x80;
        }
        ride->unk5C = ride_hp;
        if (ride->x_pos.i.hi >= shot->x_pos.i.hi) {
            ride->unk84 = 0;
        } else {
            ride->unk84 = 0x40;
        }
        return 1;
    }
    if (player->hp & 0x80) {
        return 0;
    }
    if (player->hurt_phase != 0) {
        return 0;
    }
    if (func_8002BB80((struct MainObj*)shot, (struct MainObj*)player) == 0) {
        return 0;
    }
    player->hurt_type = (s8)shot->unk62;
    player->stun_timer = 0;
    damage_type = (s8)shot->unk62;
    switch (damage_type) {
    case 0:
        if ((player->unk2 == 0) && (((u8)player->armor_parts) & 2)) {
            player->hurt_type = 4;
        } else if (shot->unk60 < 5) {
            player->hurt_type = 1;
        } else {
            player->hurt_type = 2;
        }
        break;

    case 3:
        player->stun_timer = 1;
        break;
    }

    contact_damage = (u8)shot->unk60;
    damage_type = (s8)contact_damage;
    if (damage_type != 0) {
        if (((u8)player->armor_parts) & 2) {
            if (damage_type < 3) {
                damage = 1;
            } else {
                damage = ((u32)((damage_type / 3) << 0x18)) >> 0x17;
            }
            remaining_hp = ((u8)player->hp) - damage;
        } else {
            remaining_hp = ((u8)player->hp) - contact_damage;
        }
        player->hp = remaining_hp;
    }
    if (player->hp > 0) {
        hp_flags = player->hp | 0x80;
    } else {
        hp_flags = -0x80;
    }
    player->hp = hp_flags;
    if (((s8)shot->unk62) != 3) {
        if (player->x_pos.i.hi >= shot->x_pos.i.hi) {
            player->hit_facing = 0;
        } else {
            player->hit_facing = 0x40;
        }
    }
    if (player->unk2 == 0) {
        if (!(((u8)player->armor_parts) & 2)) {
            return 1;
        }
    } else if (!(((u8)player->boss_flags) & 0x20)) {
        return 1;
    }
    if (player->weapon_energy[0] != 0x30) {
        energy = ((s8)player->weapon_energy[0]) + 6;
        player->weapon_energy[0] = energy;
        if (((s8)energy) >= 0x31) {
            player->weapon_energy[0] = 0x30;
        }
    }
    return 1;
}
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
        direction = delta > 0 ? 2 : 1;
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
