// ShotObj, shot_object_update_funcs[12]
// 8009B7F8..8009BD28
#include "common.h"
#include "main/shots/shot_12_ice_core_shot.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/collision_bounds.h"

// ice_core_shot_state_funcs
extern void (*ice_core_shot_state_funcs[])(struct ShotObj*);

void ice_core_spray_fly(struct ShotObj*);
void ice_core_spray_despawn(struct ShotObj*);

void ice_core_shard_hold(struct ShotObj*);

void ice_core_shard_fall(struct ShotObj*);

void ice_core_shard_despawn(struct ShotObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

extern u8 ice_core_shard_hit_box[4];
extern u8 ice_core_shard_terrain_box[4];
extern u8 ice_core_spray_hit_box[4];

void ice_core_shot_update(struct ShotObj* self)
{
    ice_core_shot_state_funcs[self->state](self);
    if (self->state >= 3) {
        CollisionRelated(self);
    }
}

// ice_core_spray_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009B85C(struct ShotObj* arg0);
void func_8009BA6C(struct ShotObj* arg0);
extern u8 ice_core_spray_hit_box[4];
extern u8 ice_core_shard_hit_box[4];
extern u8 ice_core_shard_terrain_box[4];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009B85C(struct ShotObj* arg0)
{
    const u8* offsets = (const u8*)&ice_core_shard_data + 0x14 + arg0->unk2 * 2;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk42 &= 0x7FFF;
    set_velocity_from_angle(MOVING_OBJECT(arg0), (arg0->unk2 * 4) & 0xFC);
    arg0->y_vel.val *= 6;
    arg0->y_pos.i.hi = (u16)arg0->y_pos.i.hi + (s8)offsets[1];
    if (arg0->unk15 == 0) {
        arg0->x_vel.val *= 6;
        arg0->x_pos.i.hi = (u16)arg0->x_pos.i.hi + (s8)offsets[0];
    } else {
        arg0->x_vel.val = -(arg0->x_vel.val * 6);
        arg0->x_pos.i.hi = (u16)arg0->x_pos.i.hi - (s8)offsets[0];
    }
    arg0->unk54 = ice_core_spray_hit_box;
    arg0->unk50.data = ice_core_spray_hit_box;
    arg0->unk5C = 6;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk60 = 3;
    set_animation(arg0, arg0->unk2 + 0x11);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_12_ice_core_shot", func_8009B85C);
#endif

void ice_core_spray_fly(struct ShotObj* self)
{
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (*(s16*)((void*)self->unk7C) == 2) {
        self->state = 2;
    }
    if (func_8002BB80(self, &g_Player) != 0) {
        self->state = 2;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
        return;
    }
    self->state = 2;
}

void ice_core_spray_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

// ice_core_shard_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009BA6C(struct ShotObj* arg0)
{
    arg0->state = 4;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk68 = (struct Unk_unk68*)ice_core_shard_terrain_box;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->unk54 = ice_core_shard_hit_box;
    arg0->unk50.data = ice_core_shard_hit_box;
    arg0->unk16 = 0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk60 = 3;
    arg0->unk42 &= 0x7FFF;
    set_animation(arg0, 0x1D);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_12_ice_core_shot", func_8009BA6C);
#endif

void ice_core_shard_hold(struct ShotObj* self)
{
    u16* flags;
    u16 value;

    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0 || func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(&g_Player)) != 0) {
        flags = (u16*)self->unk7C;
        *flags ^= ice_core_shard_data.masks[self->unk2];
        func_8001540C(5, SATURN_SOUND(2, 0x24), NULL);
        spawn_debris(4, ice_core_shard_debris, self);
        self->state = 6;
        return;
    }

    value = *(u16*)self->unk7C;
    if (value == 0) {
        spawn_debris(4, ice_core_shard_debris, self);
        self->state = 6;
    } else if (!(value & ice_core_shard_data.masks[self->unk2])) {
        set_animation(self, 0x1E);
        self->y_vel.val = 0;
        self->unk2C = FIXED(0.15625);
        self->state = 5;
    }
    update_on_screen(BASE_OBJECT(self), 0x80, 0x80);
}

void ice_core_shard_fall(struct ShotObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    func_8002D9BC(self);

    if (self->unk70 & 8) {
        func_8001540C(5, SATURN_SOUND(2, 0x24), NULL);
        spawn_debris(4, ice_core_shard_debris, self);
        self->state = 6;
    }
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        func_8001540C(5, SATURN_SOUND(2, 0x24), NULL);
        spawn_debris(4, ice_core_shard_debris, self);
        self->state = 6;
    }
    if (func_8002BB80(self, &g_Player) != 0) {
        func_8001540C(5, SATURN_SOUND(2, 0x24), NULL);
        spawn_debris(4, ice_core_shard_debris, self);
        self->state = 6;
    }
    update_on_screen(BASE_OBJECT(self), 0x80, 0x80);
}

void ice_core_shard_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

u8 ice_core_spray_hit_box[4] = { 0xFA, 0xF8, 0x0C, 0x0D };

u8 ice_core_shard_hit_box[4] = { 0xF7, 0xF0, 0x10, 0x25 };

u8 ice_core_shard_terrain_box[4] = { 0xFF, 0x04, 0x09, 0x14 };

struct Shot12CollisionData ice_core_shard_data = {
    { 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200 },
#ifdef MMX4_WIN32
    { 0 },
#endif
    0x16,
    { 0xFF, 0x0E, 0xEF, 0xFE, 0xE7, 0xF1, 0xF1, 0xEB, 0x01, 0xF2, 0x0F, 0xFF, 0x17, 0x0D, 0x11 },
};

u8 ice_core_shard_debris[4] = { 0x1F, 0x20, 0x1F, 0x20 };

void (*ice_core_shot_state_funcs[])(struct ShotObj*) = {
    func_8009B85C,
    ice_core_spray_fly,
    ice_core_spray_despawn,
    func_8009BA6C,
    ice_core_shard_hold,
    ice_core_shard_fall,
    ice_core_shard_despawn,
};
