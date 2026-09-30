// MainObj, main_object_update_funcs[39]
// 80061590..80061DC0
#include "common.h"
#include "func_tables.h"

void falling_ceiling_update(struct MainObj* self)
{
    falling_ceiling_state_funcs[self->state](self);
}

// falling_ceiling_init
INCLUDE_ASM("main/nonmatchings/mains/main_39_falling_ceiling", func_800615CC);

void falling_ceiling_main(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    falling_ceiling_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    func_8002DD04(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x1000, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }
    self->state = 2;
}

void falling_ceiling_despawn(struct MainObj* self)
{
    self->ext.main_39.unk80.w = 0;
    self->ext.main_39.unk84.w = 0;
    despawn_object_permanently(OBJECT_HEADER(self));
}

// falling_ceiling_wait
INCLUDE_ASM("main/nonmatchings/mains/main_39_falling_ceiling", func_80061918);

void falling_ceiling_drop(struct MainObj* self)
{
    falling_ceiling_drop_funcs[self->unk6](self);
}

void falling_ceiling_drop_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_pos.i.hi > 0x118) {
        self->y_speed = 0;
        self->gravity = 0;
    }
    if (self->animation_step.fields.event != 0) {
        self->unk7C = 0x3C;
        set_animation(self, 2);
        self->unk6 = 1;
    }
}

// falling_ceiling_drop_fall
INCLUDE_ASM("main/nonmatchings/mains/main_39_falling_ceiling", func_80061B58);

void falling_ceiling_drop_land(struct MainObj* self)
{
    u8 object_id;

    animate_object(ANIMATED_OBJECT(self));
    object_id = self->unk2;
    if (!(object_id & 1)) {
        apply_tile_effect((s8)object_id / 2, self->ext.main_39.unk80.h.unk82, 0x120);
    }
    self->ext.main_39.unk88 = 1;
    self->gravity = FIXED(0.125);
    self->unk5 = 0;
    self->unk6 = 0;
}

void falling_ceiling_sink(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

s8 D_800FE944[4] = { -16, -7, 29, 29 };

s8 D_800FE948[4] = { -12, -5, 22, 26 };

s8 D_800FE94C[4] = { 0, 0, 16, 26 };

union AnimationStep falling_ceiling_anim_0[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02FE0001 },
};

union AnimationStep falling_ceiling_anim_1[] = {
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05000101 },
};

union AnimationStep falling_ceiling_anim_2[] = {
    { 0x07010003 },
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A010003 },
    { 0x0B010003 },
    { 0x0C010003 },
    { 0x0D010003 },
    { 0x06F90003 },
};

union AnimationStep* falling_ceiling_animations[4] = {
    falling_ceiling_anim_0,
    falling_ceiling_anim_1,
    falling_ceiling_anim_2,
    NULL,
};

void (*falling_ceiling_state_funcs[])(struct MainObj*) = {
    func_800615CC,
    falling_ceiling_main,
    falling_ceiling_despawn,
};

void (*falling_ceiling_step_funcs[3])(struct MainObj*) = {
    func_80061918,
    falling_ceiling_drop,
    falling_ceiling_sink,
};

void (*falling_ceiling_drop_funcs[3])(struct MainObj*) = { falling_ceiling_drop_start, func_80061B58, falling_ceiling_drop_land };
