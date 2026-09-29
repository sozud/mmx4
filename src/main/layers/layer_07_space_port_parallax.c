// LayerObj, layer_object_update_funcs[7]
// 800DA878..800DAE8C
#include "common.h"

extern struct TileEffectRecord** tile_effect_tables[26];

u8 tile_effect_is_visible(s16, s16, s16, s16);
void tile_effect_write_tile(struct TileEffectRecord*, s32, s32, s32);
void func_800DADA0(struct TileEffectRecord*, u16, u16, u8, u8);

void space_port_parallax_update(struct LayerObj* arg0)
{
    space_port_parallax_state_funcs[arg0->state](arg0);
}

void space_port_parallax_init(struct LayerObj* arg0)
{
    arg0->state++;
    background_objects[1].unk4D = 1;
    background_objects[1].unk4E = 6;
    *(s32*)&arg0->bg_offset = 0x8000;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    space_port_parallax_main(arg0);
}

void space_port_parallax_main(struct LayerObj* arg0)
{
    struct BackgroundObj* background_0;
    struct BackgroundObj* background_1;

    background_0 = &background_objects[0];
    background_1 = &background_objects[1];
    background_1->x_pos.val += *(s32*)&arg0->bg_offset - ((background_0->unk14.val - background_0->x_pos.val) / 2);
    background_1->y_pos.val = background_0->y_pos.val;
}

void space_port_parallax_despawn(struct LayerObj* arg0)
{
    despawn_object_permanently(OBJECT_HEADER(arg0));
}

#define UPDATE_XY(C)   \
    do {               \
        if (C) {       \
            x += 0x10; \
        } else {       \
            y += 0x10; \
        }              \
    } while (0)

void refresh_visible_tile_effect(s32 effect_id, s32 x_offset, s32 y_offset)
{
    struct TileEffectRecord* record;
    u16 origin_x = x_offset;
    u16 origin_y = y_offset;

    record = tile_effect_tables[engine_obj.stage * 2 + engine_obj.substage][effect_id & 0xFF];
    while (1) {
        s16 x = (u16)record->x + origin_x;
        s16 y = (u16)record->y + origin_y;
        u8 index = record->layer; /* Reused as the tile index below. */
        u8 horizontal = record->packed_count;
        u32 tile_count = horizontal >> 1;
        s32 byte_mask = 0xFF;
        s16 bg_x = background_objects[index].x_pos.u.hi;
        s16 bg_y = background_objects[index].y_pos.u.hi;

        horizontal &= 1; /* Low bit selects horizontal (1) or vertical (0). */
        for (index = 0; index != tile_count; index++) {
            s16 tile_x = x;
            s16 tile_y = y;
            if (tile_effect_is_visible(bg_x, bg_y, tile_x, tile_y)) {
                tile_effect_write_tile(record, (u16)(tile_x / 16), (u16)(tile_y / 16), (u8)index);
            }
            UPDATE_XY(horizontal & byte_mask);
        }
        if (!record->has_next) {
            break;
        }
        record++;
    }
}

u8 tile_effect_is_visible(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    if (((arg0 - 0x20) <= arg2) && (arg2 < (arg0 + 0x160)) && ((arg1 - 0x20) <= arg3) && (arg3 < (arg1 + 0x110))) {
        return 1;
    }
    return 0;
}

void tile_effect_write_tile(struct TileEffectRecord* arg0, s32 arg1, s32 arg2, s32 arg3)
{
    D_801441C8[arg0->layer][arg2 & 0x1F][arg1 & 0x1F] = arg0->tiles[arg3 & 0xFF];
}

void apply_tile_effect(u8 effect_id, s32 x_offset, s32 y_offset)
{
    struct TileEffectRecord* record;
    u16 origin_x = x_offset;
    u16 origin_y = y_offset;

    record = tile_effect_tables[engine_obj.stage * 2 + engine_obj.substage][effect_id & 0xFF];
    while (1) {
        s16 x = (u16)record->x + origin_x;
        s16 y = (u16)record->y + origin_y;
        u8 index = record->layer; /* Reused as the tile index below. */
        u8 horizontal = record->packed_count;
        u32 tile_count = horizontal >> 1;
        s32 byte_mask = 0xFF;
        s16 bg_x = background_objects[index].x_pos.u.hi;
        s16 bg_y = background_objects[index].y_pos.u.hi;

        horizontal &= 1; /* Low bit selects horizontal (1) or vertical (0). */
        for (index = 0; index != tile_count; index++) {
            s16 tile_x = x;
            s16 tile_y = y;
            u8 visible = tile_effect_is_visible(bg_x, bg_y, tile_x, tile_y);
            func_800DADA0(record, (u16)(tile_x / 16), (u16)(tile_y / 16), (u8)index, (u8)visible);
            UPDATE_XY(horizontal & byte_mask);
        }
        if (!record->has_next) {
            break;
        }
        record++;
    }
}
#undef UPDATE_XY

// tile_effect_apply_tile
INCLUDE_ASM("main/nonmatchings/layers/layer_07_space_port_parallax", func_800DADA0);

void tile_effect_nop(void)
{
}

void (*space_port_parallax_state_funcs[])(struct LayerObj*) = {
    space_port_parallax_init,
    space_port_parallax_main,
    space_port_parallax_despawn,
};
