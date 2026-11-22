// MiscObj, misc_object_update_funcs[15]
// 800CA86C..800CA9EC
#include "common.h"
#include "main/misc/misc_15_vent.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/55C4.h"

// vent_state_funcs
extern void (*vent_state_funcs[])(struct MiscObj*);

void vent_animate(struct MiscObj*);
#include "weapon_resources.h"

// vent_init

extern union AnimationStep* vent_animations[2];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CA86C(struct MiscObj* self);
#endif

void func_800CA86C(struct MiscObj* self)
{
    s8 animation;

    self->unk42 = OBJECT_CLUT(0x7881);
    self->unk40 = OBJECT_STAGE_TEXTURE(4);
    self->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
    self->animation_table = (u32**)vent_animations;
    self->x_pos.val = 0x7C0000;
    self->y_pos.val = 0x1880000;
    self->bg_offset = 0;
    self->unk15 = 0;
    if (self->unk2 == 0) {
        set_animation(self, 0);
        self->unk16 = 2;
    } else {
#ifdef VERSION_DEMO
        set_animation(self, 1);
#else
        animation = engine_obj.unk5F < 5 ? 0 : (engine_obj.unk5F < 7 ? 1 : 2);
        set_animation_frame(ANIMATED_OBJECT(self), 1, animation);
#endif
        self->unk16 = 1;
    }
    self->state++;
    is_on_screen(BASE_OBJECT(self));
}

void vent_animate(struct MiscObj* self)
{
    self->on_screen = 0;
#ifdef VERSION_DEMO
    if (self->unk2 != 0) {
        self->unk6++;
    } else if (!(self->unk6++ & 1)) {
        return;
    }
#else
    if (self->unk2 == 0) {
        if (!(self->unk6++ & 1)) {
            return;
        }
    }
#endif
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void vent_update(struct MiscObj* self)
{
    vent_state_funcs[self->state](self);
}

union AnimationStep vent_anim_0[4] = {
    { 6, 0, 1, 0x00 },
    { 6, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 1, 0, -3, 0x02 },
};

#ifdef VERSION_DEMO
union AnimationStep vent_anim_1[1] = {
    { 1, 0, 0, 0x03 },
};
#else
union AnimationStep vent_anim_1[3] = {
    { 1, 0, 0, 0x03 },
    { 1, 0, 0, 0x05 },
    { 1, 0, 0, 0x04 },
};
#endif

union AnimationStep* vent_animations[2] = { vent_anim_0, vent_anim_1 };

void (*vent_state_funcs[2])(struct MiscObj*) = {
    func_800CA86C,
    vent_animate,
};
