// MainObj, main_object_update_funcs[41]
// 800623C4..80062D60
#include "common.h"

void func_800623C4(struct MainObj* arg0)
{
    D_800FEE38[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062400);

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_800624B4);

void func_80062550(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->ext.main_41.unk84 = 0;
        arg0->ext.main_41.unk83 = 1;
        func_80015D60(arg0, arg0->ext.main_41.unk82 + 5);
    }
    if (!(arg0->unk70 & 8)) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        return;
    }
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_800625C4);

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062650);

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_800626F0);

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062778);

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062910);

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062A0C);

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062AEC);

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062BBC);

void func_80062D18(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062D20);
