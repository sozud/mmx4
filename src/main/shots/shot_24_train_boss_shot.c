// ShotObj, shot_object_update_funcs[24]
// 8009E0B8..8009EB6C
#include "common.h"
#include "main/shots/shot_24_train_boss_shot.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/objects.h"

extern u8 train_boss_arm_attack_box[4];
extern u8 train_boss_arm_hurt_boxes[2][4];

extern s16 train_boss_arm_reach[4];
extern u8 train_boss_arm_extended_clear_masks[4];

extern u8 train_boss_arm_extended_bits[4];
extern u8 train_boss_arm_active_clear_masks[4];

// train_boss_shot_state_funcs
extern void (*train_boss_shot_state_funcs[])(struct ShotObj*);
void train_boss_bullet_init(struct ShotObj*);

void train_boss_bullet_despawn(struct ShotObj*);
void train_boss_arm_init(struct ShotObj*);
void train_boss_arm_main(struct ShotObj*);
void train_boss_arm_destroyed(struct ShotObj*);

void train_boss_arm_resume_step(struct ShotObj* arg0);
void train_boss_arm_advance(struct ShotObj* arg0);
void train_boss_arm_wait_signal(struct ShotObj* arg0);
void train_boss_arm_windup(struct ShotObj* arg0);
void train_boss_arm_punch(struct ShotObj* arg0);
void train_boss_arm_hold(struct ShotObj* arg0);
void train_boss_arm_retract(struct ShotObj* arg0);

void train_boss_arm_return(struct ShotObj* arg0);
#ifdef MMX4_SATURN
#define ARM_OWNER_X(owner) ((owner)->x_pos.i.lo)
#define ARM_OWNER_STATE(owner) ((owner)->x_pos.bytes[0])
#else
#define ARM_OWNER_X(owner) ((owner)->x_pos.i.hi)
#define ARM_OWNER_STATE(owner) ((u8)(owner)->x_pos.val)
#endif
#include "weapon_resources.h"

extern u8 train_boss_arm_active_bits[4];

void train_boss_shot_update(struct ShotObj* self)
{
    train_boss_shot_state_funcs[self->state](self);
}

void train_boss_bullet_init(struct ShotObj* self)
{
    u16 flags;

    self->state = 1;
    self->on_screen = 1;
    self->unk58.collision_data = D_80106070;
    flags = self->unk42;
    self->unk42 = flags & 0x7FFF;
    self->x_vel.val = 0;
    self->y_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk16 = 0;
    self->unk68 = NULL;
    self->unk54 = train_boss_bullet_hit_box;
    self->unk50.data = train_boss_bullet_hit_box;
    self->unk6 = 0;
    self->unk84.shot_24.timer = 0x20;
    self->unk84.shot_24.owner_notified = 0;
    self->unk84.shot_24.owner_state = self->unk7C->unk6;
    self->unk5C = 1;
    self->unk60 = 4;
    set_animation(self, 4);
}

// train_boss_bullet_fly

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009E188(struct ShotObj* self);
void func_8009E8E0(struct ShotObj* self);
extern u8 train_boss_arm_active_bits[4];
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/shots/shot_24_train_boss_shot", func_8009E188);
#else
void func_8009E188(struct ShotObj* self)
{
    self->unk42 &= 0x7FFF;
    animate_object(ANIMATED_OBJECT(self));
    if ((((struct Main45Ext*)self->unk7C)->attack_flags & 7) == 7 || (((struct Main45Ext*)self->unk7C)->attack_flags & 8))
        goto despawn;
    if (self->unk6 == 0) {
        self->unk84.shot_24.timer = (u16)self->unk84.shot_24.timer - 1;
        if (self->unk84.shot_24.timer == 0) {
            func_8001540C(2, SATURN_SOUND(0x65, 0x4E), self);
            set_velocity_from_angle(MOVING_OBJECT(self), (u8)angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)));
            self->x_vel.val = (u32)self->x_vel.val * 3;
            self->y_vel.val = (u32)self->y_vel.val * 3;
            if (self->unk84.shot_24.owner_state == 3)
                self->unk84.shot_24.timer = 0;
            else
                self->unk84.shot_24.timer = 0x27;
            set_animation(self, 3);
            self->unk6 = 1;
        }
    } else {
        if (self->unk84.shot_24.timer == 0) {
            if (self->unk84.shot_24.owner_notified == 0) {
                self->unk84.shot_24.owner_notified = 1;
                ((struct Main45Ext*)self->unk7C)->projectile_command = 0xFF;
            }
        } else {
            self->unk84.shot_24.timer = (u16)self->unk84.shot_24.timer - 1;
        }
        move_object(MOVING_OBJECT(self));
        func_8002D9BC(self);
        if (func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(&g_Player)))
            goto despawn;
        if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
            spawn_explosion(BASE_OBJECT(self));
            goto despawn;
        }
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20))
        goto despawn;
    update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
    return;
despawn:
    self->on_screen = 0;
    self->state = 2;
}
#endif

void train_boss_bullet_despawn(struct ShotObj* self)
{
    if (self->unk84.shot_24.timer == 0) {
        if (self->unk84.shot_24.owner_notified == 0) {
            self->unk7C->x_pos.bytes[0] = 0xFF;
        }
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    self->unk84.shot_24.timer--;
}

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/shots/shot_24_train_boss_shot", train_boss_arm_init);
#else
void train_boss_arm_init(struct ShotObj* self)
{
    u16 y_offset;
#ifndef MMX4_SHC
    volatile s64 stack_pad;
#endif

    self->state = 4;
    self->unk5 = 2;
    self->on_screen = 1;
    self->unk58.animation_steps = D_80105FF0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->x_vel.val = FIXED(1);
    self->y_vel.val = 0;
    self->unk42 &= 0x7FFF;
    self->x_pos.i.hi += train_boss_arm_offsets[self->unk2][0];
    y_offset = train_boss_arm_offsets[self->unk2][1];
    self->unk16 = VISUAL_SATURN_LAYER(5);
    self->unk68 = NULL;
    self->unk54 = train_boss_arm_attack_box;
    self->unk50.data = train_boss_arm_hurt_boxes[0];
    self->y_pos.i.hi += y_offset;
    set_animation(self, 1);
    self->unk5C = 0x1A;
    self->unk60 = 6;
}
#endif

void train_boss_arm_main(struct ShotObj* self)
{
    struct WeaponObj* weapon;
    s32 result;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    train_boss_arm_step_funcs[self->unk5](self);
    self->unk84.bytes[1] = (u8)self->unk5;
    func_8002D9BC(self);
#ifdef VERSION_JP
    if (self->unk7C->x_pos.i.hi - 8 < g_Player.x_pos.i.hi) {
#endif
        result = func_8002DD04(MAIN_OBJECT(self));

        if (self->unk42 & 0x8000) {
#ifdef MMX4_PC
            ((struct Main45Ext*)self->unk7C)->layer_signals->projectile_state[self->unk2] = 2;
#else
        ((struct Shot24Owner*)self->unk7C)->collision_states[self->unk2 + 2] = 2;
#endif
        }
        if (result < 0) {
            weapon = self->unk7C;
            weapon->unk7 = (u8)weapon->unk7 & train_boss_arm_extended_clear_masks[self->unk2];
            self->unk5 = 8;
            return;
        }
#ifdef VERSION_JP
    }
#endif
    if ((u8)self->unk7C->active & train_boss_arm_extended_bits[self->unk2]) {
        self->state = 5;
        return;
    }
    update_on_screen(BASE_OBJECT(self), 0x200, 0x100);
}

void train_boss_arm_resume_step(struct ShotObj* self)
{
    self->unk5 = self->unk84.shot_24.owner_notified;
}

void train_boss_arm_advance(struct ShotObj* self)
{
    if (self->x_pos.i.hi > train_boss_arm_offsets[self->unk2][0] + 0x1AA0) {
        self->unk28 = 0;
        self->unk5 = 3;
        return;
    }

    move_object(MOVING_OBJECT(self));
}

void train_boss_arm_wait_signal(struct ShotObj* self)
{
    if (((*(u8*)&self->unk7C->x_pos.val) == self->unk2) || ((*(u8*)&self->unk7C->x_pos.val) == 4)) {
        func_8001540C(2, SATURN_SOUND(0x63, 0x4C), self);
        self->unk84.bytes[0] = self->unk7C->unk6;
        self->unk28 = 1;
        self->x_vel.val = FIXED(-2);
        self->unk7 = 0x10;
        self->unk5 = 4;
    }
}

void train_boss_arm_windup(struct ShotObj* self)
{
    s8 timer;
    u8* owner_state;

    owner_state = (u8*)&self->unk7C->x_pos;
    if (*owner_state == 4) {
        *owner_state = 5;
    }
    move_object(MOVING_OBJECT(self));
    timer = (u8)self->unk7 - 1;
    self->unk7 = timer;
    if (timer == 0) {
        func_8001540C(2, SATURN_SOUND(0x64, 0x4D), self);
        self->x_vel.val = FIXED(6);
        self->unk7 = 0x2A;
        self->unk5 = 5;
    }
}

void train_boss_arm_punch(struct ShotObj* self)
{
    s8 subtype;
    s8 timer;
    struct WeaponObj* owner;

    move_object(MOVING_OBJECT(self));
    owner = self->unk7C;
    subtype = self->unk2;
    if (self->x_pos.i.hi > (ARM_OWNER_X(owner) + train_boss_arm_reach[subtype])) {
        owner->unk7 = (u8)owner->unk7 | train_boss_arm_extended_bits[subtype];
    }
    timer = self->unk7 - 1;
    self->unk7 = timer;
    if (timer == 0) {
        self->unk7 = 0x10;
        self->unk5 = 6;
    }
}

void train_boss_arm_hold(struct ShotObj* self)
{
    if (--self->unk7 == 0) {
        self->unk7 = 0x37;
        self->x_vel.val = -FIXED(4);
        self->unk5 = 7;
    }
}

void train_boss_arm_retract(struct ShotObj* self)
{
    s8 shot_variant;
    struct WeaponObj* weapon;

    move_object(MOVING_OBJECT(self));
    weapon = self->unk7C;
    shot_variant = self->unk2;
    if (self->x_pos.i.hi < ARM_OWNER_X(weapon) + train_boss_arm_reach[shot_variant]) {
        weapon->unk7 = (u8)weapon->unk7 & train_boss_arm_extended_clear_masks[shot_variant];
    }

    self->unk7 = (u8)self->unk7 - 1;
    if (self->unk7 == 0) {
        if ((self->unk84.bytes[0] == 3 || self->unk84.bytes[0] == 4)) {
            self->unk7C->x_pos.bytes[0] = 0xFF;
        }
        self->unk28 = 0;
        self->unk5 = 3;
    } else if (self->unk7 == 26) {
        if ((self->unk84.bytes[0] != 3 && self->unk84.bytes[0] != 4)) {
            self->unk7C->x_pos.bytes[0] = 0xFF;
        }
    }
}

// train_boss_arm_break
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009E8E0(struct ShotObj* self)
{
    struct Main45Ext* owner = (struct Main45Ext*)self->unk7C;
#ifdef MMX4_SHC
    f32 saved_x, saved_y;
#else
    f32 saved_x = self->x_pos, saved_y = self->y_pos;
#endif
    s32 subtype = self->unk2;

#ifdef MMX4_SHC
    saved_x = self->x_pos;
    saved_y = self->y_pos;
#endif
    self->x_pos.i.hi = train_boss_arm_debris_positions[subtype][0];
    self->y_pos.i.hi = train_boss_arm_debris_positions[subtype][1];
    spawn_debris(6, train_boss_arm_debris, self);
    spawn_explosion(BASE_OBJECT(self));
    self->x_pos = saved_x;
    self->y_pos = saved_y;
    owner->attack_flags |= train_boss_arm_active_bits[subtype];
    self->x_pos.i.hi = (u16)owner->unk8A + train_boss_arm_offsets[subtype][0] - 0x70;
    self->unk5C = 0x1A;
    self->unk28 = 0;
    self->unk42 &= 0x7FFF;
    self->x_vel.val = FIXED(1);
    self->unk61 = 1;
    self->unk5 = 9;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_24_train_boss_shot", func_8009E8E0);
#endif

void train_boss_arm_return(struct ShotObj* self)
{
    if (self->x_pos.i.hi > (ARM_OWNER_X(self->unk7C) + *train_boss_arm_offsets[self->unk2])) {
        self->unk61 = 0;
        self->unk7C->active = (u8)self->unk7C->active & train_boss_arm_active_clear_masks[self->unk2];
        if (((u8)self->unk7C->active & 0xF) == (train_boss_arm_extended_bits[self->unk2] ^ 0xF)) {
            self->unk5 = 3;
            return;
        }
        self->unk5 = 0xA;
        return;
    }
    move_object(MOVING_OBJECT(self));
}

void train_boss_arm_wait_sync(struct ShotObj* self)
{
    if ((self->unk7C->active & 7) == ((self->unk7C->active & 0x70) >> 4)) {
        self->unk5 = 3;
    }
    if (ARM_OWNER_STATE(self->unk7C) != 4) {
        self->unk5 = 3;
    }
}

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/shots/shot_24_train_boss_shot", train_boss_arm_destroyed);
#else
void train_boss_arm_destroyed(struct ShotObj* self)
{
    u8 pad[8];
    self->state = 0;
    self->x_pos.i.hi = train_boss_arm_debris_positions[self->unk2][0];
    self->y_pos.i.hi = train_boss_arm_debris_positions[self->unk2][1];
    spawn_debris(6, train_boss_arm_debris, self);
    spawn_explosion(self);
    ZeroObjectState(OBJECT_HEADER(self));
}
#endif

u8 train_boss_bullet_hit_box[4] = { 0xFD, 0xFD, 0x05, 0x05 };

u8 train_boss_arm_attack_box[4] = { 0x43, 0xF7, 0x28, 0x11 };

u8 train_boss_arm_hurt_boxes[2][4] = {
    { 0x45, 0xFD, 0x25, 0x04 },
    { 0xFE, 0xF8, 0x03, 0x02 },
};

s16 train_boss_arm_offsets[3][2] = {
    { -0x72, -0x3A },
    { -0x6E, -0x18 },
    { -0x6D, 9 },
};

s16 train_boss_arm_reach[4] = { -0x53, -0x4F, -0x4E, 0 };

u16 train_boss_arm_debris_positions[3][2] = {
    { 0x1A8B, 0x0143 },
    { 0x1A8E, 0x0168 },
    { 0x1A8F, 0x018A },
};

u8 train_boss_arm_extended_bits[4] = { 1, 2, 4, 0 };

u8 train_boss_arm_active_bits[4] = { 0x10, 0x20, 0x40, 0 };

u8 train_boss_arm_extended_clear_masks[4] = { 0xFE, 0xFD, 0xFB, 0 };

u8 train_boss_arm_active_clear_masks[4] = { 0xEF, 0xDF, 0xBF, 0 };

u8 train_boss_arm_debris[8] = { 6, 7, 8, 6, 7, 8, 0, 0 };

void (*train_boss_shot_state_funcs[])(struct ShotObj*) = {
    train_boss_bullet_init,
    func_8009E188,
    train_boss_bullet_despawn,
    train_boss_arm_init,
    train_boss_arm_main,
    train_boss_arm_destroyed,
};

void (*train_boss_arm_step_funcs[11])(struct ShotObj*) = {
#ifdef MMX4_PC
    enemy_hit_reaction_shot,
#else
    (void (*)(struct ShotObj*))enemy_hit_reaction,
#endif
    train_boss_arm_resume_step,
    train_boss_arm_advance,
    train_boss_arm_wait_signal,
    train_boss_arm_windup,
    train_boss_arm_punch,
    train_boss_arm_hold,
    train_boss_arm_retract,
    func_8009E8E0,
    train_boss_arm_return,
    train_boss_arm_wait_sync,
};
