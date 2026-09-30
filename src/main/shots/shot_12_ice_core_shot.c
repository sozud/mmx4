// ShotObj, shot_object_update_funcs[12]
// 8009B7F8..8009BD28
#include "common.h"

void ice_core_shot_update(struct ShotObj* self)
{
    ice_core_shot_state_funcs[self->state](self);
    if (self->state >= 3) {
        CollisionRelated(self);
    }
}

// ice_core_spray_init
INCLUDE_ASM("main/nonmatchings/shots/shot_12_ice_core_shot", func_8009B85C);

void ice_core_spray_fly(struct ShotObj* self)
{
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (*(s16*)&self->unk7C->active == 2) {
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
INCLUDE_ASM("main/nonmatchings/shots/shot_12_ice_core_shot", func_8009BA6C);

void ice_core_shard_hold(struct ShotObj* self)
{
    u16* flags;
    u16 value;

    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0 || func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(&g_Player)) != 0) {
        flags = (u16*)self->unk7C;
        *flags ^= ice_core_shard_data.masks[self->unk2];
        func_8001540C(5, 2, NULL);
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
        func_8001540C(5, 2, NULL);
        spawn_debris(4, ice_core_shard_debris, self);
        self->state = 6;
    }
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        func_8001540C(5, 2, NULL);
        spawn_debris(4, ice_core_shard_debris, self);
        self->state = 6;
    }
    if (func_8002BB80(self, &g_Player) != 0) {
        func_8001540C(5, 2, NULL);
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
