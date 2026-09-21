// ShotObj, shot_object_update_funcs[10]
// 8009B3E8..8009B67C
#include "common.h"

void func_8009B3E8(struct ShotObj* arg0)
{
    D_80108E48[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_10", func_8009B424);

void func_8009B594(struct ShotObj* arg0)
{
    struct ShotObj* self = arg0;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        if (self->unk84.value >= 3) {
            func_800AF808(BASE_OBJECT(self));
        }
        self->state = (u8)self->state + 1;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(self), 0x10, 0x10);
    } else {
        self->state = (u8)self->state + 1;
    }
    self->unk84.value += 1;
}

void func_8009B654(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009B674(struct ShotObj* arg)
{
}

u8 D_80108DC0[4] = { 0xFD, 0xFA, 0x08, 0x08 };

u8 D_80108DC4[4] = { 0xF7, 0xF6, 0x10, 0x13 };

u8 D_80108DC8[16][4] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
    { 1, 0, 0, 5 },
    { 1, 0, 0, 6 },
    { 1, 0, 0, 7 },
    { 1, 0, 0, 8 },
    { 1, 0, 0, 9 },
    { 1, 0, 0, 10 },
    { 1, 0, 0, 11 },
    { 1, 0, 0, 12 },
    { 1, 0, 0, 13 },
    { 1, 0, 0, 14 },
    { 1, 0, 0, 15 },
};

u8* D_80108E08[16] = {
    D_80108DC8[0],
    D_80108DC8[1],
    D_80108DC8[2],
    D_80108DC8[3],
    D_80108DC8[4],
    D_80108DC8[5],
    D_80108DC8[6],
    D_80108DC8[7],
    D_80108DC8[8],
    D_80108DC8[9],
    D_80108DC8[10],
    D_80108DC8[11],
    D_80108DC8[12],
    D_80108DC8[13],
    D_80108DC8[14],
    D_80108DC8[15],
};

void (*D_80108E48[])(struct ShotObj*) = {
    func_8009B424,
    func_8009B594,
    func_8009B654,
    func_8009B674,
};
