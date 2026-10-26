// VisualObj, visual_object_update_funcs[8]
// 800B0890..800B1354
#include "common.h"
#include "main/objects.h"
#include "main/visuals/visual_08_ice_shard.h"
#include "main/object_motion.h"
#include "main/55C4.h"

// ice_shard_state_funcs
extern void (*ice_shard_state_funcs[])(struct VisualObj*);

void ice_shard_despawn(struct VisualObj*);
void ice_shard_idle(struct VisualObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/55C4.h"
#endif
extern s8 ice_shard_offsets[4][2];

s8 ice_shard_offsets[4][2] = {
    { 0, -32 },
    { 32, 0 },
    { 0, 32 },
    { -32, 0 },
};

void ice_shard_update(struct VisualObj* arg0)
{
    ice_shard_state_funcs[arg0->state](arg0);
}

// ice_shard_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B0CA0(s32 type, s32 mode, struct MainObj* source, s32 radius, s32 count);
void func_800B08CC(struct VisualObj* self);
void func_800B0B48(struct VisualObj* self);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/visuals/visual_08_ice_shard", func_800B08CC);
#else
void func_800B08CC(struct VisualObj* self)
{
    s32 kind = self->unk2;

    self->on_screen = 1;
    self->x_vel.val = 0;
    self->y_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->state++;
    switch ((s8)(kind % 4)) {
    case 0:
        self->x_pos.i.hi += ice_shard_offsets[0][0] + get_random_nonzero() % 32;
        self->y_pos.i.hi += ice_shard_offsets[0][1] + get_random_nonzero() % 32;
        break;
    case 1:
        self->x_pos.i.hi += ice_shard_offsets[1][0] + get_random_nonzero() % 32;
        self->y_pos.i.hi += ice_shard_offsets[1][1] + get_random_nonzero() % 32;
        break;
    case 2:
        self->x_pos.i.hi += ice_shard_offsets[2][0] + get_random_nonzero() % 32;
        self->y_pos.i.hi += ice_shard_offsets[2][1] + get_random_nonzero() % 32;
        break;
    case 3:
        self->x_pos.i.hi += ice_shard_offsets[3][0] + get_random_nonzero() % 32;
        self->y_pos.i.hi += ice_shard_offsets[3][1] + get_random_nonzero() % 32;
        break;
    }
    set_animation(self, get_random_nonzero() % 3 + 0xE);
}
#endif

// ice_shard_main
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/visuals/visual_08_ice_shard", func_800B0B48);
#else
void func_800B0B48(struct VisualObj* self)
{
    struct MainObj* parent = (struct MainObj*)self->unk50;
    s32 direction;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    direction = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(parent));
    set_velocity_from_angle(MOVING_OBJECT(self), direction);
    switch (direction / 8) {
    case 0:
        direction = self->x_vel.val;
        self->x_vel.val = -(self->y_vel.val * 24);
        self->y_vel.val = direction * 24;
        break;
    case 1:
        direction = self->x_vel.val;
        self->x_vel.val = -(self->y_vel.val * 24);
        self->y_vel.val = direction * 24;
        break;
    case 2:
        direction = self->x_vel.val;
        self->x_vel.val = -(self->y_vel.val * 24);
        self->y_vel.val = direction * 24;
        break;
    case 3:
        direction = self->x_vel.val;
        self->x_vel.val = -(self->y_vel.val * 24);
        self->y_vel.val = direction * 24;
        break;
    }
    if (parent->ext.main_14.unk8C != 0)
        self->state++;
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0)
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
    else
        self->state++;
}
#endif

void ice_shard_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void ice_shard_idle(struct VisualObj* arg0)
{
}

// spawn_dust_puffs_at_object
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800B0CA0(s32 type, s32 mode, struct MainObj* source, s32 radius,
    s32 count)
{
    const struct Unk_unk68* bounds = source->terrain_box;
    s32 left = source->x_pos.i.hi;
    s32 right = left;
    s32 base_y = source->y_pos.i.hi + bounds->unk1;
    s32 top = base_y;
    s32 bottom = base_y;
    s32 width;
    s32 height;
    s32 i;

    switch ((u8)mode) {
    case 1:
    case 2:
        if (source->unk15 == 0) {
            left = source->x_pos.i.hi + bounds->unk0 - bounds->unk2;
            right = left + bounds->unk2 * 2;
        } else {
            right = source->x_pos.i.hi - bounds->unk0 + bounds->unk2;
            left = right - bounds->unk2 * 2;
        }
        if ((u8)mode == 1)
            top = bottom = base_y - bounds->unk3;
        else
            top = bottom = base_y + bounds->unk3;
        break;
    case 3:
        left = source->unk15 == 0
            ? source->x_pos.i.hi + bounds->unk0 - bounds->unk2
            : source->x_pos.i.hi - bounds->unk0 + bounds->unk2;
        right = left;
        top -= bounds->unk3;
        bottom += bounds->unk3;
        break;
    case 4:
        left = source->unk15 == 0
            ? source->x_pos.i.hi + bounds->unk0 + bounds->unk2
            : source->x_pos.i.hi - bounds->unk0 - bounds->unk2;
        right = left;
        top -= bounds->unk3;
        bottom += bounds->unk3;
        break;
    default:
        break;
    }
    left -= radius;
    top -= radius;
    right += radius;
    bottom += radius;
    width = (s16)(right - left);
    height = (s16)(bottom - top);

    for (i = 0; i < (s16)count; i++) {
        struct VisualObj* visual = find_free_visual_obj();
        u32 random_value;

        if (visual == NULL)
            continue;
        visual->active = 0x21;
        visual->id = 9;
        visual->unk2 = 0;
        random_value = (u32)get_random() << 8;
        random_value |= get_random();
        visual->x_pos.i.hi = width == 0 ? left : left + (s32)(u16)(random_value + 1) % width;
        random_value = (u32)get_random() << 8;
        random_value |= get_random();
        visual->y_pos.i.hi = height == 0 ? top : top + (s32)(u16)(random_value + 1) % height;
        visual->x_pos.u.lo = 0;
        visual->y_pos.u.lo = 0;
        if (((u8)type & 3) == 1) {
            visual->x_vel.val = 0;
            visual->y_vel.val = FIXED(1);
        } else if (((u8)type & 3) == 2) {
            visual->x_vel.val = visual->x_pos.i.hi < source->x_pos.i.hi
                ? FIXED(-1.5)
                : FIXED(1.5);
            visual->y_vel.val = 0;
        } else {
            visual->x_vel.val = 0;
            visual->y_vel.val = 0;
        }
        visual->unk15 = 0;
        visual->state = 0;
        visual->unk5 = 0;
        visual->unk6 = 0;
        visual->unk5C.value = (u8)type >> 4;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/visuals/visual_08_ice_shard", func_800B0CA0);
#endif

// spawn_dust_puffs_in_rect
#define RANDOM_U16_PLUS_ONE(high, low) \
    ((high) = get_random(),            \
        (low) = get_random(),          \
        (high) &= 0xFF,                \
        (high) <<= 8,                  \
        ((low)&0xFF) + (high) + 1)

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/visuals/visual_08_ice_shard", func_800B10E4);
#else
void func_800B10E4(u8 kind, s32 left, s32 top, s32 right, s32 bottom, s32 count_arg)
{
    s16 x_min = left;
    s16 y_min = top;
    s16 x_max = right;
    s16 y_max = bottom;
    s16 count = count_arg;
    s16 midpoint = x_min + (x_max - x_min) / 2;
    s16 x_delta;
    s16 y_delta;
    s16 i;

    for (i = 0; i < count; i++) {
        struct VisualObj* visual = find_free_visual_obj();
        u32 random_x;
        u32 random_y;
        u32 high;
        u32 low;

        x_delta = x_max - x_min;
        if (visual == NULL) {
            continue;
        }

        visual->active = 0x21;
        visual->id = 9;
        visual->unk2 = 0;

        random_x = RANDOM_U16_PLUS_ONE(high, low);
        random_y = RANDOM_U16_PLUS_ONE(high, low);

        if (x_delta == 0) {
            visual->x_pos.i.hi = x_min;
        } else {
            visual->x_pos.i.hi = x_min + (s32)(u16)random_x % x_delta;
        }

        y_delta = y_max - y_min;
        if (y_delta == 0) {
            visual->y_pos.i.hi = y_min;
        } else {
            visual->y_pos.i.hi = y_min + (s32)(u16)random_y % y_delta;
        }

        visual->x_pos.i.lo = 0;
        visual->y_pos.i.lo = 0;

        switch (kind & 3) {
        case 1:
            visual->x_vel.val = 0;
            visual->y_vel.val = FIXED(1);
            break;
        case 2:
            if (visual->x_pos.i.hi < midpoint) {
                visual->x_vel.val = -FIXED(1.5);
                visual->y_vel.val = 0;
            } else {
                visual->x_vel.val = FIXED(1.5);
                visual->y_vel.val = 0;
            }
            break;
        default:
            visual->x_vel.val = 0;
            visual->y_vel.val = 0;
            break;
        }

        visual->unk15 = 0;
        visual->unk5C.value = kind >> 4;
        visual->state = 0;
        visual->unk5 = 0;
        visual->unk6 = 0;
    }
}
#endif

void (*ice_shard_state_funcs[])(struct VisualObj*) = {
    func_800B08CC,
    func_800B0B48,
    ice_shard_despawn,
    ice_shard_idle,
};
