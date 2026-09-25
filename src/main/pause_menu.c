// BarObj, bar_object
// 8002FCAC..800311EC
#include "common.h"

extern u8 D_800F48EC[8];

void func_8002FCAC(void)
{
    struct BarObj* bar = &bar_object;
    D_800F48D4[bar_object.state](bar);
}

void func_8002FCEC(struct BarObj* arg0)
{
    D_800F48E0[arg0->unk5](arg0);
}

void func_8002FD28(struct BarObj* arg0)
{
    func_80015930(0xFF, 0);
    func_800129F0(8);
    func_80023D68();
    arg0->unk5 = 1;
}

INCLUDE_ASM("main/nonmatchings/pause_menu", func_8002FD70);

void func_800300AC(struct BarObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->state = 1;
        arg0->unk5 = 0;
        if (g_Player.unk2 || arg0->unk2) {
            if (arg0->unk14 >= 0xD) {
                arg0->unk5 = 2;
            } else {
                arg0->unk5 = 1;
            }
        }
    }
    func_80023D90();
}

void func_80030128(struct BarObj* arg0)
{
    if (controller_state & PADselect) {
        if (arg0->unk5 < 3) {
            arg0->unk28 = arg0->unk5;
            arg0->unk5 = 6;
            arg0->unk6 = 0;
        }
    }
    D_800F48F4[arg0->unk5](arg0);
    if (arg0->unk5 < 5) {
        func_80023D90();
    }
}

INCLUDE_ASM("main/nonmatchings/pause_menu", func_800301BC);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_800304E4);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80030728);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80030A2C);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80030C54);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80030DF8);

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80030EC8);

void func_80030F9C(struct BarObj* arg0)
{
    D_800F4910[arg0->unk5](arg0);
}

void func_80030FD8(struct BarObj* arg0)
{
    func_800129F0(8);
    func_80023D90();
    arg0->unk5 = 1;
}

void func_80031014(struct BarObj* arg0)
{
    if (D_80141BDC[0] != 0) {
        func_80023D90();
    } else {
        func_800170E0();
        arg0->unk5 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/pause_menu", func_80031064);

void func_80031130(struct BarObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (arg0->unk30 == 0) {
            engine_obj.unk1 = 0;
            arg0->state = 0;
        } else {
            engine_obj.state = 9;
            engine_obj.unk1 = 0;
            engine_obj.unk2 = 0;
            engine_obj.unk10 = 0;
            engine_obj.unk11 = 0;
            engine_obj.unk12 = 0;
            engine_obj.unk13 = 0;
            engine_obj.unk14 = 0;
            engine_obj.unk15 = 0;
            engine_obj.unk16 = 0;
            engine_obj.unk17 = 0;
            arg0->state = 0;
        }
        arg0->unk5 = 0;
    }
    if (arg0->unk30 == 0) {
        func_80023D68();
    }
}

void (*D_800F48D4[3])(struct BarObj*) = {
    func_8002FCEC,
    func_80030128,
    func_80030F9C,
};

void (*D_800F48E0[3])(struct BarObj*) = {
    func_8002FD28,
    func_8002FD70,
    func_800300AC,
};

u8 D_800F48EC[8] = { 2, 6, 1, 4, 3, 0, 5, 7 };

void (*D_800F48F4[7])(struct BarObj*) = {
    func_800301BC,
    func_800304E4,
    func_80030728,
    func_80030A2C,
    func_80030C54,
    func_80030DF8,
    func_80030EC8,
};

void (*D_800F4910[4])(struct BarObj*) = {
    func_80030FD8,
    func_80031014,
    func_80031064,
    func_80031130,
};
