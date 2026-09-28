// MiscObj, misc_object_update_funcs[19]
// 800CB634..800CB884
#include "common.h"

extern struct TitleObjectInit D_8010E71C[];
extern u32* D_8010E81C[];

// g_TitleUpdateFuncs state 0
void func_800CB634(struct MiscObj* arg0)
{
    u8 temp_a1 = arg0->unk2;
    u8 temp_v1;

    arg0->animation_table = D_8010E81C;
    arg0->bg_offset = -1;
    arg0->unk15 = 0;
    arg0->unk16 = 3;
    arg0->state++;

    arg0->unk40 = 0x600;
    arg0->unk3C = SP_TITLE_FRAMES;
    temp_v1 = D_8010E71C[temp_a1].flags;
    arg0->unk42 = ((temp_v1 & 0xF) | (((temp_v1 >> 4) + 0x1E0) << 6));
    // for unk2 == 0, setting position of "MEGAMAN" text
    // for unk2 == 1, didn't notice a difference
    // for unk2 == 2, setting position of greyed out "GAME START" text
    arg0->x_pos.val = FIXED(D_8010E71C[temp_a1].x);
    arg0->y_pos.val = FIXED(D_8010E71C[temp_a1].y);
    arg0->animation_step.fields.frame_index = D_8010E71C[temp_a1].sprite;
    is_on_screen(arg0);
}

// g_TitleUpdateFuncs state 1
void func_800CB708(struct MiscObj* arg0)
{
    u8 temp_v1;

    if (arg0->unk2 == 0xF) {
        arg0->unk16 = 2;
        arg0->y_pos.i.hi = (game_info.unk2 % 3) * 16 + 0x80;
        if (game_info.unk2 != 1) {
            if (!((game_info.unk2 < 2) && (game_info.unk2 == 0)))
                goto use_default_frame;
            arg0->animation_step.fields.frame_index = D_8010E71C[2].sprite;
        } else {
            arg0->animation_step.fields.frame_index = D_8010E71C[13].sprite;
        }
        goto frame_selected;
    use_default_frame:
        arg0->animation_step.fields.frame_index = D_8010E71C[14].sprite;
    frame_selected:;
    }

    temp_v1 = arg0->unk2;
    if (((temp_v1 >= 4) && (temp_v1 < 6)) || ((s8)temp_v1 == 6)) {
        arg0->on_screen = 0;
        if ((D_80141BD8.unk0 & 0x10) == 0) {
            return;
        }
    } else {
        arg0->on_screen = 1;
    }
    is_on_screen(arg0);
}

// g_TitleUpdateFuncs state 2
void func_800CB828(struct MiscObj* arg0)
{
    ZeroObjectState(arg0);
}

// title object. Includes the logo and the menu graphics
void TitleUpdate(struct MiscObj* arg0)
{
    g_TitleUpdateFuncs[arg0->state](arg0);
}

struct TitleObjectInit D_8010E71C[] = {
#ifdef VERSION_JP
    { 120, 72, 0, 0 },
    { 216, 72, 1, 4 },
    { 160, 128, 2, 7 },
    { 96, 144, 3, 6 },
    { 160, 160, 4, 10 },
    { 152, 184, 5, 10 },
    { 152, 184, 6, 10 },
    { 160, 216, 7, 10 },
    { 248, 120, 8, 10 },
    { 272, 104, 9, 10 },
    { 120, 72, 26, 0 },
    { 216, 72, 27, 4 },
    { 0, 0, 28, 4 },
    { 160, 144, 29, 7 },
    { 160, 160, 30, 7 },
    { 160, 128, 2, 6 },
#else
    { 144, 72, 0, 0 },
    { 160, 72, 1, 4 },
    { 160, 128, 2, 7 },
    { 96, 144, 3, 6 },
    { 160, 160, 4, 10 },
    { 152, 184, 5, 10 },
    { 152, 184, 6, 10 },
    { 160, 216, 7, 10 },
    { 272, 128, 8, 10 },
    { 288, 120, 9, 10 },
    { 120, 72, 26, 0 },
    { 208, 72, 27, 4 },
    { 248, 72, 28, 4 },
    { 160, 144, 29, 7 },
    { 160, 160, 30, 7 },
    { 160, 128, 2, 6 },
    { 278, 72, 31, 4 },
    { 176, 216, 31, 10 },
    { 128, 72, 26, 0 },
    { 176, 72, 32, 0 },
    { 128, 72, 33, 8 },
    { 176, 72, 34, 8 },
#endif
};

u32 D_8010E7A0[] = {
    0x0A010002,
    0x0B010002,
    0x0C010002,
    0x0D010002,
    0x0E010002,
    0x0F010002,
    0x10010002,
    0x11010002,
    0x11010102,
    0x11010202,
    0x11010302,
    0x11010402,
    0x11010502,
    0x11010602,
    0x11010702,
    0x11010802,
    0x11010902,
    0x11010A02,
    0x11010B02,
    0x11010C02,
    0x11010D02,
    0x11010E02,
    0x11000F02,
};

u32 D_8010E7FC[] = {
    0x12010001,
    0x13010002,
    0x14010001,
    0x15010001,
    0x16010001,
    0x17010001,
    0x18010002,
    0x19000003,
};

u32* D_8010E81C[] = { D_8010E7A0, D_8010E7FC };

void (*g_TitleUpdateFuncs[3])(struct MiscObj*) = {
    func_800CB634,
    func_800CB708,
    func_800CB828,
};
