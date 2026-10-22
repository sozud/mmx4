// MiscObj, misc_object_update_funcs[34]
// 800CE894..800CF144
#include "common.h"
#include "main/misc/misc_34_cyberspace_guide.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

void cyberspace_guide_update_blink(struct MiscObj*);

// cyberspace_guide_state_funcs
extern void (*cyberspace_guide_state_funcs[])(struct MiscObj*);
void func_800CE8DC(struct MiscObj*);
void cyberspace_guide_main(struct MiscObj*);
void cyberspace_guide_despawn(struct MiscObj*);

// cyberspace_guide_step_funcs
extern void (*cyberspace_guide_step_funcs[])(struct MiscObj*);
void cyberspace_guide_appear(struct MiscObj*);
void cyberspace_guide_start_timer(struct MiscObj*);

void cyberspace_guide_leave(struct MiscObj*);

// cyberspace_guide_leave_funcs
extern void (*cyberspace_guide_leave_funcs[])(struct MiscObj*);
void cyberspace_guide_leave_start(struct MiscObj*);
void cyberspace_guide_leave_drift(struct MiscObj*);
void cyberspace_guide_leave_finish(struct MiscObj*);
#include "weapon_resources.h"

extern union AnimationStep* cyberspace_guide_animations[5];

void cyberspace_guide_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    cyberspace_guide_state_funcs[self->state](self);
}

// cyberspace_guide_init
void func_800CE8DC(struct MiscObj* self)
{
    s32 resource;
    u16 y_pos;

    self->unk16 = 2;
    self->unk15 = 0;
    self->bg_offset = g_Player.bg_offset;
    self->animation_table = (u32**)cyberspace_guide_animations;
    resource = func_8002938C(0x90);
    self->unk40 = OBJECT_STAGE_TEXTURE(resource);
    resource = func_8002938C(0x90);
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    self->unk42 = OBJECT_STAGE_CLUT(0x90);
    self->x_pos.u.hi = g_Player.x_pos.u.hi;
    y_pos = g_Player.y_pos.u.hi;
    self->state = 1;
    self->unk5 = 0;
    self->unk6 = 0;
#ifdef MMX4_PC
    self->ext.misc_34.timer = 0;
    self->ext.misc_34.unk55 = 0;
    self->ext.misc_34.variant = 0;
    self->ext.misc_34.unk57 = 0;
    self->ext.misc_34.unk58 = 0;
    self->ext.misc_34.enabled = 0;
    self->ext.misc_34.unk5A = 0;
    self->ext.misc_34.unk5C = 0;
    self->ext.misc_34.unk5D = 0;
    self->ext.misc_34.timer = 0x24;
#else
    self->ext.tail.bytes[0] = 0;
    self->ext.tail.bytes[1] = 0;
    self->ext.tail.bytes[2] = 0;
    self->ext.tail.bytes[3] = 0;
    self->ext.tail.bytes[4] = 0;
    self->ext.tail.bytes[5] = 0;
    self->ext.tail.bytes[6] = 0;
    self->ext.tail.bytes[7] = 0;
    self->ext.tail.bytes[8] = 0;
    self->ext.tail.bytes[9] = 0;
    self->ext.tail.bytes[0] = 0x24;
#endif
    self->y_pos.u.hi = y_pos;
    set_animation(self, 0);
    func_8001540C(2, SATURN_SOUND(0xE9, 0xAA), self);
}

void cyberspace_guide_main(struct MiscObj* self)
{
    cyberspace_guide_step_funcs[self->unk5](self);
    func_800CEFC0(self);
    cyberspace_guide_update_blink(self);
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state++;
    }
}

void cyberspace_guide_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void cyberspace_guide_appear(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.misc_34.timer == 0) {
        self->ext.misc_34.timer = 0x24;
        self->unk5 = 1;
        set_animation(self, 2);
    }
}

void cyberspace_guide_start_timer(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.misc_34.timer == 0) {
        engine_obj.unk10 = 0;
        engine_obj.unk12 = 0;
        engine_obj.unk11 = 0;
        engine_obj.unk13 = 0;
        self->unk5 = 2;
        self->ext.misc_34.enabled = 1;
        set_animation(self, 1);
    }
}

// cyberspace_guide_follow

#if defined(MMX4_PC) || defined(MMX4_SATURN)
static void misc_34_track_axis(f32* position, s32 target, s16 target_hi);
void func_800CEBC0(struct MiscObj* arg0);
void func_800CEFC0(struct MiscObj* arg0);
extern u8 cyberspace_guide_offsets[12];
static void misc_34_track_axis(f32* position, s32 target, s16 target_hi)
{
    s32 delta = target - position->val;

    if (delta < 0)
        delta = -delta;
    if (delta <= 0x1FFFFF)
        return;
    position->i.hi = target < position->val ? target_hi + 0x20 : target_hi - 0x20;
}
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CEBC0(struct MiscObj* arg0)
{
    struct EffectObj* related = arg0->ext.misc_34.related;
    s32 dx;
    s32 dy;

    animate_object(ANIMATED_OBJECT(arg0));
    set_velocity_from_angle(MOVING_OBJECT(arg0),
        (u8)angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)));
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->x_vel.val *= 4;
    arg0->y_vel.val *= 3;
    misc_34_track_axis(&arg0->x_pos, g_Player.x_pos.val, g_Player.x_pos.i.hi);
    misc_34_track_axis(&arg0->y_pos, g_Player.y_pos.val, g_Player.y_pos.i.hi);
    dx = g_Player.x_pos.val - arg0->x_pos.val;
    if (dx < 0)
        dx = -dx;
    dy = g_Player.y_pos.val - arg0->y_pos.val;
    if (dy < 0)
        dy = -dy;
    if (dx > 0x20000 || dy > 0x20000) {
        move_with_gravity(ANIMATED_OBJECT(arg0));
    } else {
        arg0->x_pos.val = g_Player.x_pos.val;
        arg0->y_pos.val = g_Player.y_pos.val;
    }
    if (related->state >= 3)
        arg0->ext.misc_34.enabled = 1;
    if (related->state >= 4)
        arg0->unk5 = 3;
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_34_cyberspace_guide", func_800CEBC0);
#endif

void cyberspace_guide_leave(struct MiscObj* self)
{
    cyberspace_guide_leave_funcs[self->unk6](self);
}

void cyberspace_guide_leave_start(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 4);
    self->y_vel.val = FIXED(1);
    self->ext.misc_34.enabled = 0;
    self->x_vel.val = 0;
    self->ext.misc_34.timer = 0x1E;
    self->unk6++;
}

void cyberspace_guide_leave_drift(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (--self->ext.misc_34.timer == 0) {
        self->ext.misc_34.timer = 0x1E;
        self->x_vel.val = FIXED(3);
        self->y_vel.val = 0;
        self->unk28 = FIXED(-0.0625);
        self->unk6++;
    }
}

void cyberspace_guide_leave_finish(struct MiscObj* self)
{
    struct EffectObj* related;

    move_with_gravity(ANIMATED_OBJECT(self));
    if (--self->ext.misc_34.timer == 0) {
        related = self->ext.misc_34.related;
        related->ext.effect_38.active = 1;
        if (!(engine_obj.checkpoint % 2)) {
            related->ext.effect_38.variant = self->ext.misc_34.variant;
        } else {
            related->ext.effect_38.variant = 3;
        }
        self->state++;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

// cyberspace_guide_update_position
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CEFC0(struct MiscObj* arg0)
{
    struct Misc34Ext* ext = &arg0->ext.misc_34;
    u8 limit;
    u8 counter;

    if (ext->enabled == 0 || ext->variant == 2)
        return;
    limit = cyberspace_guide_offsets[engine_obj.checkpoint * 2 + ext->variant];
    counter = ext->unk58;
    ext->unk58 = counter + 1;
    if (counter >= 0x3C) {
        if (++ext->unk57 == limit - 3 && arg0->unk17 != 3) {
            set_animation(arg0, 2);
            ext->unk5A = 0xB4;
        }
        ext->unk58 = 0;
    }
    if (ext->unk57 >= limit) {
        ext->variant = ext->variant == 0 ? 1 : 2;
        ext->unk57 = 0;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_34_cyberspace_guide", func_800CEFC0);
#endif

void cyberspace_guide_update_blink(struct MiscObj* self)
{
    if ((self->unk17 != 1) && (self->unk17 != 4)) {
        if (--self->ext.misc_34.unk5A == 0) {
            if (self->unk17 == 2) {
                set_animation(self, 3);
                self->ext.misc_34.enabled = 0;
                self->ext.misc_34.unk5A = 0x24;
            } else {
                set_animation(self, 1);
                self->ext.misc_34.enabled = 1;
            }
        }
    }
}

union AnimationStep cyberspace_guide_anim_0[6] = {
    { 6, 0, 1, 0x1B },
    { 6, 0, 1, 0x1C },
    { 6, 0, 1, 0x1D },
    { 6, 0, 1, 0x00 },
    { 6, 0, 1, 0x01 },
    { 6, 0, 0, 0x02 },
};

union AnimationStep cyberspace_guide_anim_1[24] = {
    { 6, 0, 1, 0x03 },
    { 6, 0, 1, 0x04 },
    { 6, 0, 1, 0x05 },
    { 3, 0, 1, 0x06 },
    { 3, 0, 1, 0x07 },
    { 3, 0, 1, 0x08 },
    { 3, 0, 1, 0x09 },
    { 3, 0, 1, 0x0A },
    { 3, 0, 1, 0x0B },
    { 6, 0, 1, 0x0C },
    { 6, 0, 1, 0x0D },
    { 6, 0, 1, 0x0E },
    { 6, 0, 1, 0x0F },
    { 6, 0, 1, 0x10 },
    { 6, 0, 1, 0x11 },
    { 6, 0, 1, 0x18 },
    { 6, 0, 1, 0x19 },
    { 6, 0, 1, 0x1A },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x14 },
    { 3, 0, 1, 0x15 },
    { 3, 0, 1, 0x16 },
    { 3, 0, -23, 0x17 },
};

union AnimationStep cyberspace_guide_anim_2[6] = {
    { 3, 0, 1, 0x1E },
    { 3, 0, 1, 0x1F },
    { 3, 0, 1, 0x20 },
    { 3, 0, 1, 0x21 },
    { 3, 0, 1, 0x22 },
    { 3, 0, -5, 0x23 },
};

union AnimationStep cyberspace_guide_anim_3[6] = {
    { 3, 0, 1, 0x24 },
    { 3, 0, 1, 0x25 },
    { 3, 0, 1, 0x26 },
    { 3, 0, 1, 0x27 },
    { 3, 0, 1, 0x28 },
    { 3, 0, -5, 0x29 },
};

union AnimationStep cyberspace_guide_anim_4[6] = {
    { 6, 0, 1, 0x02 },
    { 6, 0, 1, 0x01 },
    { 6, 0, 1, 0x00 },
    { 6, 0, 1, 0x1D },
    { 6, 0, 1, 0x1C },
    { 6, 0, 0, 0x1B },
};

union AnimationStep* cyberspace_guide_animations[5] = {
    cyberspace_guide_anim_0,
    cyberspace_guide_anim_1,
    cyberspace_guide_anim_2,
    cyberspace_guide_anim_3,
    cyberspace_guide_anim_4,
};

#undef STEP

u8 cyberspace_guide_offsets[12] = {
    0x0F,
    0x0F,
    0,
    0,
    0x12,
    0x11,
    0,
    0,
    0x23,
    0x2C,
    0,
    0,
};

void (*cyberspace_guide_state_funcs[3])(struct MiscObj*) = {
    func_800CE8DC,
    cyberspace_guide_main,
    cyberspace_guide_despawn,
};

void (*cyberspace_guide_step_funcs[4])(struct MiscObj*) = {
    cyberspace_guide_appear,
    cyberspace_guide_start_timer,
    func_800CEBC0,
    cyberspace_guide_leave,
};

void (*cyberspace_guide_leave_funcs[3])(struct MiscObj*) = {
    cyberspace_guide_leave_start,
    cyberspace_guide_leave_drift,
    cyberspace_guide_leave_finish,
};
