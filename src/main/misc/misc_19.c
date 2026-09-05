// MiscObj, misc_object_update_funcs[19]
// 800CB634..800CB884
#include "common.h"

struct Unk8010E71C {
    s16 x;
    s16 y;
    s8 unk;
    s8 unk2;
};

extern struct Unk8010E71C D_8010E71C[];

extern s32* D_8010E81C[];

// g_TitleUpdateFuncs state 0
void func_800CB634(struct MiscObj* arg0)
{
    u8 temp_a1 = arg0->base.unk2;
    u8 temp_v1;

    arg0->animation_table = &D_8010E81C;
    arg0->base.bg_offset = -1;
    arg0->base.unk15 = 0;
    arg0->base.unk16 = 3;
    arg0->base.state++;

    arg0->unk40 = 0x600;
    arg0->unk3C = SP_TITLE_FRAMES;
    temp_v1 = D_8010E71C[temp_a1].unk2;
    arg0->unk42 = ((temp_v1 & 0xF) | (((temp_v1 >> 4) + 0x1E0) << 6));
    // for unk2 == 0, setting position of "MEGAMAN" text
    // for unk2 == 1, didn't notice a difference
    // for unk2 == 2, setting position of greyed out "GAME START" text
    arg0->base.x_pos.val = FIXED(D_8010E71C[temp_a1].x);
    arg0->base.y_pos.val = FIXED(D_8010E71C[temp_a1].y);
    arg0->unk47 = D_8010E71C[temp_a1].unk;
    is_on_screen(arg0);
}

// g_TitleUpdateFuncs state 1
void func_800CB708(struct MiscObj* arg0)
{
    u8 temp_v1;

    if (arg0->base.unk2 == 0xF) {
        arg0->base.unk16 = 2;
        arg0->base.y_pos.i.hi = (game_info.unk2 % 3) * 16 + 0x80;
        if (game_info.unk2 != 1) {
            if (!((game_info.unk2 < 2) && (game_info.unk2 == 0)))
                goto use_default_frame;
            arg0->unk47 = D_8010E71C[2].unk;
        } else {
            arg0->unk47 = D_8010E71C[13].unk;
        }
        goto frame_selected;
use_default_frame:
        arg0->unk47 = D_8010E71C[14].unk;
frame_selected:
        ;
    }

    temp_v1 = arg0->base.unk2;
    if (((temp_v1 >= 4) && (temp_v1 < 6)) || ((s8)temp_v1 == 6)) {
        arg0->base.on_screen = 0;
        if ((D_80141BD8.unk0 & 0x10) == 0) {
            return;
        }
    } else {
        arg0->base.on_screen = 1;
    }
    is_on_screen(&arg0->base);
}

// g_TitleUpdateFuncs state 2
void func_800CB828(struct MiscObj* arg0)
{
    ZeroObjectState(arg0);
}

// title object. Includes the logo and the menu graphics
void TitleUpdate(struct MiscObj* arg0)
{
    g_TitleUpdateFuncs[arg0->base.state]();
}
