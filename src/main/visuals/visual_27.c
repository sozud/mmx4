// VisualObj, visual_object_update_funcs[27]
// 800B2A3C..800B2AD0
#include "common.h"

void func_800B2A3C(struct VisualObj* arg0)
{
    if (arg0->base.unk2 == 0) {
        arg0->unk38 = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0x18 / 4];
    } else {
        arg0->unk38 = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0x24 / 4];
    }

    arg0->unk40 = 0x520;
    arg0->unk48 = -1;
    arg0->unk47 = 0;

    decompress_player_gfx(arg0, 0x140, 0x20);
    ZeroObjectState(arg0);
}
