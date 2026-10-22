// EffectObj, effect_object_update_funcs[18]
// 800B9690..800B9940
#include "common.h"
#include "main/effects/effect_18_world_flip.h"
#include "main/objects.h"

// world_flip_state_funcs
extern void (*world_flip_state_funcs[])(struct EffectObj*);
void world_flip_init(struct EffectObj*);

void world_flip_despawn(struct EffectObj*);

void world_flip_objects(void);

void world_flip_update(struct EffectObj* self)
{
    world_flip_state_funcs[self->state](self);
}

void world_flip_init(struct EffectObj* self)
{
    self->state++;
}

// world_flip_trigger
#ifdef MMX4_PC
void func_800B96E0(struct EffectObj* self);
#endif

#ifdef MMX4_PC
// src/main/effects/effect_18_world_flip.c

void func_800B96E0(struct EffectObj* self)
{
    (void)self;
    if (g_Player.pressed_input & 0x20) {
        background_objects[0].unk4C = 1;
        background_objects[1].unk4C = 1;
        background_objects[2].unk4C = 1;
        g_Player.y_pos.val = (s32)(0x08000000u - (u32)g_Player.y_pos.val);
        background_objects[0].y_pos.val = (s32)(0x07000000u - (u32)background_objects[0].y_pos.val);
        background_objects[0].unk18.val = (s32)(0x07000000u - (u32)background_objects[0].unk18.val);
        background_objects[1].y_pos.val = background_objects[0].y_pos.val >> 2;
        background_objects[2].y_pos.val = background_objects[0].y_pos.val >> 2;
        background_objects[1].unk18.val = background_objects[0].unk18.val >> 2;
        background_objects[2].unk18.val = background_objects[0].unk18.val >> 2;
        world_flip_objects();
        engine_obj.character_state.bytes[0] = (u8)(1 - engine_obj.character_state.bytes[0]);
    }
}
#else
INCLUDE_ASM("main/nonmatchings/effects/effect_18_world_flip", func_800B96E0);
#endif

void world_flip_despawn(struct EffectObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void world_flip_objects(void)
{
    u32 i;
    struct MainObj* p1;
    struct MiscObj* p2;
    struct WeaponObj* p3;
    struct ShotObj* p4;
    struct VisualObj* p5;

    p1 = main_objects;
    for (i = 0; i < COUNT(main_objects); p1++, i++) {
        if (p1->active != 0) {
            p1->y_pos.val = FIXED(0x800) - p1->y_pos.val;
        }
    }
    p2 = misc_objects;
    for (i = 0; i < COUNT(misc_objects); p2++, i++) {
        if (p2->active != 0) {
            p2->y_pos.val = FIXED(0x800) - p2->y_pos.val;
        }
    }
    p3 = weapon_objects;
    for (i = 0; i < COUNT(weapon_objects); p3++, i++) {
        if (p3->active != 0) {
            p3->y_pos.val = FIXED(0x800) - p3->y_pos.val;
        }
    }
    p4 = shot_objects;
    for (i = 0; i < COUNT(shot_objects); p4++, i++) {
        if (p4->active != 0) {
            p4->y_pos.val = FIXED(0x800) - p4->y_pos.val;
        }
    }
    p5 = visual_objects;
    for (i = 0; i < COUNT(visual_objects); p5++, i++) {
        if (p5->active != 0) {
            p5->y_pos.val = FIXED(0x800) - p5->y_pos.val;
        }
    }
}

void (*world_flip_state_funcs[])(struct EffectObj*) = {
    world_flip_init,
    func_800B96E0,
    world_flip_despawn,
};
