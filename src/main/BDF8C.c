#include "common.h"

// TitleLogoUpdate state 0
INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CD78C);

// TitleLogoUpdate state 1
INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CD90C);

// TitleLogoUpdate state 2
INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CD974);

// TitleLogoUpdate state 3
INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CDA90);

// TitleLogoUpdate state 4
INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CDAD0);

// TitleLogoUpdate state 5
void func_800CDB10(struct MiscObj* arg0)
{
    func_80015DC8();
    // transition "MEGAMAN" to white before full logo appears
    if (arg0->unk46 == 0) {
        arg0->palette2 = (s32)(*(s32*)SP_PALETTE_ADDR + 0x200);
        arg0->palette1 = (s32) * (s32*)0x1F800030;
        // interval to shift on
        arg0->palette_shift_speed = 2;
        // how much to shift each step
        arg0->palette_shift_value = 0xF;
        arg0->state++;
    }
    func_8002B288(arg0);
}

// TitleLogoUpdate state 6
INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CDB84);

// TitleLogoUpdate state 7
INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CDC34);

// part of the title logo animation
void TitleLogoUpdate(struct MiscObj* arg0)
{
    arg0->unk3 = 0;
    g_TitleLogoUpdateFuncs[arg0->state]();
}

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CDCC0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CDCFC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CDE24);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CDE44);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CDF4C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE080);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE0D8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE114);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE1D4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE304);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE340);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE388);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE670);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE6AC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE6CC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE754);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE7C8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE81C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE894);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CE8DC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CEA40);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CEAC8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CEAE8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CEB44);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CEBC0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CEE30);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CEE6C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CEEC4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CEF34);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CEFC0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF0B0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF144);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF184);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF268);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF2B8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF300);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF428);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF498);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF4B8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF5F0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF640);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF660);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF708);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF754);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF790);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF7CC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF824);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF844);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF898);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF8F0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CF950);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CFAC8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CFB20);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CFB70);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CFC6C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CFD38);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CFE00);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CFE3C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CFE5C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CFE98);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800CFEE0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0118);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0374);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D03B0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D04D0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0528);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0548);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D05B0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D05F4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0658);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0698);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D06E0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0754);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D07C0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D07EC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0828);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0988);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D09E4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0A04);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0AA4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0B14);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0B68);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0B90);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0BE4);

void func_800D0C60(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0C68);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0D68);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D0E48);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1060);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D10E4);

void func_800D115C(void)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1164);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D11B0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D11CC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1228);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1248);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1284);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D12C0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1464);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D14D8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D14F8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D154C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D15A8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1614);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D166C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D16E0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1708);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D177C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D17F0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1864);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D188C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D18C0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1990);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1A48);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1AE8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1B08);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1B44);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1CF8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1D38);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1D58);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1D88);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1DC4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1E0C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1E9C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1F04);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1F24);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1F74);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D1FB8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2010);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2030);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2094);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D212C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2190);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2420);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D24B4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D254C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D25AC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D25FC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D26F4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2794);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2854);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D28BC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D28E8);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2924);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2970);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D29C0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D29FC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2A38);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2A74);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2B9C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2C04);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2CA4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2D7C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2DCC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2E1C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2E64);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2EDC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2F34);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D2FC4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D301C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D3048);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D3084);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D31F8);

void func_800D323C(struct Unk* arg0)
{
    func_8002B694();
    func_80015DC8(arg0);
    func_8002B288(arg0);
    if (func_8002B160(arg0) != 0) {
        arg0->state = 2;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D3288);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D330C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D332C);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D3388);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D34AC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D34F0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D3510);

void func_800D354C(struct UnkObj* arg0)
{
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32 temp_v1;

    arg0->unk40 = 0x1F00;
    temp_v1 = *addr_801F3000;
    arg0->unk14 = -1;
    arg0->unk3C = temp_v1 + (s32)addr_801F3000;
    arg0->unk15 = 0;
    if (arg0->y_pos.i.hi == 0x10) {
        arg0->unk42 = 0x7802;
    } else {
        arg0->unk42 = 0x7800;
    }
    arg0->x_pos.i.hi = 0xA0;
    arg0->unk16 = 0;
    arg0->unk47 = arg0->unk2;
    arg0->unk4++;
    if (arg0->unk2 < 9) {
        arg0->unk4++;
    }
}

void func_800D35D0(struct UnkObj* arg0)
{
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32* addr_801F3008 = (s32*)0x801F3008;
    u32 temp_v1;

    arg0->unk40 = 0x1E00;
    arg0->unk30 = D_8010ECD4;
    temp_v1 = *addr_801F3008;
    arg0->unk14 = -1;
    arg0->unk3C = temp_v1 + (s32)addr_801F3000;
    arg0->unk15 = 0;
    if (arg0->unk2 == -1) {
        arg0->unk42 = 0x7806;
        arg0->y_pos.i.hi = arg0->unk50[D_80141BDF[0] * 2] + 8;
        arg0->unk54 = D_80141BDF[0];
        func_80015D60(arg0, 0);
    } else {
        arg0->unk42 = 0x784B;
        arg0->x_pos.i.hi = 0x60;
        arg0->y_pos.i.hi = 0xD0;
        arg0->unk47 = 0x29;
    }
    arg0->unk16 = 0;
    arg0->unk4 = 3;
}

void func_800D36AC(struct UnkObj* arg0)
{
    if (arg0->unk2 < 0) {
        func_800D35D0(arg0);
    } else {
        func_800D354C(arg0);
    }
    func_8002B288(arg0);
}

void func_800D3700(struct UnkObj* arg0)
{
    s8 temp_v1; // probably fake

    if (arg0->y_pos.i.hi != 0x10) {
        if (arg0->unk7 == D_80141BDF[0]) {
            arg0->unk42 = 0x7803;
        } else {
            arg0->unk42 = 0x7800;
        }
    }
    if ((D_80141BE0 == 0) && (D_80172203.unk0 != 0)) {
        temp_v1 = arg0->unk7;
        if ((arg0->unk7 < 7) && (temp_v1 >= 5)) {
            arg0->unk42 = 0x7804;
        }
    }
    func_8002B288(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D3798);

void func_800D38A0(struct UnkObj* arg0)
{
    if (arg0->unk2 == -1) {
        if (arg0->unk54 != D_80141BDF[0]) {
            arg0->y_pos.i.hi = arg0->unk50[D_80141BDF[0] * 2] + 8;
            arg0->unk54 = D_80141BDF[0];
        }
        func_80015DC8(arg0, D_80141BDF);
    }
    func_8002B288(arg0);
}

void func_800D3928(struct UnkObj* arg0)
{
    arg0->unk3 = 0;
    D_8010F5E8[arg0->unk4]();
}

void func_800D3964(struct UnkObj* arg0)
{
    s16 var_v0;
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32 temp_v1;

    arg0->unk40 = 0x1F00;
    temp_v1 = *addr_801F3000;
    arg0->unk14 = -1;
    arg0->unk3C = temp_v1 + (s32)addr_801F3000;
    arg0->unk15 = 0;
    if (arg0->y_pos.i.hi == 0x10) {
        arg0->unk42 = 0x7802;
    } else {
        arg0->unk42 = 0x7800;
    }
    arg0->x_pos.i.hi = 0xA0;
    arg0->unk16 = 0;
    arg0->unk47 = arg0->unk2;
    arg0->unk4++;
    func_8002B288(arg0);
}

void func_800D39EC(struct UnkObj* arg0)
{
    s8 temp_v1; // probably fake

    if (arg0->y_pos.i.hi != 0x10) {
        if (arg0->unk7 == D_80141BDF[0]) {
            arg0->unk42 = 0x7803;
        } else {
            arg0->unk42 = 0x7800;
        }
    }
    if ((D_80141BE0 == 0) && (D_80172203.unk0 != 0)) {
        temp_v1 = arg0->unk7;
        if ((arg0->unk7 < 7) && (temp_v1 >= 5)) {
            arg0->unk42 = 0x7804;
        }
    }
    func_8002B288(arg0);
}

void func_800D3A84(struct UnkObj* arg0)
{
    arg0->unk3 = 0;
    D_8010F5F8[arg0->unk4]();
}

// search lights in background of intro stage
void SearchLightUpdate(struct QuadObj* arg0)
{
    g_SearchLightUpdateFuncs[arg0->state]();
}

// SearchLight state 0
INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D3AFC);

// SearchLight state 1
INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D3C58);

// SearchLight state 2
INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D3FBC);

void func_800D3FE0(struct Unk22* arg0)
{
    arg0->unk48 += arg0->unk38;
    arg0->unk4C += arg0->unk40;
    arg0->unk38 += arg0->unk3C;
    arg0->unk40 += arg0->unk44;
}

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D4024);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D41B0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D41EC);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D4334);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D43F4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D46D4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D46F4);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D4948);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D4984);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D4A64);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D4B30);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D4C14);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D4C50);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D4DE0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D4F84);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D4FA0);

INCLUDE_ASM("asm/us/main/nonmatchings/BDF8C", func_800D5144);
