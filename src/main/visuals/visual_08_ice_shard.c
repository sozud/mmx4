// VisualObj, visual_object_update_funcs[8]
// 800B0890..800B1354
#include "common.h"

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
INCLUDE_ASM("main/nonmatchings/visuals/visual_08_ice_shard", func_800B08CC);

// ice_shard_main
INCLUDE_ASM("main/nonmatchings/visuals/visual_08_ice_shard", func_800B0B48);

void ice_shard_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void ice_shard_idle(struct VisualObj* arg0)
{
}

// spawn_dust_puffs_at_object
INCLUDE_ASM("main/nonmatchings/visuals/visual_08_ice_shard", func_800B0CA0);

// spawn_dust_puffs_in_rect
#define RANDOM_U16_PLUS_ONE(high, low) \
    ((high) = get_random(),            \
        (low) = get_random(),          \
        (high) &= 0xFF,                \
        (high) <<= 8,                  \
        ((low)&0xFF) + (high) + 1)

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
            visual->y_vel.val = 0x10000;
            break;
        case 2:
            if (visual->x_pos.i.hi < midpoint) {
                visual->x_vel.val = -0x18000;
                visual->y_vel.val = 0;
            } else {
                visual->x_vel.val = 0x18000;
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

void (*ice_shard_state_funcs[])(struct VisualObj*) = {
    func_800B08CC,
    func_800B0B48,
    ice_shard_despawn,
    ice_shard_idle,
};
