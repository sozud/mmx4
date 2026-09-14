// MiscObj, misc_object_update_funcs[45]
// 800D0E48..800D1284
#include "common.h"

#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/misc/misc_45", func_800D0E7C_jp);
#endif

INCLUDE_ASM("main/nonmatchings/misc/misc_45", func_800D0E48);

void func_800D1060(struct MiscObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->ext.misc_45.direction == 0) {
        if (arg0->x_pos.i.hi > arg0->ext.misc_45.target_x) {
            arg0->unk28 = FIXED(1);
            arg0->unk5++;
        }
    } else if (arg0->x_pos.i.hi < arg0->ext.misc_45.target_x) {
        arg0->unk28 = -FIXED(1);
        arg0->unk5++;
    }
}

void func_800D10E4(struct MiscObj* arg0)
{
    volatile u8 stack_pad[0x10];
    s32 var_v0;
    s32 var_v1;
    s32 var_a0;

    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->ext.misc_45.direction == 0) {
        var_v1 = arg0->ext.misc_45.target_x;
        var_v0 = arg0->x_pos.i.hi;
        var_a0 = var_v1;
    } else {
        var_v0 = arg0->ext.misc_45.target_x;
        var_v1 = arg0->x_pos.i.hi;
        var_a0 = var_v0;
    }
    if (var_v0 < var_v1) {
        arg0->x_pos.i.hi = var_a0;
        arg0->unk28 = 0;
        arg0->x_vel.val = 0;
        arg0->unk5++;
    }
}

void func_800D115C(void)
{
}

struct Misc45PositionData {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};

extern struct Misc45PositionData D_8010F0C4[];

void func_800D1164(struct MiscObj* self)
{
    s32 index;
    struct MainObj* source;

    index = self->unk2;
    source = self->ext.misc_2.owner;
    self->x_pos.u.hi = source->x_pos.u.hi + D_8010F0C4[index].x;
    self->y_pos.u.hi = source->y_pos.u.hi + D_8010F0C4[self->unk2].y;
}

INCLUDE_ASM("main/nonmatchings/misc/misc_45", func_800D11B0);

void func_800D11CC(struct MiscObj* arg0)
{
    if (engine_flags != 0) {
        D_8010F174[arg0->unk5](arg0);
        arg0->on_screen = 1;
    }
}

void func_800D1228(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800D1248(struct MiscObj* arg0)
{
    D_8010F188[arg0->state](arg0);
}

struct Misc45PositionData D_8010F0C4[] = {
    { -120, 176, 184, 160 },
    { 424, 208, 99, 123 },
    { 448, 208, 136, 160 },
    { 432, 208, 136, 160 },
    { 432, 208, 136, 160 },
    { 400, 208, 65, 89 },
    { 448, 208, 136, 160 },
    { 400, 208, 65, 89 },
    { 464, 208, 136, 160 },
    { -120, 176, 184, 160 },
    { 440, 208, 136, 160 },
#ifdef VERSION_JP
    { 440, 208, 136, 160 },
#else
    { 440, 208, 136, 152 },
#endif
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 440, 208, 136, 160 },
    { 136, 0, 0, 0 },
    { 144, 0, 0, 0 },
    { 144, 0, 0, 0 },
#ifndef VERSION_JP
    { 136, 0, 0, 0 },
#endif
};

void (*D_8010F174[5])(struct MiscObj*) = {
    func_800D1060,
    func_800D10E4,
    func_800D115C,
    func_800D1164,
    func_800D11B0,
};

void (*D_8010F188[3])(struct MiscObj*) = {
    func_800D0E48,
    func_800D11CC,
    func_800D1228,
};
