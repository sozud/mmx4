// MainObj, main_object_update_funcs[71]
// 80089AA4..8008ADFC
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089AA4);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089B58);

s32 func_80089C0C(struct MainObj* arg0)
{
    u8 flags;

    if (arg0->unk2 == 0) {
        flags = arg0->ext.main_71.unk8A;
        if (flags != 0) {
            if (flags & 1) {
                arg0->unk15 = 0x40;
            } else {
                arg0->unk15 = 0;
            }
            return 1;
        }
    } else {
        if ((arg0->x_pos.i.hi - g_Player.x_pos.i.hi) < 0) {
            arg0->unk15 = 0x40;
        } else {
            arg0->unk15 = 0;
        }
    }

    return 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089C7C);

void func_80089EBC(struct BaseObj* arg0, s8 arg1)
{
    arg0->unk5 = arg1;
    arg0->unk6 = 0;
}

void func_80089EC8(struct MainObj* arg0)
{
    if (arg0->unk5 < 2) {
        return;
    }
    if (arg0->unk5 == 6) {
        return;
    }
    if (arg0->unk5 == 7) {
        return;
    }
    if (arg0->unk5 == 0xB) {
        return;
    }
    if (arg0->ext.main_71.unk88 == 0) {
        return;
    }
    if (arg0->ext.main_71.unk8D & 8) {
        return;
    }
    if (arg0->unk67 != 0) {
        return;
    }
    if (arg0->ext.main_71.unk86 == 0) {
        func_80089EBC(BASE_OBJECT(arg0), 6);
    }
}

void func_80089F58(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->unk54 = D_80104CDC;
    arg0->unk50 = D_80104CE0;
    arg0->unk6 = 0;
    arg0->ext.main_71.unk88 = 0;
    arg0->ext.main_71.unk86 = 0;
    arg0->ext.main_71.unk87 = 0;
    arg0->unk60 = 5;
}

void func_80089F94(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->unk20;
}

void func_80089FAC(struct MainObj* arg0)
{
    if (arg0->unk15 != 0) {
        arg0->unk20 = FIXED(1.375);
    } else {
        arg0->unk20 = FIXED(-1.375);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089FD4);

void func_8008A024(struct MainObj* arg0)
{
    s32 var_v1;
    u8 temp_a1;

    temp_a1 = arg0->ext.main_71.unk8A;
    if (temp_a1 != 0) {
        var_v1 = arg0->ext.main_71.unk84 << 8;
        if (!(temp_a1 & 1)) {
            var_v1 = -var_v1;
        }
        arg0->unk20 = var_v1;
    }
}

void func_8008A05C(void)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A064);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A180);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A2E0);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A3B0);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A4D8);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A60C);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A778);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A8E4);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A9F4);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008AAF4);

void func_8008AC20(struct MainObj* arg0)
{
    func_80089F58(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008AC40);

void func_8008AD48(struct MainObj* arg0)
{
    arg0->unk42 &= 0x7FFF;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8008AD74(void)
{
}

void func_8008AD7C(void)
{
}

void func_8008AD84(struct MainObj* arg0)
{
    D_80104D28[arg0->unk5](arg0);
}

void func_8008ADC0(struct MainObj* arg0)
{
    D_80104D34[arg0->state](arg0);
}
