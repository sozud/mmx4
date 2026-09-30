// ShotObj, shot_object_update_funcs[24]
// 8009E0B8..8009EB6C
#include "common.h"

void train_boss_shot_update(struct ShotObj* self)
{
    train_boss_shot_state_funcs[self->state](self);
}

void train_boss_bullet_init(struct ShotObj* self)
{
    u16 flags;
    struct WeaponObj* owner;

    flags = self->unk42;
    owner = self->unk7C;
    self->state = 1;
    self->on_screen = 1;
    self->unk58.collision_data = D_80106070;
    self->x_vel.val = 0;
    self->unk54 = train_boss_bullet_hit_box;
    self->unk50.data = train_boss_bullet_hit_box;
    self->unk84.shot_24.timer = 0x20;
    self->y_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk16 = 0;
    self->unk68 = NULL;
    self->unk6 = 0;
    self->unk84.shot_24.owner_notified = 0;
    self->unk42 = flags & 0x7FFF;
    self->unk84.shot_24.owner_state = owner->unk6;
    self->unk5C = 1;
    self->unk60 = 4;
    set_animation(self, 4);
}

// train_boss_bullet_fly
INCLUDE_ASM("main/nonmatchings/shots/shot_24_train_boss_shot", func_8009E188);

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

void train_boss_arm_init(struct ShotObj* self)
{
    u16 y_offset;
    volatile s64 stack_pad;

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
    self->unk16 = 5;
    self->unk54 = train_boss_arm_attack_box;
    self->unk68 = NULL;
    self->unk50.data = train_boss_arm_hurt_boxes[0];
    self->y_pos.i.hi += y_offset;
    set_animation(self, 1);
    self->unk5C = 0x1A;
    self->unk60 = 6;
}

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
            ((struct Shot24Owner*)self->unk7C)->collision_states[self->unk2 + 2] = 2;
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
    if (train_boss_arm_offsets[self->unk2][0] + 0x1AA0 < self->x_pos.i.hi) {
        self->unk28 = 0;
        self->unk5 = 3;
        return;
    }

    move_object(MOVING_OBJECT(self));
}

void train_boss_arm_wait_signal(struct ShotObj* self)
{
    u8 temp_v1;

    temp_v1 = *(u8*)&self->unk7C->x_pos.val;
    if ((temp_v1 == self->unk2) || (temp_v1 == 4)) {
        func_8001540C(2, 0x63, self);
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
        func_8001540C(2, 0x64, self);
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
    if ((owner->x_pos.i.hi + train_boss_arm_reach[subtype]) < self->x_pos.i.hi) {
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
    s8 timer;
    struct WeaponObj* weapon;

    move_object(MOVING_OBJECT(self));
    weapon = self->unk7C;
    shot_variant = self->unk2;
    if (self->x_pos.i.hi < weapon->x_pos.i.hi + train_boss_arm_reach[shot_variant]) {
        weapon->unk7 = (u8)weapon->unk7 & train_boss_arm_extended_clear_masks[shot_variant];
    }

    timer = (u8)self->unk7 - 1;
    self->unk7 = timer;
    if (timer == 0) {
        if (self->unk84.bytes[0] >= 3 && self->unk84.bytes[0] <= 4) {
            self->unk7C->x_pos.bytes[0] = 0xFF;
        }
        self->unk28 = 0;
        self->unk5 = 3;
    } else if (timer == 26) {
        if (self->unk84.bytes[0] < 3 || self->unk84.bytes[0] > 4) {
            self->unk7C->x_pos.bytes[0] = 0xFF;
        }
    }
}

// train_boss_arm_break
INCLUDE_ASM("main/nonmatchings/shots/shot_24_train_boss_shot", func_8009E8E0);

void train_boss_arm_return(struct ShotObj* self)
{
    if ((self->unk7C->x_pos.i.hi + *train_boss_arm_offsets[self->unk2]) < self->x_pos.i.hi) {
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
    u8 active;

    active = self->unk7C->active;
    if ((active & 7) == ((active & 0x70) >> 4)) {
        self->unk5 = 3;
    }
    if ((u8)self->unk7C->x_pos.val != 4) {
        self->unk5 = 3;
    }
}

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
    enemy_hit_reaction,
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
