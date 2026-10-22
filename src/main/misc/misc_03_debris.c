// MiscObj, misc_object_update_funcs[3]
// 800C85D0..800C8774
#include "common.h"
#include "main/misc/misc_03_debris.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

void func_800C8610(struct MiscObj* arg0);
void debris_fall(struct MiscObj* arg0);

void debris_update(struct MiscObj* self)
{
    if (self->state == 0) {
        func_800C8610(self);
    } else {
        debris_fall(self);
    }
}

// debris_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
extern s32 debris_x_speeds[8];
extern s32 debris_y_speeds[8];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800C8610(struct MiscObj* arg0)
{
    struct MainObj* owner = arg0->ext.misc_2.owner;

    arg0->on_screen = 1;
    if (arg0->unk2 == 0) {
        arg0->unk3C = (void*)owner->sprite_frames;
        arg0->animation_table = (u32**)owner->animation_table;
        arg0->unk40 = owner->unk40;
        arg0->unk42 = owner->unk42 & 0x7FFF;
    }
    arg0->unk16 = 1;
    arg0->unk2C = 0x5000;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->x_vel.val = debris_x_speeds[get_random() & 7] + owner->x_speed / 2;
    arg0->y_vel.val = debris_y_speeds[get_random() & 7];
    set_animation(arg0, arg0->ext.misc_2.unk58);
    arg0->state = (u8)arg0->state + 1;
    is_on_screen(BASE_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_03_debris", func_800C8610);
#endif

void debris_fall(struct MiscObj* self)
{
    u8 temp_v0;

    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        move_with_gravity((struct AnimatedObj*)self);
        animate_object(self);
        if (FLICKER_ENABLED) {
            self->on_screen ^= 1;
        }
        if (self->on_screen != 0) {
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

s32 debris_x_speeds[8] = { -0x30000, -0x20000, 0x18000, 0x28000, -0x38000, -0x28000, 0x20000, 0x30000 };
s32 debris_y_speeds[8] = { 0x38000, 0x48000, 0x60000, 0x30000, 0x40000, 0x50000, 0x58000, 0x28000 };
