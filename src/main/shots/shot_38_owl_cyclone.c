// ShotObj, shot_object_update_funcs[38]
// 800A428C..800A47C4
#include "common.h"
#include "main/objects.h"
#include "main/shots/shot_38_owl_cyclone.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"

#ifdef MMX4_PC
#include "main/collision_bounds.h"
#endif

// owl_cyclone_state_funcs
extern void (*owl_cyclone_state_funcs[])(struct ShotObj*);

void owl_cyclone_fly(struct ShotObj*);

void owl_cyclone_despawn(struct ShotObj*);
void owl_cyclone_idle(struct ShotObj*);

u8 owl_cyclone_hit_box[4] = { 0xFC, 0xFC, 0x08, 0x08 };
u8 owl_cyclone_column_box[4] = { 0xF0, 0x92, 0x1F, 0xD4 };

void owl_cyclone_update(struct ShotObj* self)
{
    owl_cyclone_state_funcs[self->state](self);
}

// owl_cyclone_init
#ifdef MMX4_PC
void func_800A42C8(struct ShotObj* arg0);
#endif

#ifdef MMX4_PC
void func_800A42C8(struct ShotObj* arg0)
{
    struct MainObj* owner = (struct MainObj*)arg0->unk7C;
    s16 dx = 0;
    s16 dy = 0;

    arg0->unk58.data = (u8*)D_80105FF0;
    arg0->unk60 = 6;
    arg0->unk54 = owl_cyclone_hit_box;
    arg0->unk50.data = owl_cyclone_hit_box;
    arg0->unk84.value = 4;
    arg0->state++;
    arg0->on_screen = 1;
    arg0->unk68 = NULL;
    arg0->unk5C = 1;
    arg0->unk42 &= 0x7FFF;
    switch ((u8)arg0->unk2) {
    case 0:
        set_animation(arg0, 0xF);
        arg0->x_vel.val = 0x45000;
        arg0->y_vel.val = 0x45000;
        dx = 0xB;
        dy = -0x15;
        break;
    case 1:
        set_animation(arg0, 0x10);
        arg0->x_vel.val = 0x52800;
        arg0->y_vel.val = 0x2A000;
        dx = 0x10;
        dy = -0x13;
        break;
    case 2:
        set_animation(arg0, 0x11);
        arg0->x_vel.val = 0x60000;
        arg0->y_vel.val = 0;
        if (owner->unk17 == 4) {
            dx = 0x19;
            dy = -6;
        } else {
            dx = 0x13;
            dy = -0xD;
        }
        break;
    case 3:
        set_animation(arg0, 0x12);
        arg0->x_vel.val = 0x52800;
        arg0->y_vel.val = -0x2A000;
        dx = 0x19;
        dy = 0;
        break;
    case 4:
        set_animation(arg0, 0x13);
        arg0->x_vel.val = 0x45000;
        arg0->y_vel.val = -0x45000;
        dx = 0x14;
        dy = 5;
        break;
    case 5:
        arg0->unk58.data = (u8*)D_80105FF0;
        arg0->unk50.data = owl_cyclone_column_box;
        arg0->unk54 = NULL;
        set_animation(arg0, 0x1D);
        arg0->unk60 = 9;
        arg0->on_screen = 0;
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->unk84.value = 0;
        arg0->timer = 1;
        break;
    }
    if (arg0->unk2 >= 5)
        return;
    if (owner->unk15 == 0) {
        arg0->x_pos.i.hi = owner->x_pos.i.hi - dx;
        arg0->x_vel.val = -arg0->x_vel.val;
    } else {
        arg0->x_pos.i.hi = owner->x_pos.i.hi + dx;
    }
    arg0->y_pos.i.hi = owner->y_pos.i.hi + dy;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_38_owl_cyclone", func_800A42C8);
#endif

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
                self->unk84.value = 2;
                self->timer = 0xC;
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
