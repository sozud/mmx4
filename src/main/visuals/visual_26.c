// VisualObj, visual_object_update_funcs[26]
// 800B28CC..800B2A3C
#include "common.h"

void func_800B28CC(struct VisualObj* arg0)
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
        arg0->unk40 = D_8010A588[arg0->unk2];
        arg0->unk42 = temp_s1->unk42;
        arg0->unk16 = D_8010A590[arg0->unk2];
        arg0->unk15 = temp_s1->unk15;
        arg0->unk49 = 1;
        func_80015D60(arg0, D_8010A594[arg0->unk2]);
        arg0->state++;
    } else {
        func_80015DC8(arg0);
    }

    arg0->x_pos.val = temp_s1->x_pos.val;
    arg0->y_pos.val = temp_s1->y_pos.val;

    if (D_8010A598[arg0->unk2] != 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, D_8010A598[arg0->unk2]);
    }

    func_8002B318(arg0, D_8010A5A0[arg0->unk2].x,
        D_8010A5A0[arg0->unk2].y);
}

struct VisualSpawnOffset D_8010A584[2] = {
    { -0x10, -0x07 },
    { 0x1F, -0x07 },
};

u16 D_8010A588[4] = { 0x0530, 0x0520, 0x0530, 0x0530 };
u8 D_8010A590[4] = { 3, 2, 3, 3 };
u8 D_8010A594[4] = { 0, 1, 2, 4 };
s16 D_8010A598[4] = { 0x30, 0, 0x30, 0x30 };

struct VisualBounds D_8010A5A0[4] = {
    { 0x20, 0x28 },
    { 0x28, 0x38 },
    { 0x38, 0x38 },
    { 0x38, 0x38 },
};
