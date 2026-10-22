// ShotObj, shot_object_update_funcs[25]
// 8009EB6C..8009EE68
#include "common.h"
#include "main/shots/shot_24_train_boss_shot.h"
#include "main/shots/shot_25_grenade.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"

void grenade_fly(struct ShotObj*);

// grenade_state_funcs
extern void (*grenade_state_funcs[])(struct ShotObj*);

void grenade_despawn(struct ShotObj* arg0);
void grenade_idle(struct ShotObj* arg0);
#include "weapon_resources.h"

extern u8 grenade_hit_box[4];
extern s8 grenade_spawn_offsets[8];
extern u8 grenade_terrain_box[4];

void grenade_update(struct ShotObj* self)
{
    grenade_state_funcs[self->state](self);
}

// grenade_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009EBA8(struct ShotObj* self);
extern u8 grenade_hit_box[4];
extern u8 grenade_terrain_box[4];
extern s8 grenade_spawn_offsets[8];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009EBA8(struct ShotObj* self)
{
    s32 velocity;
    s32 variant;
    s16 x;

    self->on_screen = 1;
    self->state = (u8)self->state + 1;
    variant = (u8)self->unk2 & 0xF;

    if (self->unk2 & 0x80) {
        self->y_vel.val = 0;
        velocity = variant == 1 ? -FIXED(3) : -FIXED(1.5);
        if (self->unk15 != 0) {
            velocity = FIXED(3);
        }
        self->x_vel.val = velocity;
        if (variant == 0) {
            self->y_vel.val = FIXED(1.5);
        }
        if (variant == 2) {
            self->y_vel.val = -FIXED(1.5);
        }
        self->unk28 = 0;
        self->unk2C = 0;
        set_animation(self, 0x10);
        self->unk60 = 2;
    } else {
        velocity = self->unk15 != 0 ? FIXED(3) : -FIXED(3);
        self->y_vel.val = FIXED(1.5);
        self->x_vel.val = velocity;
        self->unk28 = 0;
        self->unk2C = 0x4000;
        set_animation(self, 0x16);
        self->unk60 = 5;
    }

    x = self->x_pos.i.hi;
    if (self->unk15 != 0) {
        x += grenade_spawn_offsets[variant << 1];
    } else {
        x -= grenade_spawn_offsets[variant << 1];
    }
    self->x_pos.i.hi = x;

    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->unk68 = (struct Unk_unk68*)grenade_terrain_box;
    self->unk54 = grenade_hit_box;
    self->unk50.data = grenade_hit_box;
    self->unk67 = 0;
    self->y_pos.u.hi += (s8)grenade_spawn_offsets[(variant << 1) + 1];
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_25_grenade", func_8009EBA8);
#endif

void grenade_fly(struct ShotObj* self)
{
    animate_object(self);
    move_with_gravity(self);
    func_8002D9BC(self);

    if (func_8002BB80(self, &g_Player) != 0) {
        if (self->unk2 & 0x40) {
        label:
            spawn_explosion(self);
        }
    } else if (!(self->unk2 & 0x40) || (CollisionRelated(self), self->unk70 == 0)) {
        if (func_8002B160(self) == 0) {
            is_on_screen(self);
            return;
        }
    } else {
        goto label; // unfortunately seems to be necessary for a match
    }

    self->state++;
}

void grenade_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void grenade_idle(struct ShotObj* self)
{
}

extern void (*train_boss_arm_step_funcs[11])(struct ShotObj*);

u8 grenade_hit_box[4] = { 0xF9, 0xF9, 0x0C, 0x0C };

u8 grenade_terrain_box[4] = { 0, 0, 4, 4 };

s8 grenade_spawn_offsets[8] = { 0x21, -0x2A, 0x30, -0x15, 0x28, 7, 0, 0 };

void (*grenade_state_funcs[])(struct ShotObj*) = {
    func_8009EBA8,
    grenade_fly,
    grenade_despawn,
    grenade_idle,
};
