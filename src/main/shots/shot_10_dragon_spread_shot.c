// ShotObj, shot_object_update_funcs[10]
// 8009B3E8..8009B67C
#include "common.h"

extern u8 dragon_spread_shot_hit_box[4];
extern u8 dragon_spread_shot_large_hit_box[4];
extern u8* dragon_spread_shot_animations[16];

void dragon_spread_shot_update(struct ShotObj* self)
{
    dragon_spread_shot_state_funcs[self->state](self);
}

// dragon_spread_shot_init
void func_8009B424(struct ShotObj* self)
{

    self->on_screen = 1;
    self->unk54 = dragon_spread_shot_hit_box;
    self->unk50.data = dragon_spread_shot_hit_box;
    self->unk28 = 0;
    self->unk2C = 0;
    self->unk67 = 0;
    self->unk16 = 0;
    self->unk15 = 0;
    self->unk68 = NULL;
    self->unk58.animation_steps = D_80105FF0;
    self->state++;
    self->unk42 &= 0x7FFF;
    self->unk40 = D_801406A8[9] >> 7;
    self->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 9);
    self->animation_table = (u32**)dragon_spread_shot_animations;
    self->unk42 = CLUT_FROM_ID(0xB);
    self->unk60 = 2;
    self->unk5C = 1;
    self->unk54 = dragon_spread_shot_large_hit_box;
    self->x_vel.val *= 5;
    self->y_vel.val *= 5;
    self->y_pos.u.hi -= 8;
    set_animation(self, self->unk2 >> 1);
    self->unk84.value = 0;
}

void dragon_spread_shot_fly(struct ShotObj* arg0)
{
    struct ShotObj* self = arg0;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        if (self->unk84.value > 2) {
            spawn_explosion(BASE_OBJECT(self));
        }
        self->state = (u8)self->state + 1;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
    } else {
        self->state = (u8)self->state + 1;
    }
    self->unk84.value += 1;
}

void dragon_spread_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void dragon_spread_shot_idle(struct ShotObj* arg)
{
}

u8 dragon_spread_shot_hit_box[4] = { 0xFD, 0xFA, 0x08, 0x08 };

u8 dragon_spread_shot_large_hit_box[4] = { 0xF7, 0xF6, 0x10, 0x13 };

u8 dragon_spread_shot_anim_steps[16][4] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
    { 1, 0, 0, 5 },
    { 1, 0, 0, 6 },
    { 1, 0, 0, 7 },
    { 1, 0, 0, 8 },
    { 1, 0, 0, 9 },
    { 1, 0, 0, 10 },
    { 1, 0, 0, 11 },
    { 1, 0, 0, 12 },
    { 1, 0, 0, 13 },
    { 1, 0, 0, 14 },
    { 1, 0, 0, 15 },
};

u8* dragon_spread_shot_animations[16] = {
    dragon_spread_shot_anim_steps[0],
    dragon_spread_shot_anim_steps[1],
    dragon_spread_shot_anim_steps[2],
    dragon_spread_shot_anim_steps[3],
    dragon_spread_shot_anim_steps[4],
    dragon_spread_shot_anim_steps[5],
    dragon_spread_shot_anim_steps[6],
    dragon_spread_shot_anim_steps[7],
    dragon_spread_shot_anim_steps[8],
    dragon_spread_shot_anim_steps[9],
    dragon_spread_shot_anim_steps[10],
    dragon_spread_shot_anim_steps[11],
    dragon_spread_shot_anim_steps[12],
    dragon_spread_shot_anim_steps[13],
    dragon_spread_shot_anim_steps[14],
    dragon_spread_shot_anim_steps[15],
};

void (*dragon_spread_shot_state_funcs[])(struct ShotObj*) = {
    func_8009B424,
    dragon_spread_shot_fly,
    dragon_spread_shot_despawn,
    dragon_spread_shot_idle,
};
