// MiscObj, misc_object_update_funcs[50]
// 800D1B44..800D1DC4
#include "common.h"
#include "main/misc/misc_50_cutscene_actor.h"
#include "main/55C4.h"
#include "main/objects.h"

// cutscene_actor_state_funcs
extern void (*cutscene_actor_state_funcs[])(struct MiscObj*);
void func_800D1B44(struct MiscObj*);
extern union AnimationStep* cutscene_actor_animations[];
void cutscene_actor_wait(struct MiscObj*);
void cutscene_actor_hold(struct MiscObj*);
void cutscene_actor_animate(struct MiscObj* arg0);
#include "weapon_resources.h"

// cutscene_actor_init
#ifdef MMX4_SATURN
#define ACTOR_CLUT 32
#define ACTOR_STILL_CLUT 28
#define ACTOR_LAYER 16
#define ACTOR_STILL_LAYER 17
#define ACTOR_STILL_X 136
#define ACTOR_STILL_Y 120
#define ACTOR_PALETTE_WORD 0x200
#define ACTOR_PALETTE_WORDS 64

void func_800D1B44(struct MiscObj* self)
{
    u16* palette;
    s32 i;

    if (self->unk2 != 0) {
        self->animation_table = (u32**)cutscene_actor_animations;
        self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[0];
        self->unk40 = OBJECT_STAGE_TEXTURE(0);
        self->unk42 = ACTOR_CLUT;
        palette = (u16*)SP_PALETTE + ACTOR_PALETTE_WORD;
        for (i = 0; i < ACTOR_PALETTE_WORDS; i++)
            palette[i] = 0;
        need_palette_load |= 1;
        set_animation(self, self->unk2 - 1);
        self->state = 1;
        self->unk16 = ACTOR_LAYER;
    } else {
        self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[1];
        self->unk40 = OBJECT_STAGE_TEXTURE(1);
        self->unk42 = ACTOR_STILL_CLUT;
        self->animation_step.fields.frame_index = 0;
        self->x_pos.i.hi = ACTOR_STILL_X;
        self->y_pos.i.hi = ACTOR_STILL_Y;
        self->state = 2;
        self->unk16 = ACTOR_STILL_LAYER;
    }
    self->bg_offset = -1;
    self->unk15 = 0;
    is_on_screen(BASE_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_50_cutscene_actor", func_800D1B44);
#endif

void cutscene_actor_wait(struct MiscObj* self)
{
    if (engine_obj.unk2 == 7) {
        self->state = 3;
        self->unk42 = OBJECT_CLUT(0x7848);
    }
    is_on_screen(BASE_OBJECT(self));
}

void cutscene_actor_hold(struct MiscObj* self)
{
    is_on_screen(BASE_OBJECT(self));
}

void cutscene_actor_animate(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void cutscene_actor_update(struct MiscObj* self)
{
    self->on_screen = 0;
    cutscene_actor_state_funcs[self->state](self);
}

union AnimationStep cutscene_actor_anim_0[18] = {
    { 30, 0, 1, 0x10 },
    { 4, 0, 1, 0x01 },
    { 4, 0, 1, 0x02 },
    { 5, 0, 1, 0x11 },
    { 8, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x2B },
    { 3, 0, 1, 0x2C },
    { 12, 0, 1, 0x32 },
    { 2, 0, 1, 0x2E },
    { 29, 0, 1, 0x2F },
    { 1, 0, 0, 0x2F },
};

union AnimationStep cutscene_actor_anim_1[49] = {
    { 30, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x15 },
    { 10, 0, 1, 0x16 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 8, 0, 1, 0x17 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x15 },
    { 10, 0, 1, 0x16 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 8, 0, 1, 0x17 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 18, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 29, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep cutscene_actor_anim_2[19] = {
    { 30, 0, 1, 0x02 },
    { 4, 0, 1, 0x00 },
    { 24, 0, 1, 0x4D },
    { 8, 0, 1, 0x4E },
    { 2, 0, 1, 0x4D },
    { 2, 0, 1, 0x82 },
    { 2, 0, 1, 0x83 },
    { 3, 0, 1, 0x84 },
    { 3, 0, 1, 0x85 },
    { 3, 0, 1, 0x86 },
    { 3, 0, 1, 0x87 },
    { 4, 0, 1, 0x88 },
    { 4, 0, 1, 0x89 },
    { 4, 0, 1, 0x8A },
    { 4, 0, 1, 0x8B },
    { 2, 0, 1, 0x50 },
    { 2, 0, 1, 0x01 },
    { 29, 0, 1, 0x02 },
    { 1, 0, 0, 0x02 },
};

union AnimationStep cutscene_actor_anim_3[30] = {
    { 30, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x20 },
    { 15, 0, 1, 0x21 },
    { 3, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x2C },
    { 2, 0, 1, 0x27 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x2C },
    { 20, 0, 1, 0x27 },
    { 3, 0, 1, 0x03 },
    { 3, 0, 1, 0x01 },
    { 15, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 29, 0, 1, 0x5B },
    { 1, 0, 0, 0x5B },
};

union AnimationStep cutscene_actor_anim_4[11] = {
    { 30, 0, 1, 0x01 },
    { 8, 0, 1, 0x08 },
    { 3, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 8, 0, 1, 0x0B },
    { 4, 0, 1, 0x0C },
    { 6, 0, 1, 0x66 },
    { 2, 0, 1, 0x55 },
    { 2, 0, 1, 0x56 },
    { 29, 0, 1, 0x57 },
    { 1, 0, 0, 0x57 },
};

union AnimationStep cutscene_actor_anim_5[12] = {
    { 30, 0, 1, 0x00 },
    { 7, 0, 1, 0x35 },
    { 7, 0, 1, 0x36 },
    { 10, 0, 1, 0x37 },
    { 3, 0, 1, 0x36 },
    { 3, 0, 1, 0x35 },
    { 14, 0, 1, 0x93 },
    { 25, 0, 1, 0x2D },
    { 20, 0, 1, 0x05 },
    { 3, 0, 1, 0x2E },
    { 29, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep cutscene_actor_anim_6[13] = {
    { 30, 0, 1, 0x06 },
    { 2, 0, 1, 0x5A },
    { 2, 0, 1, 0x5B },
    { 24, 0, 1, 0x5A },
    { 8, 0, 1, 0x5C },
    { 8, 0, 1, 0x5D },
    { 8, 0, 1, 0x5E },
    { 11, 0, 1, 0x5F },
    { 2, 0, 1, 0x60 },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x60 },
    { 29, 0, 1, 0x61 },
    { 1, 0, 0, 0x61 },
};

union AnimationStep cutscene_actor_anim_7[16] = {
    { 30, 0, 1, 0x7D },
    { 2, 0, 1, 0x7E },
    { 10, 0, 1, 0x7F },
    { 2, 0, 1, 0x7E },
    { 1, 0, 1, 0x80 },
    { 1, 0, 1, 0x81 },
    { 1, 0, 1, 0x80 },
    { 1, 0, 1, 0x81 },
    { 1, 0, 1, 0x80 },
    { 30, 0, 1, 0x81 },
    { 2, 0, 1, 0x80 },
    { 2, 0, 1, 0x82 },
    { 10, 0, 1, 0x83 },
    { 2, 0, 1, 0x82 },
    { 29, 0, 1, 0x84 },
    { 1, 0, 0, 0x84 },
};

union AnimationStep* cutscene_actor_animations[8] = {
    cutscene_actor_anim_0,
    cutscene_actor_anim_1,
    cutscene_actor_anim_2,
    cutscene_actor_anim_3,
    cutscene_actor_anim_4,
    cutscene_actor_anim_5,
    cutscene_actor_anim_6,
    cutscene_actor_anim_7,
};

void (*cutscene_actor_state_funcs[4])(struct MiscObj*) = {
    func_800D1B44,
    cutscene_actor_wait,
    cutscene_actor_hold,
    cutscene_actor_animate,
};
