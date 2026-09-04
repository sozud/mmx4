// MiscObj, misc_object_update_funcs[57]
// 800D3388..800D3928
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_57", func_800D3388);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_57", func_800D34AC);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_57", func_800D34F0);

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_57", func_800D3510);

void func_800D354C(struct UnkObj* arg0)
{
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32 temp_v1;

    arg0->unk40 = 0x1F00;
    temp_v1 = *addr_801F3000;
    arg0->base.bg_offset = -1;
    arg0->unk3C = temp_v1 + (s32)addr_801F3000;
    arg0->base.unk15 = 0;
    if (arg0->base.y_pos.i.hi == 0x10) {
        arg0->unk42 = 0x7802;
    } else {
        arg0->unk42 = 0x7800;
    }
    arg0->base.x_pos.i.hi = 0xA0;
    arg0->base.unk16 = 0;
    arg0->unk47 = arg0->base.unk2;
    arg0->base.state++;
    if (arg0->base.unk2 < 9) {
        arg0->base.state++;
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
    arg0->base.bg_offset = -1;
    arg0->unk3C = temp_v1 + (s32)addr_801F3000;
    arg0->base.unk15 = 0;
    if (arg0->base.unk2 == -1) {
        arg0->unk42 = 0x7806;
        arg0->base.y_pos.i.hi = arg0->unk50[D_80141BDF[0] * 2] + 8;
        arg0->unk54 = D_80141BDF[0];
        func_80015D60(arg0, 0);
    } else {
        arg0->unk42 = 0x784B;
        arg0->base.x_pos.i.hi = 0x60;
        arg0->base.y_pos.i.hi = 0xD0;
        arg0->unk47 = 0x29;
    }
    arg0->base.unk16 = 0;
    arg0->base.state = 3;
}

void func_800D36AC(struct UnkObj* arg0)
{
    if (arg0->base.unk2 < 0) {
        func_800D35D0(arg0);
    } else {
        func_800D354C(arg0);
    }
    is_on_screen(arg0);
}

void func_800D3700(struct UnkObj* arg0)
{
    s8 temp_v1; // probably fake

    if (arg0->base.y_pos.i.hi != 0x10) {
        if (arg0->base.unk7 == D_80141BDF[0]) {
            arg0->unk42 = 0x7803;
        } else {
            arg0->unk42 = 0x7800;
        }
    }
    if ((D_80141BE0 == 0) && (engine_obj.cur_character != CHARACTER_X)) {
        temp_v1 = arg0->base.unk7;
        if ((arg0->base.unk7 < 7) && (temp_v1 >= 5)) {
            arg0->unk42 = 0x7804;
        }
    }
    is_on_screen(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/misc/misc_57", func_800D3798);

void func_800D38A0(struct UnkObj* arg0)
{
    if (arg0->base.unk2 == -1) {
        if (arg0->unk54 != D_80141BDF[0]) {
            arg0->base.y_pos.i.hi = arg0->unk50[D_80141BDF[0] * 2] + 8;
            arg0->unk54 = D_80141BDF[0];
        }
        func_80015DC8(arg0, D_80141BDF);
    }
    is_on_screen(arg0);
}
