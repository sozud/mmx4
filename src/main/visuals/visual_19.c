// VisualObj, visual_object_update_funcs[19]
// 800B2698..800B28CC
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_19", func_800B2698);

void func_800B2880(struct VisualObj* arg0)
{
    if (arg0->base.unk2 == 0) {
        decompress_player_gfx(arg0, 0x140, 0x20);
    }
    func_8002B318(arg0, 0x18, 0x30);
}
