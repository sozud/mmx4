#include "common.h"

struct Unk8010E71C {
    s16 x;
    s16 y;
    s8 unk;
    s8 unk2;
};

extern struct Unk8010E71C D_8010E71C[];
extern s32* D_8010E81C[];

// g_TitleUpdateFuncs state 0
void func_800CB634(struct MiscObj* arg0)
{
    u8 temp_a1 = arg0->base.unk2;
    u8 temp_v1;

    arg0->unk30 = &D_8010E81C;
    arg0->base.bg_offset = -1;
    arg0->base.unk15 = 0;
    arg0->base.unk16 = 3;
    arg0->base.state++;

    arg0->unk40 = 0x600;
    arg0->unk3C = *(s32*)0x1F80003C;
    temp_v1 = D_8010E71C[temp_a1].unk2;
    arg0->unk42 = ((temp_v1 & 0xF) | (((temp_v1 >> 4) + 0x1E0) << 6));
    // for unk2 == 0, setting position of "MEGAMAN" text
    // for unk2 == 1, didn't notice a difference
    // for unk2 == 2, setting position of greyed out "GAME START" text
    arg0->base.x_pos.val = FIXED(D_8010E71C[temp_a1].x);
    arg0->base.y_pos.val = FIXED(D_8010E71C[temp_a1].y);
    arg0->unk47 = D_8010E71C[temp_a1].unk;
    is_on_screen(arg0);
}

// g_TitleUpdateFuncs state 1
INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CB708);

// g_TitleUpdateFuncs state 2
void func_800CB828(struct MiscObj* arg0)
{
    ZeroObjectState(arg0);
}

// title object. Includes the logo and the menu graphics
void TitleUpdate(struct MiscObj* arg0)
{
    g_TitleUpdateFuncs[arg0->base.state]();
}

void func_800CB884(struct MiscObj* arg0)
{
    if (arg0->base.state == 0) {
        arg0->base.on_screen = 1;
        arg0->base.bg_offset = -1;
        arg0->unk47 = 0;
        arg0->unk3C = *(void**)0x1F80001C;
        arg0->unk40 = 0x600;
        arg0->unk42 = 0x7804;
        arg0->base.x_pos.i.hi = 0xA0;
        arg0->unk38 = 0;
        arg0->unk30 = 0;
        arg0->base.unk15 = 0;
        arg0->base.unk16 = 0;
        arg0->base.y_pos.i.hi = 0x78;
        arg0->base.state++;
    }
}

void func_800CB8F8(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    D_8010E830[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CB940);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CB9C4);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CBA5C);

// misc obj update #22
void func_800CBA80(struct MiscObj* arg0)
{
    u8* ptr;

    switch (arg0->base.unk2) {
    case 0:
        is_on_screen(arg0);
        return;
    case 1:
        if ((u8)controller_state == 0) {
            if (--arg0->ext.unk.unk56.sht == 0) {
                arg0->ext.unk.unk56.sht = 0x20;
                arg0->ext.unk.unk54 ^= 1;
            }
            if (arg0->ext.unk.unk54) {
                arg0->base.on_screen = 0;
                return;
            }
            is_on_screen(arg0);
            return;
        }
        ZeroObjectState(arg0);
        return;
    case 2:
        if (abc_object.unkC != 0) {
            if (abc_object.unkD == 0 || abc_object.unkD == 4) {
                func_80015DC8(arg0);
            }
            is_on_screen(arg0);
            return;
        }
        ZeroObjectState(arg0);
        return;
    case 3:
        ptr = abc_object.unkE + &arg0->ext.unk.unk50->unk0;
        if (*ptr != 0 && (abc_object.unkC == 1)) {
            if (arg0->ext.unk.unk55 == 0) {
                func_80015D60(arg0, 1);
                arg0->ext.unk.unk55 = 1;
            } else {
                func_80015DC8(arg0);
                if (arg0->unk45 != 0) {
                    arg0->ext.unk.unk55 = 0;
                }
            }
        } else if (arg0->ext.unk.unk55 != 0) {
            func_80015DC8(arg0);
            if (arg0->unk45 != 0) {
                arg0->ext.unk.unk55 = 0;
                func_80015D60(arg0, 0);
            }
        } else {
            func_80015D60(arg0, 0);
        }
        is_on_screen(arg0);
        return;
    case 4:
        func_80015DC8(arg0);
        is_on_screen(arg0);
        return;
    case 5:
        ptr = abc_object.unkE + &arg0->ext.unk.unk50->unk0;
        if ((*ptr == 0) && (abc_object.unkC == 1)) {
            if (arg0->ext.unk.unk55 == 0) {
                func_80015D60(arg0, arg0->ext.unk.unk54 + 1);
                arg0->ext.unk.unk55 = 1;
            } else {
                func_80015DC8(arg0);
                if (arg0->unk45 != 0) {
                    arg0->ext.unk.unk55 = 0;
                }
            }
        } else if (arg0->ext.unk.unk55) {
            func_80015DC8(arg0);
            if (arg0->unk45 != 0) {
                arg0->ext.unk.unk55 = 0;
                func_80015D60(arg0, arg0->ext.unk.unk54);
            }
        } else {
            func_80015D60(arg0, arg0->ext.unk.unk54);
        }
        is_on_screen(arg0);
        return;
    case 8:
        if (arg0->base.unk5 == 0) {
            func_80015DC8(arg0);
            if (--arg0->ext.unk.unk56.byte == 0) {
                arg0->base.unk5 = 1;
            }
            if (arg0->base.unk6) {
                arg0->base.x_pos.val = arg0->ext.unk.unk50->x_pos.val;
                arg0->base.y_pos.val = arg0->ext.unk.unk50->y_pos.val;
            }
            is_on_screen(arg0);
            return;
        }
        arg0->base.on_screen = 0;
        ZeroObjectState(arg0);
        return;
    }
}

void func_800CBD40(struct MiscObj* arg0)
{
    if (arg0->base.state == 0) {
        func_800CBD80(arg0);
    } else {
        func_800CBE34(arg0);
    }
}

void func_800CBD80(struct MiscObj* arg0)
{
    arg0->base.on_screen = 1;
    arg0->unk38 = 0;
    arg0->unk3C = *(u8**)0x1F80001C + (*(u32**)0x1F80001C)[2];
    arg0->unk30 = &D_8010A4C0;
    arg0->unk40 = 0;
    if (arg0->ext.unk.unk54 != 2) {
        arg0->unk42 = 0x7805;
    } else {
        arg0->unk42 = 0x7806;
    }
    if (arg0->base.unk7 == 0) {
        arg0->base.unk16 = 1;
    }
    func_80015D60(arg0, arg0->ext.unk.unk54);
    arg0->base.state++;
    arg0->base.unk7 = get_random() & 1;
    is_on_screen(arg0);
}

void func_800CBE34(struct MiscObj* arg0)
{
    func_8002B718(arg0);
    func_80015DC8(arg0);
    if (arg0->unk46 == 0) {
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->ext.unk.unk54 = 0;
        ZeroObjectState(arg0);
    } else {
        arg0->base.on_screen = 0;
        if (((arg0->ext.unk.unk54 & 3) && !(arg0->ext.unk.unk54 & 1)) || (D_80141BD8.unk0 & 1) == arg0->base.unk7) {
            is_on_screen(arg0);
        }
    }
}

void func_800CBECC(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    D_8010E90C[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CBF14);

void func_800CC040(struct MiscObj* arg0)
{
    D_8010E918[arg0->base.unk5](arg0);
    if (func_8002B160(arg0) == 0) {
        is_on_screen(arg0);
    } else {
        arg0->base.state = 2;
    }
}

void func_800CC0AC(struct MiscObj* arg0)
{
    D_8010E924[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC0E8);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC114);

void func_800CC1F8(struct MiscObj* arg0)
{
    D_8010E92C[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC234);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC304);

void func_800CC350(struct MiscObj* arg0)
{
    D_8010E934[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC38C);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC3D4);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC418);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC460);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC4E0);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC738);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC79C);

void func_800CC7BC(struct MiscObj* arg0)
{
    D_8010E958[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC7F8);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC8E8);

void func_800CC908(struct MiscObj* arg0)
{
    D_8010E960[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CC944);

INCLUDE_ASM("asm/us/main/nonmatchings/BBE34", func_800CCA14);