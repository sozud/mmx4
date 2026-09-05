// QuadObj, quad_object_update_funcs[12]
// 800D7734..800D7A4C
#include "common.h"

extern u8 D_8010FDEC[][4];
extern u16 D_8016949A[][4];

void func_800D7734(struct QuadObj* arg0)
{
    u16* vertex;
    u16 x;
    u16 y;
    u8 state;

    arg0->bg_offset = -1;
    arg0->x_pos.i.hi = 0;
    arg0->y_pos.i.hi = 0;
    arg0->active |= 0x80;
    vertex = D_8016949A[D_8010FDEC[arg0->unk2][0]];
    arg0->unk14.i.hi = vertex[0];
    arg0->unk18.i.hi = vertex[2];
    vertex = D_8016949A[D_8010FDEC[arg0->unk2][1]];
    arg0->unk1C.i.hi = vertex[0];
    arg0->unk20.i.hi = vertex[2];
    vertex = D_8016949A[D_8010FDEC[arg0->unk2][2]];
    arg0->unk24.i.hi = vertex[0];
    arg0->unk28.i.hi = vertex[2];
    vertex = D_8016949A[D_8010FDEC[arg0->unk2][3]];
    state = arg0->state;
    x = vertex[0];
    state++;
    arg0->unk2C.i.hi = x;
    y = vertex[2];
    arg0->unk36 = 0x11;
    arg0->ext.unk_ext.unk38 = 0x3C;
    arg0->state = state;
    arg0->unk30.i.hi = y;
    arg0->unk34 = 0x7FFF;
    arg0->on_screen = 1;
}

void func_800D784C(struct QuadObj* arg0)
{
    u16* vertex;

    vertex = D_8016949A[D_8010FDEC[arg0->unk2][0]];
    arg0->unk14.i.hi = vertex[0];
    arg0->unk18.i.hi = vertex[2];
    vertex = D_8016949A[D_8010FDEC[arg0->unk2][1]];
    arg0->unk1C.i.hi = vertex[0];
    arg0->unk20.i.hi = vertex[2];
    vertex = D_8016949A[D_8010FDEC[arg0->unk2][2]];
    arg0->unk24.i.hi = vertex[0];
    arg0->unk28.i.hi = vertex[2];
    vertex = D_8016949A[D_8010FDEC[arg0->unk2][3]];
    arg0->unk2C.i.hi = vertex[0];
    arg0->unk30.i.hi = vertex[2];
    if (game_info.unk6 == 0) {
        arg0->state++;
        arg0->ext.unk_ext.unk38 = 5;
    }
    arg0->on_screen = 1;
}

void func_800D7960(struct QuadObj* arg0)
{
    struct MiscObj* misc;
    if (--(arg0->ext.unk_ext.unk38) == 0) {
        if (arg0->unk2 == 0) {
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->base.active = 1;
                misc->base.id = 0x13;
                misc->base.unk2 = 0xB;
            }
        }
        arg0->state++;
    }
    quad_is_on_screen(arg0);
}

void func_800D79F0(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D7A10(struct QuadObj* arg0)
{
    D_8010FE10[arg0->state](arg0);
}

void (*D_8010FE10[])(struct QuadObj*) = {
    func_800D7734,
    func_800D784C,
    func_800D7960,
    func_800D79F0,
};
