// ShotObj, shot_object_update_funcs[25]
// 8009EB6C..8009EE68
#include "common.h"

void func_8009EB6C(struct ShotObj* arg0)
{
    D_80109160[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_25", func_8009EBA8);

void func_8009ED70(struct ShotObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B694(arg0);
    func_8002D9BC(arg0);

    if (func_8002BB80(arg0, &g_Player) != 0) {
        if (arg0->unk2 & 0x40) {
        label:
            func_800AF808(arg0);
        }
    } else if (!(arg0->unk2 & 0x40) || (CollisionRelated(arg0), arg0->unk70 == 0)) {
        if (func_8002B160(arg0) == 0) {
            is_on_screen(arg0);
            return;
        }
    } else {
        goto label; // unfortunately seems to be necessary for a match
    }

    arg0->state++;
}

void func_8009EE40(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8009EE60(struct ShotObj* arg0)
{
}

void (*D_80109124[11])(struct ShotObj*) = {
    func_8009216C,
    func_8009E5A4,
    func_8009E5B0,
    func_8009E608,
    func_8009E690,
    func_8009E718,
    func_8009E7B4,
    func_8009E7EC,
    func_8009E8E0,
    func_8009E9EC,
    func_8009EAA4,
};

u8 D_80109150[4] = { 0xF9, 0xF9, 0x0C, 0x0C };

u8 D_80109154[4] = { 0, 0, 4, 4 };

s8 D_80109158[8] = { 0x21, -0x2A, 0x30, -0x15, 0x28, 7, 0, 0 };

void (*D_80109160[])(struct ShotObj*) = {
    func_8009EBA8,
    func_8009ED70,
    func_8009EE40,
    func_8009EE60,
};
