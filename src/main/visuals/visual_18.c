// VisualObj, visual_object_update_funcs[18]
// 800B2544..800B2698
#include "common.h"

void func_800B2544(struct VisualObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    s32 var_a0;

    var_a0 = engine_obj.unkF != 0;
    if (player->unk93 != 6) {
        var_a0 = 1;
    }
    if (player->unk5C == 0) {
        var_a0 = 1;
    }
    if (var_a0 != 0) {
        ZeroObjectState(arg0);
        return;
    }
    if (arg0->base.state == 0) {
        arg0->base.on_screen = 1;
        arg0->base.bg_offset = player->base.bg_offset;
        arg0->unk38 = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[0x1C / 4];
        arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0x3C / 4];
        arg0->unk30 = &D_8011C0E4;
        arg0->unk40 = 0x520;
        arg0->unk42 = 0x7801;
        arg0->base.unk16 = 0x12;
        arg0->unk49 = 0;
        func_80015D60(arg0, 0);
        arg0->base.state++;
        decompress_player_gfx(arg0, 0x140, 0x20);
    } else {
        func_80015DC8(arg0);
    }
    arg0->base.x_pos.val = player->base.x_pos.val;
    arg0->base.y_pos.val = player->base.y_pos.val;
    arg0->base.unk15 = player->base.unk15;
    func_8002B318(arg0, 0x68, 0x48);
}
