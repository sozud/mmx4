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

// TitleUpdate2 state 0
extern s16 D_8010FCCC[1][8];
extern u16 D_8010FD94[];

void func_800D6F94(struct QuadObj* entity)
{
    u16* ptr;
    u16 temp;

    entity->unk37 = -1;
    entity->unk42 = 1;
    entity->x_pos.i.hi = 0;
    entity->y_pos.i.hi = 0;
    entity->active |= 0x80;

    ptr = D_8010FCCC[entity->unk2];
    entity->unk14.i.hi = *ptr++;
    entity->unk18.i.hi = *ptr++;
    entity->unk1C.i.hi = *ptr++;
    entity->unk20.i.hi = *ptr++;
    entity->unk24.i.hi = *ptr++;
    entity->unk28.i.hi = *ptr++;
    entity->unk2C.i.hi = *ptr++;
    entity->unk30.i.hi = *ptr;

    temp = D_8010FD94[0];
    entity->unk36 = 0x10;
    entity->state = 3;
    entity->unk38 = 0x14;
    entity->unk43 = 0;
    entity->unk34 = temp;
}

// TitleUpdate2 state 1
INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7058);

// TitleUpdate2 state 3
void func_800D7100(struct QuadObj* arg0)
{
    // seems to be a timer before the white Quad appears
    if (arg0->unk38 != 0) {
        arg0->unk38--;
        return;
    }
    arg0->unk38 = 3;
    func_800D46F4(arg0);
    arg0->state = 4;
}

// TitleUpdate2 state 4
void TitleSetWhiteQuadSpeed(struct Unk* arg0)
{
    if (D_80173C7A == 2) {
        arg0->animation_speed = 0x2C; // sets animation speed of white quad that transforms into "MEGAMAN"
        arg0->base.state = 5;
    }
    func_800D46F4();
}

// TitleUpdate2 state 5
INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7194);

// TitleUpdate2 state 6
INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7468);

// TitleUpdate2 state 2
void func_800D76D8(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

// title screen doesn't appear if nopped out
void TitleUpdate2(struct QuadObj* arg0)
{
    g_TitleUpdate2Funcs[arg0->state]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7734);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D784C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7960);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D79F0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7A10);

void func_800D7A4C(struct QuadObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7A54);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7A90);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7AF8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7B50);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7B70);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7BBC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7C3C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7C70);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7CEC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7D60);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7DA4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7EA8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7F64);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7FD0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D7FF0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D802C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8150);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8180);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8290);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D82E8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D83DC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D842C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D845C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8578);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D85C8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D85E8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8648);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8684);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D872C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D87C0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D87E0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8820);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8834);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8844);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8884);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D88E4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8934);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8974);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D89D4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8A24);

void func_800D8A64(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8A6C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8ABC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8AFC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8B5C);

void func_800D8BAC(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8BB4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8C24);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8C84);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8CF4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8E40);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8E94);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8ED4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8F10);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8F48);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8F9C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D8FDC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9008);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9050);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9090);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D90BC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D90CC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D910C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9138);

void func_800D91A0(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D91A8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9218);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9268);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9330);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D93FC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D941C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D945C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9470);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9480);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D94FC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D95F4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D964C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9728);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9768);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D97F4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D986C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D98AC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D98C0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D98D0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9910);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9924);

void func_800D9934(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D993C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D99B0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9A04);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9A58);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9B08);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9B48);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D9C84);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA05C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA098);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA0EC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA140);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA160);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA1A0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA1B4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA1C4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA204);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA218);

void func_800DA228(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA230);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA298);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA2D4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA358);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA478);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA498);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA4D8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA4EC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA4FC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA53C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA550);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA560);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA5A0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA5B4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA5C4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA600);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA6A4);

void func_800DA748(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA750);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA7C0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA7FC);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA818);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA878);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA8B4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA90C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA964);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DA984);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DAB40);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DAB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DABE4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800DADA0);

void func_800DAE84(void)
{
}
