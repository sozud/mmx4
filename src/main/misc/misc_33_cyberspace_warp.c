// MiscObj, misc_object_update_funcs[33]
// 800CE340..800CE894
#include "common.h"
#include "main/misc/misc_33_cyberspace_warp.h"
#include "main/55C4.h"
#include "main/objects.h"

// cyberspace_warp_state_funcs
extern void (*cyberspace_warp_state_funcs[])(struct MiscObj*);

void cyberspace_warp_main(struct MiscObj*);
void cyberspace_warp_despawn(struct MiscObj*);

// cyberspace_warp_main_funcs
extern void (*cyberspace_warp_main_funcs[])(struct MiscObj*);
void cyberspace_warp_fade(struct MiscObj*);
void cyberspace_warp_wait(struct MiscObj*);

// cyberspace_warp_wait_funcs
extern void (*cyberspace_warp_wait_funcs[])(struct MiscObj*);
void cyberspace_warp_wait_start(struct MiscObj*);
void cyberspace_warp_wait_blink(struct MiscObj*);
#include "weapon_resources.h"

void cyberspace_warp_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    cyberspace_warp_state_funcs[self->state](self);
}

// cyberspace_warp_init
struct Misc33Position {
    s16 x;
    s16 y;
};

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CE388(struct MiscObj* arg0);
extern union AnimationStep* cyberspace_warp_animations[5];
extern struct Misc33Position cyberspace_warp_positions[6];
extern struct Misc33Position cyberspace_warp_exit_position;
extern ret_u8 func_8002938C(s32);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CE388(struct MiscObj* arg0)
{
    s32 resource;

    arg0->unk16 = 2;
    arg0->unk15 = 0;
    arg0->animation_table = (u32**)cyberspace_warp_animations;
    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(0x9B);
    arg0->unk40 = OBJECT_STAGE_TEXTURE(resource);
    resource = func_8002938C(0x9B);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk42 = OBJECT_STAGE_CLUT(0x9B);
    arg0->x_pos.i.hi = g_Player.x_pos.i.hi;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi;
    switch ((u32)arg0->unk2) {
    case 0:
        set_animation(arg0, 0);
        arg0->ext.misc_33.timer = 0x48;
        arg0->unk5 = 0;
        arg0->unk16 = VISUAL_SATURN_LAYER(6);
        break;
    case 1:
        set_animation(arg0, 1);
        arg0->ext.misc_33.timer = 0x48;
        arg0->unk5 = 0;
        arg0->unk16 = 0x11;
        break;
    case 2:
    case 3:
    case 4:
        set_animation(arg0, arg0->unk2);
        arg0->unk5 = 1;
        arg0->unk16 = 0x10;
        break;
    }
    if (engine_obj.substage != 0) {
        arg0->x_pos.i.hi = ((s16*)&cyberspace_warp_exit_position)[0];
        arg0->y_pos.i.hi = ((s16*)&cyberspace_warp_exit_position)[1];
    } else if (arg0->unk2 >= 2) {
        arg0->x_pos.i.hi = ((s16(*)[2])cyberspace_warp_positions)[engine_obj.checkpoint][0];
        arg0->y_pos.i.hi = ((s16(*)[2])cyberspace_warp_positions)[engine_obj.checkpoint][1];
    } else {
        arg0->x_pos.i.hi = ((s16(*)[2])cyberspace_warp_positions)[engine_obj.checkpoint][0] - 0xA;
        arg0->y_pos.i.hi = ((s16(*)[2])cyberspace_warp_positions)[engine_obj.checkpoint][1] + 0x30;
    }
    arg0->state = 1;
    arg0->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_33_cyberspace_warp", func_800CE388);
#endif

void cyberspace_warp_main(struct MiscObj* self)
{
    cyberspace_warp_main_funcs[self->unk5](self);
}

void cyberspace_warp_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void cyberspace_warp_fade(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.misc_33.timer == 0) {
        self->state++;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state++;
}

void cyberspace_warp_wait(struct MiscObj* self)
{
    cyberspace_warp_wait_funcs[self->unk6](self);
    if (*self->ext.misc_33.completion_flag == 0) {
        self->state++;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void cyberspace_warp_wait_start(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->ext.misc_33.timer = 0x14;
    self->unk6 += 1;
    func_8001540C(2, SATURN_SOUND(0xE8, 0xA9), self);
    is_on_screen(BASE_OBJECT(self));
}

void cyberspace_warp_wait_blink(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->ext.misc_33.timer != 0) {
        if (FLICKER_ENABLED) {
            self->on_screen ^= 1;
        }
        if (self->on_screen != 0) {
            update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        }
        self->ext.misc_33.timer--;
    } else {
        is_on_screen(BASE_OBJECT(self));
    }
}

union AnimationStep cyberspace_warp_anim_0[24] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x03 },
    { 3, 0, 1, 0x05 },
    { 3, 0, 1, 0x07 },
    { 3, 0, 1, 0x09 },
    { 3, 0, 1, 0x0B },
    { 3, 0, 1, 0x0D },
    { 3, 0, 1, 0x0F },
    { 3, 0, 1, 0x11 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x15 },
    { 3, 0, 1, 0x17 },
    { 3, 0, 1, 0x19 },
    { 3, 0, 1, 0x1B },
    { 3, 0, 1, 0x1D },
    { 3, 0, 1, 0x1F },
    { 3, 0, 1, 0x21 },
    { 3, 0, 1, 0x23 },
    { 3, 0, 1, 0x25 },
    { 3, 0, 1, 0x27 },
    { 3, 0, 1, 0x29 },
    { 3, 0, 1, 0x2B },
    { 3, 0, 0, 0x2D },
};

union AnimationStep cyberspace_warp_anim_1[24] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x04 },
    { 3, 0, 1, 0x06 },
    { 3, 0, 1, 0x08 },
    { 3, 0, 1, 0x0A },
    { 3, 0, 1, 0x0C },
    { 3, 0, 1, 0x0E },
    { 3, 0, 1, 0x10 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x14 },
    { 3, 0, 1, 0x16 },
    { 3, 0, 1, 0x18 },
    { 3, 0, 1, 0x1A },
    { 3, 0, 1, 0x1C },
    { 3, 0, 1, 0x1E },
    { 3, 0, 1, 0x20 },
    { 3, 0, 1, 0x22 },
    { 3, 0, 1, 0x24 },
    { 3, 0, 1, 0x26 },
    { 3, 0, 1, 0x28 },
    { 3, 0, 1, 0x2A },
    { 3, 0, 1, 0x2C },
    { 3, 0, 0, 0x2E },
};

union AnimationStep cyberspace_warp_anim_2[1] = { { 8, 0, 0, 0x2F } };
union AnimationStep cyberspace_warp_anim_3[1] = { { 8, 0, 0, 0x30 } };
union AnimationStep cyberspace_warp_anim_4[1] = { { 8, 0, 0, 0x31 } };

union AnimationStep* cyberspace_warp_animations[5] = {
    cyberspace_warp_anim_0,
    cyberspace_warp_anim_1,
    cyberspace_warp_anim_2,
    cyberspace_warp_anim_3,
    cyberspace_warp_anim_4,
};

#undef STEP

struct Misc33Position cyberspace_warp_positions[6] = {
    { 0x778, 0x60 },
    { 0x378, 0x360 },
    { 0x878, 0x260 },
    { 0x378, 0x360 },
    { 0xC78, 0x560 },
    { 0x378, 0x360 },
};

struct Misc33Position cyberspace_warp_exit_position = { 0xFF0, 0x290 };

void (*cyberspace_warp_state_funcs[3])(struct MiscObj*) = {
    func_800CE388,
    cyberspace_warp_main,
    cyberspace_warp_despawn,
};

void (*cyberspace_warp_main_funcs[2])(struct MiscObj*) = {
    cyberspace_warp_fade,
    cyberspace_warp_wait,
};

void (*cyberspace_warp_wait_funcs[2])(struct MiscObj*) = {
    cyberspace_warp_wait_start,
    cyberspace_warp_wait_blink,
};
