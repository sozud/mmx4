// MiscObj, misc_object_update_funcs[49]
// 800D1990..800D1B44
#include "common.h"
#include "main/misc/misc_49_double_afterimage.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

// double_afterimage_state_funcs
extern void (*double_afterimage_state_funcs[])(struct MiscObj*);

void func_800D1A48(struct MiscObj*);
void double_afterimage_despawn(struct MiscObj*);

// double_afterimage_init
#ifdef MMX4_PC
void func_800D1990(struct MiscObj* arg0);
extern u8 double_afterimage_angles[4];
#endif

#ifdef MMX4_PC
void func_800D1990(struct MiscObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 3;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    if (arg0->unk2 == 4) {
        arg0->ext.misc_49.timer = 0x14;
        set_animation(arg0, 0x1E);
        return;
    }
    set_animation(arg0, 0x12);
    set_velocity_from_angle(MOVING_OBJECT(arg0), double_afterimage_angles[arg0->unk2]);
    arg0->unk2C = 0x4000;
    arg0->ext.misc_49.timer = 0xA;
    arg0->unk28 = 0;
    arg0->x_vel.val *= 2;
    arg0->y_vel.val *= 3;
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_49_double_afterimage", func_800D1990);
#endif

// double_afterimage_fade
void func_800D1A48(struct MiscObj* self)
{
    if (self->unk2 != 4) {
        if (--self->ext.misc_49.timer == 0) {
            self->on_screen = 0;
            self->state = 2;
            return;
        }
        animate_object(ANIMATED_OBJECT(self));
        move_with_gravity(ANIMATED_OBJECT(self));
    } else {
        if (--self->ext.misc_49.timer == 0) {
            self->on_screen = 0;
            self->state = 2;
            return;
        }
        animate_object(ANIMATED_OBJECT(self));
    }
    is_on_screen(BASE_OBJECT(self));
}

void double_afterimage_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void double_afterimage_update(struct MiscObj* self)
{
    double_afterimage_state_funcs[self->state](self);
}

u8 double_afterimage_angles[4] = { 4, 12, 16, 31 };

void (*double_afterimage_state_funcs[3])(struct MiscObj*) = {
    func_800D1990,
    func_800D1A48,
    double_afterimage_despawn,
};
