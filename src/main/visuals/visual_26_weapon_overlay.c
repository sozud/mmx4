// VisualObj, visual_object_update_funcs[26]
// 800B28CC..800B2A3C
#include "common.h"
#include "main/visuals/visual_26_weapon_overlay.h"
#include "main/55C4.h"
#include "main/objects.h"
#include "main/mains/main_23_slope_skier.h"

struct VisualBounds {
    s16 x, y;
};

extern u16 weapon_overlay_palettes[];
extern u8 weapon_overlay_layers[4];
extern u8 weapon_overlay_animations[4];
extern s16 weapon_overlay_gfx_rows[4];
extern struct VisualBounds weapon_overlay_bounds[4];
#include "weapon_resources.h"

void weapon_overlay_update(struct VisualObj* arg0)
{
    struct VisualObj* temp_s1;

    temp_s1 = arg0->unk50;
    if ((temp_s1 == 0) || (temp_s1->active == 0)) {
        ZeroObjectState(arg0);
        return;
    }

    if (arg0->state == 0) {
        arg0->on_screen = 1;
        arg0->unk38 = temp_s1->unk38;
        arg0->unk3C = temp_s1->unk3C;
        arg0->animation_table = temp_s1->animation_table;
        arg0->unk40 = weapon_overlay_palettes[arg0->unk2];
        arg0->unk42 = temp_s1->unk42;
        arg0->unk16 = weapon_overlay_layers[arg0->unk2];
        arg0->unk15 = temp_s1->unk15;
        arg0->unk49 = 1;
        set_animation(arg0, weapon_overlay_animations[arg0->unk2]);
        arg0->state++;
    } else {
        animate_object(arg0);
    }

    arg0->x_pos.val = temp_s1->x_pos.val;
    arg0->y_pos.val = temp_s1->y_pos.val;

    if (weapon_overlay_gfx_rows[arg0->unk2] != 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, weapon_overlay_gfx_rows[arg0->unk2]);
    }

    update_on_screen(arg0, weapon_overlay_bounds[arg0->unk2].x,
        weapon_overlay_bounds[arg0->unk2].y);
}

struct VisualSpawnOffset double_cyclone_charged_fan_offsets[2] = {
    { -0x10, -0x07 },
    { 0x1F, -0x07 },
};

u16 weapon_overlay_palettes[4] = { WEAPON_TEXTURE_SPECIAL_1, WEAPON_TEXTURE_SPECIAL_0, WEAPON_TEXTURE_SPECIAL_1, WEAPON_TEXTURE_SPECIAL_1 };
u8 weapon_overlay_layers[4] = { 3, 2, 3, 3 };
u8 weapon_overlay_animations[4] = { 0, 1, 2, 4 };
s16 weapon_overlay_gfx_rows[4] = { 0x30, 0, 0x30, 0x30 };

struct VisualBounds weapon_overlay_bounds[4] = {
    { 0x20, 0x28 },
    { 0x28, 0x38 },
    { 0x38, 0x38 },
    { 0x38, 0x38 },
};
