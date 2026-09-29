// ShotObj, shot_object_update_funcs[38]
// 800A428C..800A47C4
#include "common.h"

u8 owl_cyclone_hit_box[4] = { 0xFC, 0xFC, 0x08, 0x08 };
u8 owl_cyclone_column_box[4] = { 0xF0, 0x92, 0x1F, 0xD4 };

void owl_cyclone_update(struct ShotObj* self)
{
    owl_cyclone_state_funcs[self->state](self);
}

// owl_cyclone_init
INCLUDE_ASM("main/nonmatchings/shots/shot_38_owl_cyclone", func_800A42C8);

void owl_cyclone_fly(struct ShotObj* self)
{
    struct WeaponObj* owner = self->unk7C;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (self->unk2 < 5) {
        owl_cyclone_spawn_trail(self);
        if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
            spawn_explosion(BASE_OBJECT(self));
            self->state++;
            return;
        }
    } else {
        if (owner->state == 2) {
            self->state++;
            return;
        }
        if (--self->timer == 0) {
            switch (self->unk84.value) {
            case 0:
                self->unk84.value = 1;
                self->timer = 0x2D;
                self->y_vel.val = 0;
                break;
            case 1:
                self->timer = 0xC;
                self->unk84.value = 2;
                self->y_vel.val = FIXED(21);
                break;
            case 2:
                self->unk84.value = 3;
                self->timer = 0x3E;
                self->y_vel.val = 0;
                break;
            case 3:
                self->unk84.value = 4;
                self->y_vel.val = FIXED(21);
                self->timer = 0xC;
                break;
            }
        }
    }
    if (owner->active == 0) {
        self->state++;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, self->unk2 < 5 ? 0x20 : 0x80) == 0) {
        if (self->unk2 < 5) {
            update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
        }
    } else {
        self->state++;
    }
}

void owl_cyclone_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void owl_cyclone_idle(struct ShotObj* self)
{
}

void owl_cyclone_spawn_trail(struct ShotObj* self)
{
    struct ShotObj* shot;
    struct MiscObj* misc;
    s32 timer;

    shot = self;
    timer = shot->unk84.value;
    if (timer == 0) {
        misc = find_free_misc_obj();
        if (misc != 0) {
            misc->active = 0x41;
            misc->id = 0x23;
            misc->unk2 = shot->unk2;
            misc->ext.pointer.unk50 = shot;
            misc->bg_offset = shot->bg_offset;
            misc->unk42 = shot->unk42;
            misc->animation_table = shot->animation_table;
            misc->unk3C = shot->unk3C;
            misc->unk40 = shot->unk40;
            misc->unk15 = shot->unk15;
            misc->x_pos.u.hi = shot->x_pos.u.hi;
            misc->y_pos.u.hi = shot->y_pos.u.hi;
        }
        timer = 5;
    } else {
        timer--;
    }
    shot->unk84.value = timer;
}

void (*owl_cyclone_state_funcs[])(struct ShotObj*) = {
    func_800A42C8,
    owl_cyclone_fly,
    owl_cyclone_despawn,
    owl_cyclone_idle,
};
