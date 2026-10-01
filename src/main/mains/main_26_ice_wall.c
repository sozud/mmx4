// MainObj, main_object_update_funcs[26]
// 80058158..800586F0
#include "common.h"
#include "func_tables.h"

void ice_wall_update(struct MainObj* self)
{
    ice_wall_state_funcs[self->state](self);
}

// ice_wall_init
INCLUDE_ASM("main/nonmatchings/mains/main_26_ice_wall", func_80058194);

void ice_wall_start_idle(struct MainObj* self)
{
    self->unk5 = 2;
}

void ice_wall_idle(struct MainObj* self)
{
}

void ice_wall_main(struct MainObj* self)
{
    s32 hit = func_8002DD04(self);
    s32 stage;

    if (self->ext.main_26.last_health != self->hp) {
        stage = self->ext.main_26.stage--;
        if (stage != 1) {
            if (stage == 2) {
                func_800583B0(self, self->x_pos.i.hi, self->y_pos.i.hi, 0);
            }
        } else {
            func_800583B0(self, self->x_pos.i.hi, self->y_pos.i.hi, 5);
            self->hp = 1;
        }
        self->ext.main_26.last_health = self->hp;
    }
    if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi, self->y_pos.i.hi - 0x10) == 0 || hit < 0) {
        self->state++;
        self->unk5 = 0;
        self->unk42 &= 0x7FFF;
        func_8001540C(5, 1, NULL);
        return;
    }
    ice_wall_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x50, 0x30) != 0) {
        despawn_object(OBJECT_HEADER(self));
    }
}

// spawn_ice_chunks
INCLUDE_ASM("main/nonmatchings/mains/main_26_ice_wall", func_800583B0);

void ice_wall_break_start(struct BaseObj* self)
{
    func_800583B0(self, self->x_pos.i.hi, self->y_pos.i.hi, 10);
    self->y_pos.u.hi += 0x18;
    spawn_debris(0xC, ice_wall_debris, self);
    self->unk5 += 2;
}

void ice_wall_break_idle(struct BaseObj* self)
{
}

void ice_wall_break_remove(struct BaseObj* self)
{
    despawn_object_permanently(OBJECT_HEADER(self));
}

void ice_wall_break(struct BaseObj* self)
{
    ice_wall_break_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(self, 0x50, 0x30) != 0) {
        despawn_object_permanently(OBJECT_HEADER(self));
    }
}

struct Unk_unk68 ice_wall_hurt_box[] = {
    { -16, -16, 0x30, 0x30 },
};

union AnimationStep ice_wall_anim_0[] = {
    { 0x00000001 },
};

union AnimationStep ice_wall_anim_1[] = {
    { 0x01000001 },
};

union AnimationStep ice_wall_anim_2[] = {
    { 0x02000001 },
};

union AnimationStep ice_wall_anim_3[] = {
    { 0x03000001 },
};

union AnimationStep ice_wall_anim_4[] = {
    { 0x04000001 },
};

union AnimationStep ice_wall_anim_5[] = {
    { 0x05000001 },
};

union AnimationStep* ice_wall_animations[] = {
    ice_wall_anim_0,
    ice_wall_anim_1,
    ice_wall_anim_2,
    ice_wall_anim_3,
    ice_wall_anim_4,
    ice_wall_anim_5,
};

u8 ice_wall_debris[] = {
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
};

void (*ice_wall_state_funcs[])(struct MainObj*) = {
    func_80058194,
    ice_wall_main,
    ice_wall_break,
};

void (*ice_wall_step_funcs[])() = {
    enemy_hit_reaction,
    ice_wall_start_idle,
    ice_wall_idle,
};

void (*ice_wall_break_funcs[])(struct BaseObj*) = {
    ice_wall_break_start,
    ice_wall_break_idle,
    ice_wall_break_remove,
};
