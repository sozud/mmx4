#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7734);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D784C);

void func_800D7960(struct QuadObj* arg0)
{
    struct MiscObj* misc;
    if (--(arg0->ext.unk_ext.unk38) == 0) {
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

void func_800D8648(struct LayerObj* arg0)
{
    D_8010FF08[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8684);

void func_800D872C(struct LayerObj* arg0)
{
    arg0->base.unk15 = arg0->base.bg_offset;
    func_800D8BB4(arg0);
    D_8010FF14[arg0->base.unk5](arg0);
    func_800D8E40(arg0);
    background_objects[1].x_pos.val += arg0->unk18.val;
    background_objects[2].x_pos.val += arg0->unk18.val >> 1;
}

void func_800D87C0(struct LayerObj* arg0)
{
    func_8002B108(arg0);
}

void func_800D87E0(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D8820(arg0);
    } else {
        func_800D8834(arg0);
    }
}

void func_800D8820(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800D8834(struct LayerObj* arg0)
{
    arg0->base.unk5 = 5;
    arg0->base.unk6 = 0;
}

void func_800D8844(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D8884(arg0);
    } else {
        func_800D88E4(arg0);
    }
}

void func_800D8884(struct LayerObj* arg0)
{
    if (func_800D8E94(arg0)) {
        background_objects[0].unk24 = 0x8D0;
        background_objects[0].unk26 = 0x8D0;
        func_80036AE4(0x14, 0x40);
        arg0->base.unk7 = 0;
        arg0->base.unk6++;
    }
}

void func_800D88E4(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        D_8010FF2C[arg0->base.unk7](arg0);
    }
}

void func_800D8934(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D8974(arg0);
    } else {
        func_800D89D4(arg0);
    }
}

void func_800D8974(struct LayerObj* arg0)
{
    if (func_800D8E94(arg0)) {
        background_objects[0].unk24 = 0xD30;
        background_objects[0].unk26 = 0xD30;
        func_80036AE4(0x14, 0x40);
        arg0->base.unk7 = 0;
        arg0->base.unk6++;
    }
}

void func_800D89D4(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        D_8010FF2C[arg0->base.unk7](arg0);
    }
}

void func_800D8A24(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D8A64(arg0);
    } else {
        func_800D8A6C(arg0);
    }
}

void func_800D8A64(struct LayerObj* arg0)
{
}

void func_800D8A6C(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        D_8010FF2C[arg0->base.unk7](arg0);
    }
}

void func_800D8ABC(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D8AFC(arg0);
    } else {
        func_800D8B5C(arg0);
    }
}

void func_800D8AFC(struct LayerObj* arg0)
{
    if (func_800D8E94(arg0)) {
        background_objects[0].unk24 = 0x1A50;
        background_objects[0].unk26 = 0x1A50;
        func_80036AE4(0x14, 0x40);
        arg0->base.unk7 = 0;
        arg0->base.unk6++;
    }
}

void func_800D8B5C(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        D_8010FF2C[arg0->base.unk7](arg0);
    }
}

void func_800D8BAC(struct LayerObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8BB4);

void func_800D8C24(struct LayerObj* arg0)
{
    struct BaseObj* temp_v0;

    temp_v0 = (struct BaseObj*)find_free_main_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x41;
        temp_v0->id = 0x22;
        temp_v0->unk2 = arg0->base.bg_offset - 1;
        temp_v0->unk10 = arg0;
    }
    arg0->base.unk7++;
}

void func_800D8C84(struct LayerObj* arg0)
{
    struct BaseObj* temp_v0;

    if (*(s8*)&arg0->unk1C == 1) {
        arg0->base.unk7++;
        temp_v0 = (struct BaseObj*)find_free_item_obj();
        if (temp_v0 != NULL) {
            temp_v0->active = 0x41;
            temp_v0->id = 0xC;
            temp_v0->unk2 = arg0->base.bg_offset - 1;
            temp_v0->state = 0;
        }
    }
}

void func_800D8CF4(struct LayerObj* arg0)
{
    u8 temp = arg0->base.bg_offset;
    switch (temp) {
    case 1:
        func_800DABE4(0xD, 0x8C0, 0x160);
        func_800DABE4(0xC, 0x970, 0x190);
        break;
    case 2:
        func_800DABE4(0, 0xD20, 0x160);
        func_800DABE4(7, 0xE10, 0x170);
        break;
    case 3:
        func_800DABE4(0, 0x13B0, 0x160);
        func_800DABE4(7, 0x14A0, 0x170);
        break;
    case 4:
        func_800DABE4(0, 0x1A40, 0x160);
        func_800DABE4(7, 0x1B30, 0x170);
        break;
    }
    arg0->base.unk7++;
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8DE0);

void func_800D8E40(struct LayerObj* arg0)
{
    if (--arg0->base.unk16 == 0) {
        func_80028BAC(0x30, 2, 1);
        arg0->base.unk16 = 0x78;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8E94);

void func_800D8ED4(struct LayerObj* arg0)
{
    D_8010FF40[arg0->base.state](arg0);
}

void func_800D8F10(struct LayerObj* arg0)
{
    arg0->base.unk5 = 2;
    arg0->base.bg_offset = 3;
    arg0->base.state++;
    func_800D8F48(arg0);
}

void func_800D8F48(struct LayerObj* arg0)
{
    arg0->base.unk15 = arg0->base.bg_offset;
    func_800D91A8(arg0);
    D_8010FF48[arg0->base.unk5](arg0);
}

void func_800D8F9C(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D8FDC(arg0);
    } else {
        func_800D9008(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8FDC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9008);

void func_800D9050(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D9090(arg0);
    } else {
        func_800D90BC(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9090);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D90BC);

void func_800D90CC(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D910C(arg0);
    } else {
        func_800D9138(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D910C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9138);

void func_800D91A0(struct LayerObj* arg0)
{
}

void func_800D91A8(struct LayerObj* arg0)
{
    u32 var_v1;

    if (g_Player.base.y_pos.i.hi < 0x201) {
        var_v1 = (u32) ~(g_Player.base.x_pos.i.hi - 0x450) >> 0x1F;
    } else {
        var_v1 = 2;
        if (g_Player.base.x_pos.i.hi - 0xA00 < 0) {
            var_v1 = 1;
        }
    }
    arg0->base.bg_offset = var_v1;
    if (var_v1 != arg0->base.unk15) {
        arg0->base.unk5 = var_v1;
        arg0->base.unk6 = 0;
    }
}

void func_800D9218(struct LayerObj* arg0)
{
    D_8010FF60[arg0->base.state](arg0);
    func_800D9B48(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9268);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9330);

void func_800D93FC(struct LayerObj* arg0)
{
    func_8002B108(arg0);
}

void func_800D941C(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D945C(arg0);
    } else {
        func_800D9470(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D945C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9470);

void func_800D9480(struct LayerObj* arg0)
{
    switch (arg0->base.unk6) {
    case 0:
        func_800D94FC(arg0);
        return;
    case 1:
        func_800D95F4(arg0);
        return;
    case 2:
        func_800D964C(arg0);
        return;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D94FC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D95F4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D964C);

void func_800D9728(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D9768(arg0);
    } else {
        func_800D97F4(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9768);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D97F4);

void func_800D986C(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D98AC(arg0);
    } else {
        func_800D98C0(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D98AC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D98C0);

void func_800D98D0(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D9910(arg0);
    } else {
        func_800D9924(arg0);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9910);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9924);

void func_800D9934(struct LayerObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D993C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D99B0);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9A04);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9A58);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9B08);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9B48);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9C84);

void func_800DA05C(struct LayerObj* arg0)
{
    D_8010FF88[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA098);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA0EC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA140);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA160);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA1A0);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA1B4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA1C4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA204);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA218);

void func_800DA228(struct LayerObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA230);

void func_800DA298(struct LayerObj* arg0)
{
    D_8010FFA0[arg0->base.state](arg0);
}

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

void func_800DA748(struct LayerObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA750);

void func_800DA7C0(struct LayerObj* arg0)
{
    D_8010FFC8[arg0->base.state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA7FC);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA818);

void func_800DA878(struct LayerObj* arg0)
{
    D_8010FFD0[arg0->base.state](arg0);
}

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
