// MiscObj, misc_object_update_funcs[17]
// 800CADF8..800CB00C
#include "common.h"
#include "main/misc/misc_17_death_orb.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/sprite_animations.h"

void death_orb_fly(struct MiscObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/sprite_animations.h"
#endif

void death_orb_update(struct MiscObj* self)
{
    if (self->state == 0) {
        func_800CAE38(self);
    } else {
        death_orb_fly(self);
    }
}

// death_orb_init

extern s8 death_orb_frames[4];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CAE38(struct MiscObj* arg0);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/misc/misc_17_death_orb", func_800CAE38);
#else
void func_800CAE38(struct MiscObj* arg0)
{
    u8 variant;
    s32 x_vel;
    s32 y_vel;
    s32 animation;

    arg0->on_screen = 1;
    variant = arg0->unk2;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk38 = NULL;
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
    arg0->animation_table = D_8011BF40;
    arg0->unk42 = OBJECT_CLUT(0x7802);
    arg0->unk40 = WEAPON_TEXTURE_BASE;
    arg0->unk16 = 0x10;
    arg0->unk15 = 0;
    arg0->x_pos.val = g_Player.x_pos.val;
    arg0->y_pos.val = g_Player.y_pos.val;
    set_velocity_from_angle(MOVING_OBJECT(arg0), variant & 0x7F);
    x_vel = arg0->x_vel.val;
    y_vel = arg0->y_vel.val;
    if (arg0->unk2 & 0x80) {
        animation = 7;
        arg0->x_vel.val = x_vel * 8;
        arg0->y_vel.val = y_vel * 8;
    } else {
        arg0->x_vel.val = x_vel + (x_vel / 2) * death_orb_frames[arg0->unk2 & 3];
        arg0->y_vel.val = y_vel + (y_vel / 2) * death_orb_frames[arg0->unk2 & 3];
        animation = 6;
    }
    set_animation(arg0, animation);
    move_object(MOVING_OBJECT(arg0));
    arg0->state = (u8)arg0->state + 1;
    update_on_screen(BASE_OBJECT(arg0), 0x80000, 0x80000);
}
#endif

void death_orb_fly(struct MiscObj* self)
{
    if ((self->unk2 & 0x80) && (func_8002B1E8(BASE_OBJECT(self), 0x80000, 0x80000) == 1)) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x80000, 0x80000);
}

s8 death_orb_frames[4] = { 1, 3, 2, 3 };
