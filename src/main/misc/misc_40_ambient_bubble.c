// MiscObj, misc_object_update_funcs[40]
// 800CFB70..800CFE98
#include "common.h"
#include "main/misc/misc_40_ambient_bubble.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#include "main/objects.h"

// ambient_bubble_step_funcs
extern void (*ambient_bubble_step_funcs[])(struct MiscObj*);

void ambient_bubble_float(struct MiscObj*);

extern s32 ambient_bubble_max_speeds[4];

// ambient_bubble_state_funcs
extern void (*ambient_bubble_state_funcs[])(struct MiscObj*);

void ambient_bubble_main(struct MiscObj*);
void ambient_bubble_despawn(struct MiscObj*);
#include "weapon_resources.h"

// ambient_bubble_init

extern union AnimationStep* ambient_bubble_animations[3];
extern u16 ambient_bubble_positions[8];
extern s32 ambient_bubble_speeds[4];
extern s32 ambient_bubble_accels[4];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CFB70(struct MiscObj* arg0);
void func_800CFC6C(struct MiscObj* arg0);
extern u16 ambient_bubble_respawn_delays[4];
extern ret_u8 func_8002938C(s32);
#endif

void func_800CFB70(struct MiscObj* arg0)
{
    u8 resource = func_8002938C(0x9F);

    arg0->active |= 0x40;
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk40 = OBJECT_STAGE_TEXTURE(resource);
    arg0->unk42 = VISUAL_STAGE_PALETTE(resource);
    arg0->animation_table = (u32**)ambient_bubble_animations;
    arg0->unk16 = 0x20;
    arg0->bg_offset = 1;
    arg0->unk15 = PLAYER_FACING_RIGHT;
    arg0->state++;
    arg0->unk2 &= 3;
    arg0->ext.misc_24.timer = ambient_bubble_respawn_delays[arg0->unk2];
}

// ambient_bubble_wait
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/misc/misc_40_ambient_bubble", func_800CFC6C);
#else
void func_800CFC6C(struct MiscObj* arg0)
{
    if ((u16)arg0->ext.misc_24.timer != 0) {
        arg0->ext.misc_24.timer--;
        return;
    }
    arg0->x_pos.i.hi = background_objects[1].x_pos.i.hi + 0x14A;
    arg0->y_pos.i.hi = background_objects[1].y_pos.i.hi + ambient_bubble_positions[get_random() & 7];
    set_animation(arg0, 1);
    arg0->y_vel.val = 0;
    arg0->unk5++;
    arg0->unk28 = 0;
    arg0->x_vel.val = ambient_bubble_speeds[arg0->unk2];
    arg0->unk2C = ambient_bubble_accels[arg0->unk2];
}
#endif

void ambient_bubble_float(struct MiscObj* self)
{
    s8 subtype;

    subtype = self->unk2;
    if (self->y_vel.val < ambient_bubble_max_speeds[subtype]) {
        self->unk2C = -ambient_bubble_accels[subtype];
        set_animation(self, 2);
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->unk5 = 0;
    self->ext.misc_24.timer = ambient_bubble_respawn_delays[self->unk2] + (get_random() & 0x3F);
}

void ambient_bubble_main(struct MiscObj* self)
{
    ambient_bubble_step_funcs[self->unk5](self);
}

void ambient_bubble_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void ambient_bubble_update(struct MiscObj* self)
{
    ambient_bubble_state_funcs[self->state](self);
}

union AnimationStep ambient_bubble_anim_0[4] = {
    { 14, 0, 1, 0x00 },
    { 14, 0, 1, 0x01 },
    { 14, 0, 1, 0x02 },
    { 14, 0, -3, 0x01 },
};

union AnimationStep ambient_bubble_anim_1[3] = {
    { 14, 0, 1, 0x00 },
    { 14, 0, 1, 0x01 },
    { 14, 0, 0, 0x02 },
};

union AnimationStep ambient_bubble_anim_2[3] = {
    { 14, 0, 1, 0x02 },
    { 14, 0, 1, 0x01 },
    { 14, 0, 0, 0x00 },
};

union AnimationStep* ambient_bubble_animations[3] = {
    ambient_bubble_anim_0,
    ambient_bubble_anim_1,
    ambient_bubble_anim_2,
};

u16 ambient_bubble_positions[8] = {
    0x90,
    0x70,
    0xB0,
    0xD0,
    0x80,
    0xA0,
    0xC0,
    0xE0,
};

s32 ambient_bubble_speeds[4] = {
    -0x18000,
    -0x28000,
    -0x38000,
    -0x48000,
};

s32 ambient_bubble_accels[4] = {
    0x1000,
    0x1000,
    0x1000,
    0x1000,
};

s32 ambient_bubble_max_speeds[4] = {
    -0x18000,
    -0x10000,
    -0x8000,
    -0x4000,
};

u16 ambient_bubble_respawn_delays[4] = { 0xB4, 0x12C, 0x168, 0 };

void (*ambient_bubble_step_funcs[2])(struct MiscObj*) = {
    func_800CFC6C,
    ambient_bubble_float,
};

void (*ambient_bubble_state_funcs[3])(struct MiscObj*) = {
    func_800CFB70,
    ambient_bubble_main,
    ambient_bubble_despawn,
};
