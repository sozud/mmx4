// VisualObj, visual_object_update_funcs[19]
// 800B2698..800B28CC
#include "common.h"

// double_cyclone_charged_fan_update
INCLUDE_ASM("main/nonmatchings/visuals/visual_19_double_cyclone_charged_fan", func_800B2698);

void double_cyclone_charged_fan_draw(struct VisualObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    }
    update_on_screen(arg0, 0x18, 0x30);
}
