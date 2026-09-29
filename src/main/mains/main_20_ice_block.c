// MainObj, main_object_update_funcs[20]
// 8005458C..80054C50
#include "common.h"
#include "func_tables.h"

void ice_block_update(struct MainObj* self)
{
    ice_block_state_funcs[self->state](self);
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    CollisionRelated(PLAYER_OBJECT(self));
}

// ice_block_init
INCLUDE_ASM("main/nonmatchings/mains/main_20_ice_block", func_800545EC);

void ice_block_start_idle(struct MainObj* self)
{
    self->unk5 = 2;
    set_animation(self, 0);
}

void ice_block_idle(struct MainObj* self)
{
    animate_object(self);
}

void ice_block_main(struct MainObj* self)
{
    s32 collision = func_8002DD04(self);
    s8 countdown;

    if (self->unk2 == 0 && self->ext.main_20.unk80 != self->hp) {
        countdown = self->ext.main_20.unk81--;
        if (countdown != 1) {
            if (countdown == 2) {
                func_800583B0(self, self->x_pos.i.hi, self->y_pos.i.hi - 0x10, 0);
            }
        } else {
            func_800583B0(self, self->x_pos.i.hi, self->y_pos.i.hi - 0x10, 5);
            self->hp = 1;
        }
        self->ext.main_20.unk80 = self->hp;
    }
    if (collision < 0) {
        self->unk5 = 0;
        self->state++;
        self->unk42 &= 0x7FFF;
        return;
    }
    ice_block_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
    } else {
        despawn_object(OBJECT_HEADER(self));
    }
}

// ice_block_break_start
INCLUDE_ASM("main/nonmatchings/mains/main_20_ice_block", func_800548B8);

void ice_block_break_crumble(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->attack_box = (const u8*)&ice_block_crumble_attack_box;
    }
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5++;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void ice_block_break_remove(struct MainObj* self)
{
    self->unk7C = 1;
    despawn_object_permanently(OBJECT_HEADER(self));
}

void ice_block_break(struct MainObj* self)
{
    ice_block_break_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0) {
        if (self->unk7C == 0) {
            update_on_screen(BASE_OBJECT(self), 0x50, 0x80);
        }
    } else {
        despawn_object_permanently(OBJECT_HEADER(self));
    }
}

struct Unk_unk68 D_800FC844 = { -7, -14, 14, 27 };

struct Unk_unk68 D_800FC848 = { -7, -14, 14, 27 };

struct Unk_unk68 D_800FC84C = { -24, -36, 48, 48 };

struct Unk_unk68 D_800FC850 = { -15, -16, 29, 64 };

struct Unk_unk68 D_800FC854 = { -15, -48, 29, 64 };

struct Unk_unk68 D_800FC858 = { -15, -16, 29, 32 };

struct Unk_unk68 D_800FC85C = { -15, -48, 29, 96 };

struct Unk_unk68 ice_block_crumble_attack_box = { 0, 0, 0, 0 };

union AnimationStep ice_block_anim_0[] = {
    { 0x0001000C },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x01010001 },
    { 0x00010001 },
    { 0x01010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x01010001 },
    { 0x01F40001 },
};

union AnimationStep ice_block_anim_1[] = {
    { 0x04010003 },
    { 0x05010002 },
    { 0x06010003 },
    { 0x07010008 },
    { 0x00010002 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x09010001 },
    { 0x08F60002 },
};

union AnimationStep ice_block_anim_6[] = {
    { 0x10010003 },
    { 0x11010004 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x16010003 },
    { 0x17010103 },
    { 0x18010003 },
    { 0x19010004 },
    { 0x1A010004 },
    { 0x1AF50001 },
};

union AnimationStep ice_block_anim_7[] = {
    { 0x1B010003 },
    { 0x1C010004 },
    { 0x1D010003 },
    { 0x1E010003 },
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21010003 },
    { 0x22010103 },
    { 0x23010003 },
    { 0x24010004 },
    { 0x25010004 },
    { 0x25F50001 },
};

union AnimationStep ice_block_anim_8[] = {
    { 0x26010003 },
    { 0x27010004 },
    { 0x28010003 },
    { 0x29010003 },
    { 0x2A010002 },
    { 0x2B010002 },
    { 0x2C010003 },
    { 0x2D010103 },
    { 0x2E010003 },
    { 0x2F010004 },
    { 0x30010004 },
    { 0x30F50001 },
};

union AnimationStep ice_block_anim_2[] = {
    { 0x0C000001 },
};

union AnimationStep ice_block_anim_3[] = {
    { 0x0D000001 },
};

union AnimationStep ice_block_anim_4[] = {
    { 0x0E000001 },
};

union AnimationStep ice_block_anim_5[] = {
    { 0x0F000001 },
};

union AnimationStep* ice_block_animations[9] = {
    ice_block_anim_0,
    ice_block_anim_1,
    ice_block_anim_2,
    ice_block_anim_3,
    ice_block_anim_4,
    ice_block_anim_5,
    ice_block_anim_6,
    ice_block_anim_7,
    ice_block_anim_8,
};

u8 ice_block_debris[4] = { 2, 3, 4, 5 };

void (*ice_block_state_funcs[3])() = {
    func_800545EC,
    ice_block_main,
    ice_block_break,
};

void (*ice_block_step_funcs[3])() = {
    enemy_hit_reaction,
    ice_block_start_idle,
    ice_block_idle,
};

void (*ice_block_break_funcs[3])() = {
    func_800548B8,
    ice_block_break_crumble,
    ice_block_break_remove,
};
