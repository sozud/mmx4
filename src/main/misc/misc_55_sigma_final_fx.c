// MiscObj, misc_object_update_funcs[55]
// 800D3084..800D3388
#include "common.h"
#include "main/misc/misc_55_sigma_final_fx.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

// sigma_final_fx_state_funcs
extern void (*sigma_final_fx_state_funcs[])(struct MiscObj*);

void sigma_final_fx_charge(struct MiscObj*);
void sigma_final_fx_despawn(struct MiscObj*);
void sigma_final_fx_gust(struct MiscObj* arg0);
void sigma_final_fx_follow(struct MiscObj*);

// sigma_final_fx_init
#ifdef MMX4_PC
void func_800D3084(struct MiscObj* self);
#endif

#ifdef MMX4_PC
void func_800D3084(struct MiscObj* self)
{
    struct MainObj* owner = (struct MainObj*)self->ext.misc_55.owner;
    s32 animation;

    self->x_pos.val = owner->x_pos.val;
    self->y_pos.val = owner->y_pos.val;
    self->unk40 = owner->unk40;
    self->unk42 = owner->unk42 & 0x7FFF;
    self->animation_table = (u32**)owner->animation_table;
    self->unk3C = (void*)owner->sprite_frames;
    self->unk15 = 0;
    self->bg_offset = owner->bg_offset;
    switch (self->unk2) {
    case 0:
        self->x_pos.i.hi = 0x4FF;
        self->y_pos.i.hi = 0x279;
        animation = 0x26;
        self->state = 1;
        break;
    case 1:
        self->x_pos.i.hi = 0x4FD;
        self->y_pos.i.hi = 0x259;
        animation = 0x26;
        self->state = 1;
        break;
    case 2:
        self->x_pos.i.hi = background_objects[0].x_pos.i.hi - 0x20;
        self->y_pos.i.hi = background_objects[0].y_pos.i.hi + (get_random() & 0xFF);
        self->x_vel.val = 0x30000;
        self->unk28 = -0x1000;
        self->state = 3;
        self->y_vel.val = 0;
        self->unk2C = 0;
        self->unk42 += 3;
        animation = 0x16;
        break;
    default:
        animation = 0xF;
        self->state = 4;
        break;
    }
    set_animation(self, animation);
    self->unk16 = 0x13;
    is_on_screen(BASE_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_55_sigma_final_fx", func_800D3084);
#endif

void sigma_final_fx_charge(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->state = 2;
    }
}

void sigma_final_fx_gust(struct MiscObj* self)
{
    move_with_gravity((struct AnimatedObj*)self);
    animate_object(self);
    is_on_screen(self);
    if (func_8002B160(self) != 0) {
        self->state = 2;
    }
}

void sigma_final_fx_follow(struct MiscObj* self)
{
    self->x_pos.u.hi = self->ext.misc_55.owner->x_pos.u.hi;
    self->y_pos.u.hi = self->ext.misc_55.owner->y_pos.u.hi;
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (self->ext.misc_55.owner->state == 2) {
        self->state = 2;
        self->unk5 = 0;
    }
    if (func_8002B160(BASE_OBJECT(self)) != 0) {
        self->state = 2;
        self->unk5 = 0;
    }
}

void sigma_final_fx_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void sigma_final_fx_update(struct MiscObj* self)
{
    if (self->ext.misc_55.owner->ext.main_74.death_kind != 0) {
        self->state = 2;
        self->unk5 = 0;
    }
    sigma_final_fx_state_funcs[self->state](self);
}

void (*sigma_final_fx_state_funcs[5])(struct MiscObj*) = {
    func_800D3084,
    sigma_final_fx_charge,
    sigma_final_fx_despawn,
    sigma_final_fx_gust,
    sigma_final_fx_follow,
};
