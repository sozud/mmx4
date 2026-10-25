// MiscObj, misc_object_update_funcs[13]
// 800CA52C..800CA754
#include "common.h"
#include "main/misc/misc_13_stage_portrait.h"
#include "main/55C4.h"
#include "main/objects.h"

// stage_portrait_state_funcs
extern void (*stage_portrait_state_funcs[])(struct MiscObj*);

void stage_portrait_select(struct MiscObj*);
void stage_portrait_show(struct MiscObj*);
#include "weapon_resources.h"

// stage_portrait_init

extern union AnimationStep* stage_portrait_animations[1];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CA52C(struct MiscObj* self);
#endif

void func_800CA52C(struct MiscObj* self)
{
    self->unk42 = OBJECT_PALETTE_FROM_COLOR(0x0B);
    self->unk40 = OBJECT_STAGE_TEXTURE(1);
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[1];
    self->animation_table = (u32**)stage_portrait_animations;
    self->bg_offset = 0;
    self->unk15 = 0;
    self->unk16 = 1;
    if (self->unk2 == 0) {
        self->x_pos.val = 0xE40000;
        self->y_pos.val = 0x1880000;
        set_animation_frame(ANIMATED_OBJECT(self), 0, 1);
        self->unk7 = 1;
        self->state++;
    } else {
        self->x_pos.i.hi = 0x60;
        self->y_pos.i.hi = 0x180;
        set_animation_frame(ANIMATED_OBJECT(self), 0, 10);
        self->unk42 = OBJECT_PALETTE_FROM_COLOR(0x1F);
        self->state = 2;
    }
}

void stage_portrait_select(struct MiscObj* self)
{
    s32 temp_a0;
    s32 temp_v0;
    s32 var_a2;
    s32 var_v1;
    s8 stage;
    s8 engine_state;
    s8 animation;

    engine_state = engine_obj.unk3;
    if (engine_state != self->unk7) {
        animation = engine_state;
        self->unk7 = animation;
        if (engine_state >= 8) {
            animation = engine_obj.unk5F < 7U ? 8 : 9;
        }
        set_animation_frame(ANIMATED_OBJECT(self), 0,
            (s8)mission_stage_order[animation] - 1);
        stage = (s8)mission_stage_order[animation];
        temp_v0 = (stage - 1) << 1;
        temp_a0 = temp_v0 + 0xB;
        var_a2 = temp_a0;
        if (temp_a0 < 0) {
            var_a2 = temp_v0 + 0x1A;
        }
        var_v1 = stage + 4;
        temp_a0 -= (var_a2 >> 4) * 0x10;
        if (var_v1 < 0) {
            var_v1 = stage + 0xB;
        }
#ifdef MMX4_SATURN
        self->unk42 = OBJECT_PALETTE_FROM_COLOR((stage - 1) * 2 + 0xB);
#else
        self->unk42 = temp_a0 | (((var_v1 >> 3) + 0x1E0) << 6);
#endif
    }
    is_on_screen(BASE_OBJECT(self));
}

void stage_portrait_show(struct MiscObj* self)
{
    is_on_screen(BASE_OBJECT(self));
}

void stage_portrait_update(struct MiscObj* self)
{
    self->on_screen = 0;
    stage_portrait_state_funcs[self->state](self);
}

union AnimationStep stage_portrait_anim_0[12] = {
    { 30, 0, 1, 0x00 },
    { 30, 0, 1, 0x01 },
    { 30, 0, 1, 0x02 },
    { 30, 0, 1, 0x03 },
    { 30, 0, 1, 0x04 },
    { 30, 0, 1, 0x05 },
    { 30, 0, 1, 0x06 },
    { 30, 0, 1, 0x07 },
    { 30, 0, 1, 0x08 },
    { 30, 0, 1, 0x09 },
    { 30, 0, 1, 0x0A },
    { 30, 0, 1, 0x10 },
};

union AnimationStep* stage_portrait_animations[1] = { stage_portrait_anim_0 };

void (*stage_portrait_state_funcs[3])(struct MiscObj*) = {
    func_800CA52C,
    stage_portrait_select,
    stage_portrait_show,
};
