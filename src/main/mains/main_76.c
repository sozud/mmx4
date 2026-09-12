// MainObj, main_object_update_funcs[76]
// 800919C4..800922D8
#include "common.h"

void func_800919C4(struct MainObj* arg0)
{
    D_80105FB4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091A00);

void func_80091AC4(struct MainObj* arg0)
{
    if (arg0->unk70 & 8) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk7C = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk2C = 0;
        arg0->unk20 = arg0->ext.raw[0];
        return;
    }

    func_8002B694(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091B1C);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091C64);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091D1C);

void func_80091E18(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80091E38(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6++;
        arg0->unk61 = 0x28;
    }
    if (arg0->unk61 & 7) {
        arg0->unk42 &= 0x7FFF;
    } else {
        arg0->unk42 |= 0x8000;
    }
    if (--arg0->unk61 == 0) {
        arg0->unk5 = 1;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091EC4);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_80091FC8);

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_8009216C);

INCLUDE_RODATA("main/nonmatchings/mains/main_76", D_80010D7C);

void func_800921E8(s32 arg0)
{
    u32 object_id;
    u32 random_value;
    s8 value;

#ifndef VERSION_JP
    object_id = arg0 & 0xFF;
    if (object_id >= 8U) {
#endif
        random_value = get_random() & 0xFF;
        random_value %= 3U;
#ifdef VERSION_JP
        object_id = arg0 & 0xFF;
#endif
        func_8001663C(D_80105FC8[object_id][random_value & 0xFF], 0x7F);
        value = 1;
#ifndef VERSION_JP
    } else {
        value = 0x3C;
    }
#endif
    engine_obj.unk36 = value;
}

INCLUDE_ASM("main/nonmatchings/mains/main_76", func_8009227C);

void (*D_80105FB4[])(struct MainObj*) = {
    func_80091A00,
    func_80091D1C,
    func_80091E18,
};
