// LayerObj, layer_object_update_funcs[7]
// 800DA878..800DA984
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
#undef UPDATE_XY

// tile_effect_apply_tile

void (*space_port_parallax_state_funcs[])(struct LayerObj*) = {
    space_port_parallax_init,
    space_port_parallax_main,
    space_port_parallax_despawn,
};
