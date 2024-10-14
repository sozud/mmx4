#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D514C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5210);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5230);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D526C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D52F4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D54A0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D54E0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5500);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D553C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5578);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D55E4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D56A8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D56C8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D57A8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5934);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5AB0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5BF8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5C18);

// megaman never appears in intro stage if nopped out
void func_800D5C54(struct QuadObj* arg0)
{
    D_8010FC84[arg0->state]();
}

// D_8010FC84 state 0
void func_800D5C90(struct QuadObj* arg0)
{
    arg0->active |= 0x92;
    if (arg0->unk2 == 0) {
        arg0->unk36 = 0x10;
    } else {
        arg0->unk36 = 0x13;
    }
    arg0->unk34 = 5;
    arg0->state = 1;
    arg0->unk37 = -1;
    arg0->x_pos.val = 0;
    arg0->y_pos.val = 0;
    arg0->unk14.val = 0;
    arg0->unk18.val = 0;
    arg0->unk1C.val = 0;
    arg0->unk20.val = 0;
    arg0->unk24.val = 0;
    arg0->unk28.val = 0;
    arg0->unk2C.val = 0;
    arg0->unk30.val = 0;
}

// D_8010FC84 state 1
// "READY" never appears if noppped out
//  asm(".rept 20 ; nop ; .endr");
void func_800D5CF8(struct QuadObj* arg0)
{
    D_8010FC90[arg0->unk2](arg0);
    arg0->unk3 = 1;
    func_8002B458(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5D50);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5F1C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6260);

void func_800D6494(struct Unk22* arg0)
{
    arg0->unk8 += arg0->unk38;
    arg0->unkC += arg0->unk3C;
    arg0->unk38 += arg0->unk40;
    arg0->unk3C += arg0->unk44;
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D64D8);

// D_8010FC84 state 2
void func_800D666C(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D668C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6694);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6700);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6780);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D67A0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D67DC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D68D0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6944);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D69A8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6AD8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6B9C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6C48);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6CA0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6D48);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6DC4);
