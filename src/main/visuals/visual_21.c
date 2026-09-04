// VisualObj, visual_object_update_funcs[21]
// 800B2E98..800B3074
#include "common.h"

void func_800B2E98(struct VisualObj* arg0)
{
    struct VisualObj* temp_v1 = arg0->unk50;
    arg0->unk40 = temp_v1->unk40;
    arg0->unk42 = temp_v1->unk42 & ~0x8000;
    arg0->unk30 = temp_v1->unk30;
    arg0->unk3C = temp_v1->unk3C;
    arg0->base.unk15 = temp_v1->base.unk15;
    arg0->base.bg_offset = temp_v1->base.bg_offset;
    arg0->base.x_pos.val = temp_v1->base.x_pos.val;
    arg0->base.y_pos.val = temp_v1->base.y_pos.val;
    arg0->base.unk16 = 6;
    arg0->base.unk2 = D_8010A5B8[temp_v1->unk47];
    func_80015D60(arg0, arg0->base.unk2);
    arg0->base.state++;
}

void func_800B2F60(struct VisualObj* arg0)
{
    struct PlayerObj* temp_a0;

    temp_a0 = arg0->unk50;
    if (temp_a0->base.state == 0 || temp_a0->base.state == 2) {
        arg0->base.state = 2;
    } else {
        if (arg0->base.unk2 != D_8010A5B8[temp_a0->cur_anim]) {
            arg0->base.unk2 = D_8010A5B8[temp_a0->cur_anim];
            func_80015D60(arg0, arg0->base.unk2);
        } else {
            func_80015DC8(arg0);
        }
        func_8002B318(arg0, 0x90, 0x90);
    }
}

void func_800B3000(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800B3020(struct VisualObj* arg0)
{
    struct BaseObj* temp_v1 = arg0->unk50;

    arg0->base.x_pos.val = temp_v1->x_pos.val;
    arg0->base.y_pos.val = temp_v1->y_pos.val;
    D_8010A5C8[arg0->base.state](arg0);
}

u8 D_8010A5B8[16] = {
    6,
    7,
    8,
    9,
    6,
    6,
    6,
    7,
    7,
    7,
    8,
    8,
    8,
    0,
    0,
    0,
};

void (*D_8010A5C8[])(struct VisualObj*) = {
    func_800B2E98,
    func_800B2F60,
    func_800B3000,
};
