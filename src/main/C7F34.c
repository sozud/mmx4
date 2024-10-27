#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7734);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D784C);

void func_800D7960(struct QuadObj* arg0)
{
    struct MiscObj* misc;
    if (--(arg0->unk38.utwo.lo) == 0) {
        if (arg0->unk2 == 0) {
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->base.active = 1;
                misc->base.id = 0x13;
                misc->base.unk2 = 0xB;
            }
        }
        arg0->state++;
    }
    quad_is_on_screen(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D79F0);

void func_800D7A10(struct QuadObj* arg0)
{
    D_8010FE10[arg0->state](arg0);
}

void func_800D7A4C(struct QuadObj* arg0)
{
}

void func_800D7A54(struct QuadObj* arg0)
{
    D_8010FE20[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7A90);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7AF8);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7B50);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7B70);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7BBC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7C3C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7C70);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7D60);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7DA4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7EA8);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7F64);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7FD0);

void func_800D7FF0(struct QuadObj* arg0)
{
    D_8010FE48[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D802C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8150);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8180);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8290);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D82E8);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D83DC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D842C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D845C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8578);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D85C8);

void func_800D85E8(struct QuadObj* arg0)
{
    struct PlayerObj* temp_v1;

    temp_v1 = arg0->unk5C;
    if (temp_v1->unk94 != 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        temp_v1->unk95 = 0;
    }
    D_8010FEF0[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8648);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8684);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D872C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D87C0);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D87E0);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8820);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8834);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8844);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8884);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D88E4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8934);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8974);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D89D4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8A24);

void func_800D8A64(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8A6C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8ABC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8AFC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8B5C);

void func_800D8BAC(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8BB4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8C24);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8C84);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8CF4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8E40);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8E94);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8ED4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8F10);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8F48);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8F9C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8FDC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9008);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9050);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9090);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D90BC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D90CC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D910C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9138);

void func_800D91A0(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D91A8);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9218);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9268);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9330);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D93FC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D941C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D945C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9470);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9480);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D94FC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D95F4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D964C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9728);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9768);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D97F4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D986C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D98AC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D98C0);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D98D0);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9910);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9924);

void func_800D9934(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D993C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D99B0);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9A04);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9A58);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9B08);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9B48);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9C84);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA05C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA098);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA0EC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA140);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA160);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA1A0);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA1B4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA1C4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA204);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA218);

void func_800DA228(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA230);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA298);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA2D4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA358);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA478);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA498);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA4D8);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA4EC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA4FC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA53C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA550);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA560);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA5A0);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA5B4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA5C4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA600);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA6A4);

void func_800DA748(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA750);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA7FC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA818);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA878);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA8B4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA90C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA964);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA984);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DAB40);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DAB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DABE4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DADA0);

void func_800DAE84(void)
{
}
