// MainObj, main_object_update_funcs[50]
// 8006970C..80069A94
#include "common.h"
#include "func_tables.h"

void train_crate_update(struct MainObj* self)
{
    train_crate_state_funcs[self->state](self);
}

// train_crate_init
INCLUDE_ASM("main/nonmatchings/mains/main_50_train_crate", func_80069748);

// train_crate_main
INCLUDE_ASM("main/nonmatchings/mains/main_50_train_crate", func_800698D8);

void train_crate_explode(struct MainObj* self)
{
    if (++self->ext.main_50.timer != 0x30) {
        if (!(main_bss_state.frame_counter & 7)) {
            func_800AF878(BASE_OBJECT(self), 1, 0x18, 0x18);
        }
    } else {
        self->state = 3;
    }
}

void train_crate_despawn(struct MainObj* self)
{
    despawn_object_permanently(self);
}

void train_crate_idle(struct MainObj* self)
{
}

u8 train_crate_hurt_box[4] = { 0xE0, 0xE0, 0x40, 0x50 };

u8 D_800FFBDC[6] = { 0, 1, 2, 1, 0, 2 };

u8 train_crate_debris[6] = { 7, 8, 9, 7, 9, 8 };

union AnimationStep train_crate_anim_0[1] = { { 0x00000101 } };

union AnimationStep train_crate_anim_1[1] = { { 0x01000001 } };

union AnimationStep train_crate_anim_2[1] = { { 0x02000001 } };

union AnimationStep train_crate_anim_3[1] = { { 0x03000001 } };

union AnimationStep train_crate_anim_4[1] = { { 0x04000001 } };

union AnimationStep train_crate_anim_5[1] = { { 0x05000001 } };

union AnimationStep train_crate_anim_6[1] = { { 0x06000001 } };

union AnimationStep train_crate_anim_7[1] = { { 0x07000001 } };

union AnimationStep train_crate_anim_8[1] = { { 0x08000001 } };

union AnimationStep train_crate_anim_9[1] = { { 0x09000001 } };

union AnimationStep* train_crate_animations[10] = {
    train_crate_anim_0,
    train_crate_anim_1,
    train_crate_anim_2,
    train_crate_anim_3,
    train_crate_anim_4,
    train_crate_anim_5,
    train_crate_anim_6,
    train_crate_anim_7,
    train_crate_anim_8,
    train_crate_anim_9,
};

void (*train_crate_state_funcs[])(struct MainObj*) = {
    func_80069748,
    func_800698D8,
    train_crate_explode,
    train_crate_despawn,
};

void (*train_crate_step_funcs[2])() = {
    enemy_hit_reaction,
    train_crate_idle,
};

#ifdef MMX4_WIN32
u8 D_800FFB5C[4] = { 0, 0, 13, 21 };
#endif
