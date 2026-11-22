// VisualObj, visual_object_update_funcs[4]
// 800AF808..800AFC9C
#include "common.h"
#include "main/visuals/visual_04_blast.h"
#include "main/55C4.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "weapon_resources.h"
extern u8* blast_animations[1];

void blast_animate(struct VisualObj* arg0);
void func_800AFB90(struct VisualObj* arg0);

u8 blast_anim_0[19][4] = {
    { 1, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 2, 0, 1, 4 },
    { 2, 0, 1, 5 },
    { 2, 0, 1, 6 },
    { 2, 0, 1, 7 },
    { 2, 0, 1, 8 },
    { 2, 0, 1, 9 },
    { 2, 0, 1, 10 },
    { 2, 0, 1, 11 },
    { 2, 0, 1, 12 },
    { 3, 0, 1, 13 },
    { 3, 0, 1, 14 },
    { 4, 0, 1, 15 },
    { 5, 0, 1, 16 },
    { 6, 0, 1, 17 },
    { 0x60, 0, 0xFF, 17 },
};

u8* blast_animations[1] = { blast_anim_0 };

extern u8 D_8013B8E0;
extern u8 D_8013B8E4;

void spawn_explosion(struct BaseObj* arg0)
{
    spawn_explosion_variant(arg0, 0);
}

void spawn_explosion_variant(struct BaseObj* arg0, s8 arg1)
{
    spawn_explosion_at(arg1, arg0->x_pos.i.hi, arg0->y_pos.i.hi, (get_random() & 1) ^ 1);
}

// spawn_random_explosion

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800AF95C(struct ObjectHeader* arg0, s32 type, s32 x_range, s32 y_range, s32 divisor);
#endif

void func_800AF878(void* arg0, s8 arg1, s32 arg2, s32 arg3)
{
    struct BaseObj* obj = arg0;
    s16 x;
    s16 y;
    u8 toggle;

    arg2 &= get_random();
    if (get_random() & 1)
        x = obj->x_pos.i.hi + (arg2 & 0xFF);
    else
        x = obj->x_pos.i.hi - (arg2 & 0xFF);
    arg3 &= get_random();
    if (get_random() & 1)
        y = obj->y_pos.i.hi + (arg3 & 0xFF);
    else
        y = obj->y_pos.i.hi - (arg3 & 0xFF);
    toggle = D_8013B8E0 + 1;
    D_8013B8E0 = toggle;
    spawn_explosion_at(arg1, x, y, (toggle & 1) ^ 1);
}

// spawn_explosion_in_box
#ifdef MMX4_SATURN
void func_800AF95C(struct ObjectHeader* arg0, s32 type, s32 x_range, s32 y_range, s32 divisor)
{
    s16 x;
    s16 y;
    s32 roll;
    u8 variant;

    x_range &= get_random();
    if (get_random() & 1)
        x = arg0->x_pos.i.hi + (x_range & 0xFF);
    else
        x = arg0->x_pos.i.hi - (x_range & 0xFF);
    y_range &= get_random();
    if (get_random() & 1)
        y = arg0->y_pos.i.hi + (y_range & 0xFF);
    else
        y = arg0->y_pos.i.hi - (y_range & 0xFF);
    roll = get_random_nonzero();
    divisor &= 0xFF;
    if (divisor == 0 || roll % divisor == 0) {
        D_8013B8E4++;
        variant = (D_8013B8E4 & 1) ? 2 : 3;
    } else {
        variant = 0xFF;
    }
    spawn_explosion_at((s8)type, x, y, variant);
}
#else
// clang-format off
void func_800AF95C(arg0, type, x_range, y_range, divisor)
    struct ObjectHeader* arg0;
    s8 type;
    s32 x_range;
    s32 y_range;
    u8 divisor;
// clang-format on
{
    struct ObjectHeader* obj = arg0;
    s16 x;
    s16 y;
    s32 roll;
    u8 variant;
    u8 toggle;

    x_range &= get_random();
    if (get_random() & 1)
        x = obj->x_pos.i.hi + (x_range & 0xFF);
    else
        x = obj->x_pos.i.hi - (x_range & 0xFF);
    y_range &= get_random();
    if (get_random() & 1)
        y = obj->y_pos.i.hi + (y_range & 0xFF);
    else
        y = obj->y_pos.i.hi - (y_range & 0xFF);
    roll = get_random_nonzero();
    if (divisor == 0 || roll % divisor == 0) {
        toggle = D_8013B8E4 + 1;
        D_8013B8E4 = toggle;
        variant = (toggle & 1) ? 2 : 3;
    } else {
        variant = 0xFF;
    }
    spawn_explosion_at(type, x, y, variant);
}
#endif

struct VisualObj* spawn_explosion_at(s8 arg0, s16 x, s16 y, u8 arg3)
{
    struct VisualObj* visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x21;
        visual->id = 4;
        visual->unk2 = arg0;
        visual->state = 0;
        visual->unk5 = 0;
        visual->unk6 = 0;
        visual->unk5C.value = arg3;
        visual->x_pos.i.hi = x;
        visual->x_pos.i.lo = 0;
        visual->y_pos.i.hi = y;
        visual->y_pos.i.lo = 0;
        visual->unk15 = 0;
        visual->bg_offset = 0;
        visual->unk16 = VISUAL_SATURN_LAYER(1);
    }
    return visual;
}

void blast_update(struct VisualObj* arg0)
{
    if (arg0->state == 0) {
        func_800AFB90(arg0);
    } else {
        blast_animate(arg0);
    }
}

// blast_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800AFB90(struct VisualObj* arg0);
#endif

void func_800AFB90(struct VisualObj* arg0)
{
    s32 clut = arg0->unk2 + 4;

    arg0->on_screen = 1;
    arg0->unk38 = NULL;
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 2);
    arg0->animation_table = (u32**)blast_animations;
    arg0->unk40 = WEAPON_TEXTURE_BASE;
#ifdef MMX4_SATURN
    arg0->unk42 = (u8)(arg0->unk2 + 4);
#else
    arg0->unk42 = (clut % 16) | ((clut / 16 + 0x1E0) << 6);
#endif
    set_animation(arg0, 0);
    if ((u8)arg0->unk5C.value != 0xFF) {
        func_8001540C(0, (u8)arg0->unk5C.value, arg0);
    }
    arg0->state++;
    is_on_screen(BASE_OBJECT(arg0));
}

void blast_animate(struct VisualObj* arg0)
{
    animate_object(arg0);
    if (arg0->animation_step.fields.relative_step < 0) {
        ZeroObjectState(arg0);
    } else {
        is_on_screen(arg0);
    }
}

#ifdef VERSION_DEMO
void func_80096994_demo(u8 count, u8* animations, struct BaseObj* source)
{
    u8* anim = animations;
    struct BaseObj* src = source;
    struct VisualObj* visual;
    u8 n;

    for (n = count; n != 0; n--) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 5;
            visual->unk15 = get_random() & 0x40;
            visual->state = 0;
            visual->unk5 = 0;
            visual->unk6 = 0;
            visual->unk50 = (struct PlayerObj*)src;
            visual->x_pos.val = src->x_pos.val + (get_random() & 3);
            visual->y_pos.val = src->y_pos.val + (get_random() & 3);
            visual->unk56 = *anim;
            anim++;
        }
    }
}
#endif
