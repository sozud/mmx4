// MiscObj, misc_object_update_funcs[57]
// 800D3388..800D3928
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_57", func_800D3388);

INCLUDE_ASM("main/nonmatchings/misc/misc_57", func_800D34AC);

void func_800D34F0(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800D3510(struct MiscObj* arg0)
{
    D_8010F5BC[arg0->state](arg0);
}

void func_800D354C(struct UnkObj* arg0)
{
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32 temp_v1;

    arg0->unk40 = 0x1F00;
    temp_v1 = *addr_801F3000;
    arg0->bg_offset = -1;
    arg0->unk3C = temp_v1 + (s32)addr_801F3000;
    arg0->unk15 = 0;
    if (arg0->y_pos.i.hi == 0x10) {
        arg0->unk42 = 0x7802;
    } else {
        arg0->unk42 = 0x7800;
    }
    arg0->x_pos.i.hi = 0xA0;
    arg0->unk16 = 0;
    arg0->animation_step.fields.frame_index = arg0->unk2;
    arg0->state++;
    if (arg0->unk2 < 9) {
        arg0->state++;
    }
}

void func_800D35D0(struct UnkObj* arg0)
{
    s32* addr_801F3000 = (s32*)0x801F3000;
    s32* addr_801F3008 = (s32*)0x801F3008;
    u32 temp_v1;

    arg0->unk40 = 0x1E00;
    arg0->animation_table = D_8010ECD4;
    temp_v1 = *addr_801F3008;
    arg0->bg_offset = -1;
    arg0->unk3C = temp_v1 + (s32)addr_801F3000;
    arg0->unk15 = 0;
    if (arg0->unk2 == -1) {
        arg0->unk42 = 0x7806;
        arg0->y_pos.i.hi = arg0->link.data[D_80141BDF[0] * 2] + 8;
        arg0->ext.timer = D_80141BDF[0];
        func_80015D60(arg0, 0);
    } else {
        arg0->unk42 = 0x784B;
        arg0->x_pos.i.hi = 0x60;
        arg0->y_pos.i.hi = 0xD0;
        arg0->animation_step.fields.frame_index = 0x29;
    }
    arg0->unk16 = 0;
    arg0->state = 3;
}

void func_800D36AC(struct UnkObj* arg0)
{
    if (arg0->unk2 < 0) {
        func_800D35D0(arg0);
    } else {
        func_800D354C(arg0);
    }
    is_on_screen(arg0);
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
    if ((D_80141BE0 == 0) && (engine_obj.cur_character != CHARACTER_X)) {
        temp_v1 = arg0->unk7;
        if ((arg0->unk7 < 7) && (temp_v1 >= 5)) {
            arg0->unk42 = 0x7804;
        }
    }
    is_on_screen(arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_57", func_800D3798);

void func_800D38A0(struct UnkObj* arg0)
{
    if (arg0->unk2 == -1) {
        if (arg0->ext.timer != D_80141BDF[0]) {
            arg0->y_pos.i.hi = arg0->link.data[D_80141BDF[0] * 2] + 8;
            arg0->ext.timer = D_80141BDF[0];
        }
        func_80015DC8(arg0);
    }
    is_on_screen(arg0);
}

union AnimationStep D_8010F5A0[6] = {
    { .packed = 0x00010001 },
    { .packed = 0x01010001 },
    { .packed = 0x02010001 },
    { .packed = 0x03010001 },
    { .packed = 0x04010001 },
    { .packed = 0x05000001 },
};
union AnimationStep* D_8010F5B8[1] = { D_8010F5A0 };

void (*D_8010F5BC[3])(struct MiscObj*) = {
    func_800D3388,
    func_800D34AC,
    func_800D34F0,
};

u16 D_8010F5C8[8] = { 0x10, 0x80, 0x100, 0x40, 0x20, 0x200, 0x400, 0 };
u16 D_8010F5D8[8] = { 0x80, 0x10, 0x40, 0x20, 4, 1, 8, 2 };
