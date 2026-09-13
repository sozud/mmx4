// MainObj, main_object_update_funcs[33]
// 8005D1F4..8005E570
#include "common.h"

void func_8005D1F4(struct MainObj* arg0)
{
    D_800FDF54[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005D230);

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005D348);

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005D4E0);

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005D7E8);

void func_8005D844(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_33.saved_unk5;
}

void func_8005D850(struct MainObj* arg0)
{
    D_800FDF80[arg0->unk6](arg0);
}

void func_8005D88C(struct MainObj* arg0)
{
    arg0->unk7C = 0xB4;
    if (arg0->unk15 == 0) {
        arg0->unk20 = FIXED(-2.5);
    } else {
        arg0->unk20 = FIXED(2.5);
    }
    arg0->unk6 = 1;
}

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005D8B8);

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005D9C4);

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005DAB8);

void func_8005DB84(struct MainObj* arg0)
{
    D_800FDF8C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005DBC0);

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005DC58);

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005DED4);

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005DF84);

void func_8005E044(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, 0x53, arg0);
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk24 = FIXED(4);
        arg0->unk20 = 0;
        func_8001540C(2, 0x54, arg0);
        func_80015D60(arg0, 6);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_8005E0CC(struct MainObj* arg0)
{
    D_800FDFA0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005E108);

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005E1BC);

INCLUDE_ASM("main/nonmatchings/mains/main_33", func_8005E298);

void func_8005E3E8(struct MainObj* arg0)
{
    D_800FDFAC[arg0->unk6](arg0);
}

void func_8005E424(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk7E = 3;
        arg0->unk6 = 1;
    }
}

void func_8005E47C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7E == 0) {
        func_8001540C(0, 0xE, NULL);
        arg0->unk7E = 3;
    }
    if (++arg0->unk5C == 0x30) {
        arg0->unk6 = 2;
        arg0->unk7C = 0x3C;
    }
}

void func_8005E500(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_800DABE4(0, 0x1340, 0x2A0);
        arg0->ext.main_33.unk85 = 0;
        func_80036B18();
        func_80015D60(arg0, 2);
        arg0->unk5 = 4;
        arg0->unk6 = 0;
    }
}
