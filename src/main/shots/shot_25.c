// ShotObj, shot_object_update_funcs[25]
// 8009EB6C..8009EE68
#include "common.h"

void func_8009EB6C(struct ShotObj* arg0)
{
    D_80109160[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_25", func_8009EBA8);

void func_8009ED70(struct Unk* arg0)
{
    func_80015DC8(arg0);
    func_8002B694(arg0);
    func_8002D9BC(arg0);

    if (func_8002BB80(arg0, &g_Player) != 0) {
        if (arg0->base.unk2 & 0x40) {
        label:
            func_800AF808(arg0);
        }
    } else if (!(arg0->base.unk2 & 0x40) || (CollisionRelated(arg0), arg0->unk70 == 0)) {
        if (func_8002B160(arg0) == 0) {
            is_on_screen(arg0);
            return;
        }
    } else {
        goto label; // unfortunately seems to be necessary for a match
    }

    arg0->base.state++;
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_25", func_8009EE40);

void func_8009EE60(void)
{
}

void (*D_80109160[])(struct ShotObj*) = {
    func_8009EBA8,
    func_8009ED70,
    func_8009EE40,
    func_8009EE60,
};
