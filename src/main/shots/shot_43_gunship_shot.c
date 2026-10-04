// ShotObj, shot_object_update_funcs[43]
// 800A6960..800A6FCC
#include "common.h"

void gunship_shot_update(struct ShotObj* self)
{
    gunship_shot_state_funcs[self->state](self);
}

// gunship_shot_init
INCLUDE_ASM("main/nonmatchings/shots/shot_43_gunship_shot", func_800A699C);

void gunship_shot_bullet_fall(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 3;
        return;
    }
    func_8002D9BC(self);
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state = 3;
}

void gunship_shot_missile_fly(struct ShotObj* self)
{
    struct MiscObj* misc;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 3;
        return;
    }
    if (func_8002D9BC(self) != 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state++;
        return;
    }
    if (self->unk8C.word != 0) {
        func_800A6DF4(self);
        self->unk8C.word--;
    }
    if (self->unk7 == 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x21;
            misc->id = 0x17;
            misc->unk2 = 0;
            misc->unk15 = get_random() & 0x40;
            misc->ext.unk.unk54 = 0;
            misc->x_pos.i.hi = self->x_pos.i.hi;
            misc->y_pos.i.hi = self->y_pos.i.hi;
            misc->unk7 = 1;
            misc->x_vel.val = 0;
            misc->y_vel.val = 0;
            misc->unk16 = 7;
        }
        self->unk7 = 2;
    } else {
        self->unk7--;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state++;
    }
}

void gunship_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void gunship_shot_idle(struct ShotObj* self)
{
}

// gunship_shot_missile_steer
INCLUDE_ASM("main/nonmatchings/shots/shot_43_gunship_shot", func_800A6DF4);

u8 gunship_shot_bullet_hit_box[4] = { 0xF7, 0xFB, 0x0C, 0x08 };

u8 gunship_shot_missile_hit_box[4] = { 0xFA, 0xFA, 0x0C, 0x0D };

s32 gunship_shot_missile_speeds[2] = { -0x40000, 0x40000 };

void (*gunship_shot_state_funcs[])(struct ShotObj*) = {
    func_800A699C,
    gunship_shot_bullet_fall,
    gunship_shot_missile_fly,
    gunship_shot_despawn,
    gunship_shot_idle,
};
