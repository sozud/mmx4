// MainObj, main_object_update_funcs[47]
// 80066DAC..80067350
#include "common.h"

void func_80066DAC(struct MainObj* arg0)
{
    D_800FFA0C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_47", func_80066DE8);

INCLUDE_ASM("main/nonmatchings/mains/main_47", func_80066F1C);

extern u16 D_800FF9F0[][2];

void func_800671D8(struct MainObj* self)
{
    s16 timer7C;
    s16 timer7E;
    s32 tableIndex;
    s32 x;
    s32 y;
    s32 frameArea[2];

    timer7C = self->unk7C - 1;
    self->unk7C = timer7C;
    if (timer7C == 0) {
        self->state = 3;
        return;
    }

    timer7E = self->unk7E - 1;
    self->unk7E = timer7E;
    if (timer7E == 0) {
        tableIndex = self->unk2;
        y = (u16)self->ext.main_47.unk80->x_pos.i.hi + D_800FF9F0[tableIndex][0];
        x = (u16)self->y_pos.i.hi + D_800FF9F0[tableIndex][1];
        func_800B10E4(0x11, (s16)(y - 6), (s16)(x - 6),
            (s16)(y + 6), (s16)(x + 6), 1);
        self->unk7E = 10;
    }
}

void func_800672BC(struct MainObj* arg0)
{
    arg0->ext.main_47.unk80 = 0;
    arg0->ext.main_47.unk84 = 0;
    arg0->ext.main_47.unk88 = 0;
    arg0->ext.main_47.unk8C = 0;
    arg0->ext.main_47.unk90 = 0;
    arg0->ext.main_47.unk94 = 0;
}

void func_800672D8(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->unk6 = 1;
}

void func_800672EC(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        if (arg0->x_pos.i.hi >= 0x1AA1) {
            arg0->unk6 = 1;
            return;
        }
        func_8002B718(MOVING_OBJECT(arg0));
        return;
    }
    arg0->unk42 &= 0x7FFF;
}
