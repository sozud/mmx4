// VisualObj, visual_object_update_funcs[3]
// 800AF6A0..800AFB50
#include "common.h"

u8 D_8010A1D4[] = {
    0x00,
    0x01,
    0x05,
    0x0A,
    0x0B,
    0x17,
    0x0C,
    0x0D,
    0x11,
    0x12,
    0x0E,
    0x0F,
    0x10,
    0x09,
    0x00,
    0x00,
};

struct Visual03Bounds D_8010A1E4[14] = {
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
    { 0x20, 0x20 },
};

void func_800AF6A0(struct VisualObj* arg0)
{
    switch (arg0->state) {
    case 0:
        arg0->on_screen = 1;
        func_80015D60(arg0, D_8010A1D4[arg0->unk2]);
        arg0->state++;
        func_8002B318(BASE_OBJECT(arg0), D_8010A1E4[arg0->unk2].x,
            D_8010A1E4[arg0->unk2].y);
        break;
    case 1:
        if (func_8002B1E8(BASE_OBJECT(arg0),
                D_8010A1E4[arg0->unk2].x,
                D_8010A1E4[arg0->unk2].y)
            == 0) {
            func_80015DC8(arg0);
            if ((arg0->unk2 == 9) && (arg0->animation_step.fields.event != 0)) {
                arg0->animation_step.fields.event = 0;
                g_Player.unkDF = 0;
            }
            if (arg0->animation_step.fields.relative_step < 0) {
                arg0->state = 2;
            }
        } else {
            arg0->state = 2;
        }
        func_8002B318(BASE_OBJECT(arg0), D_8010A1E4[arg0->unk2].x,
            D_8010A1E4[arg0->unk2].y);
        break;
    case 2:
        ZeroObjectState(OBJECT_HEADER(arg0));
        break;
    }
}

void func_800AF808(struct BaseObj* arg0)
{
    func_800AF828(arg0, 0);
}

void func_800AF828(struct BaseObj* arg0, s8 arg1)
{
    func_800AFAB4(arg1, arg0->x_pos.i.hi, arg0->y_pos.i.hi, (get_random() & 1) ^ 1);
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_03", func_800AF878);

INCLUDE_ASM("main/nonmatchings/visuals/visual_03", func_800AF95C);

struct VisualObj* func_800AFAB4(s8 arg0, s16 x, s16 y, u8 arg3)
{
    struct VisualObj* temp_v0 = find_free_visual_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x21;
        temp_v0->id = 4;
        temp_v0->unk2 = arg0;
        temp_v0->state = 0;
        temp_v0->unk5 = 0;
        temp_v0->unk6 = 0;
        temp_v0->unk5C = arg3;
        temp_v0->x_pos.i.hi = x;
        temp_v0->x_pos.i.lo = 0;
        temp_v0->y_pos.i.hi = y;
        temp_v0->y_pos.i.lo = 0;
        temp_v0->unk15 = 0;
        temp_v0->bg_offset = 0;
        temp_v0->unk16 = 1;
    }
    return temp_v0;
}
