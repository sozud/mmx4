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

void func_800D79F0(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

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

void func_800D7AF8(struct QuadObj* arg0)
{
    D_8010FE2C[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
    arg0->on_screen = 1;
}

void func_800D7B50(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D7B70(struct QuadObj* arg0)
{
    arg0->unk28.i.hi += 0x10;
    arg0->unk30.i.hi += 0x10;
    if (arg0->unk28.i.hi >= background_objects[0].y_pos.i.hi + 0xC8) {
        arg0->unk5++;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D7BBC);

void func_800D7C3C(struct QuadObj* arg0)
{
    if (arg0->unk5C->base.unk7 >= 8) {
        arg0->state++;
    }
}

void func_800D7C70(struct QuadObj* arg0, u8 arg1)
{
    if (arg1) {
        arg0->unk14.val = arg0->unk5C->base.x_pos.val + FIXED(-1);
    } else {
        arg0->unk14.val = g_Player.base.x_pos.val + FIXED(-1);
    }
    arg0->unk18.val = 0;
    arg0->unk1C.val = arg0->unk14.val + FIXED(2);
    arg0->unk28.val = arg0->unk18.val + FIXED(1);
    arg0->unk20.val = arg0->unk18.val;
    arg0->unk24.val = arg0->unk14.val;
    arg0->unk2C.val = arg0->unk1C.val;
    arg0->unk30.val = arg0->unk28.val;
}

void func_800D7CEC(struct QuadObj* arg0)
{
    struct BaseObj* obj = arg0->unk5C;
    arg0->state++;
    arg0->active = -0x7D;
    arg0->bg_offset = g_Player.base.bg_offset;
    arg0->unk36 = 6;
    arg0->unk34 = 0x10;
    arg0->x_pos.i.hi = obj->x_pos.i.hi;
    arg0->y_pos.i.hi = obj->y_pos.i.hi - 0x17;
    arg0->unk14.i.hi = -2;
    arg0->unk1C.i.hi = 2;
    arg0->unk24.i.hi = 2;
    arg0->unk2C.i.hi = -2;
    arg0->unk18.i.hi = 0;
    arg0->unk20.i.hi = 0;
    arg0->unk28.i.hi = 0;
    arg0->unk30.i.hi = 0;
}

void func_800D7D60(struct QuadObj* arg0)
{
    arg0->unk28.i.hi += 4;
    arg0->unk30.i.hi += 4;
    if (arg0->unk28.i.hi >= 0x41) {
        arg0->ext.unk_ext2.unk3C = 0x2D;
        arg0->unk5++;
    }
}

void func_800D7DA4(struct QuadObj* arg0)
{
    struct ShotObj* obj;
    if (--arg0->ext.unk_ext4.unk3C == 0) {
        arg0->unk5 = (u8)arg0->unk5 + 1;
        if (engine_obj.unk43 == 0) {
            arg0->ext.unk_ext4.unk3C = 0xD2U;
            return;
        }
        arg0->ext.unk_ext4.unk3C = 0x46U;
        return;
    }
    if (!(D_80141BD8.unk0 & 3)) {
        obj = find_free_shot_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0x2E;
            obj->base.unk2 = 8;
            obj->unk7C = arg0;
        }
    }
    arg0->unk24.i.hi += D_8010FE38[arg0->unk2];
    arg0->unk2C.i.hi += D_8010FE38[arg0->unk2];
}

void func_800D7EA8(struct QuadObj* arg0)
{
    struct ShotObj* temp_v0;

    if (!(D_80141BD8.unk0 & 3)) {
        temp_v0 = find_free_shot_obj();
        if (temp_v0 != NULL) {
            temp_v0->base.active = 0x41;
            temp_v0->base.id = 0x2E;
            temp_v0->base.unk2 = 8;
            temp_v0->unk7C = arg0;
        }
    }
    if (arg0->ext.unk_ext4.unk3C == 0) {
        arg0->unk14.i.hi++;
        arg0->unk1C.i.hi--;
        arg0->unk2C.i.hi++;
        arg0->unk24.i.hi--;
        if (arg0->unk14.i.hi == arg0->unk1C.i.hi) {
            arg0->state = 2;
        }
    } else {
        arg0->ext.unk_ext4.unk3C--;
    }
}

void func_800D7F64(struct QuadObj* arg0)
{
    D_8010FE3C[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
    if (arg0->unk5C->base.state == 2) {
        arg0->state = 2;
    }
}

void func_800D7FD0(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D7FF0(struct QuadObj* arg0)
{
    D_8010FE48[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D802C);

void func_800D8150(struct QuadObj* arg0)
{
    if (--arg0->ext.unk38 == 0) {
        arg0->ext.unk38 = 8;
        arg0->unk5++;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D8180);

void func_800D8290(struct QuadObj* arg0)
{
    struct PlayerObj* obj = arg0->unk5C;
    arg0->ext.unk38--;
    if (arg0->ext.unk38 == 0) {
        arg0->unk34 = 0x12;
        arg0->ext.unk38 = 0x10;
        arg0->unk5 = (u8)arg0->unk5 + 1;
        obj->unk95 = 0;
    } else {
        arg0->unk34 = D_8010FED4[arg0->ext.unk38 & 3];
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D82E8);

void func_800D83DC(struct QuadObj* arg0)
{
    D_8010FED8[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
}

void func_800D842C(struct QuadObj* arg0)
{
    if (--arg0->ext.unk38 == 0) {
        arg0->ext.unk38 = 0x10;
        arg0->unk5++;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D845C);

void func_800D8578(struct QuadObj* arg0)
{
    D_8010FEE8[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
}

void func_800D85C8(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

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

void func_800D8FDC(struct LayerObj* arg0)
{
    background_objects[1].unk4 = 5;
    background_objects[1].unk40 = 0x28;
    arg0->base.unk6++;
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800D9008);

void func_800D9050(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D9090(arg0);
    } else {
        func_800D90BC(arg0);
    }
}

void func_800D9090(struct LayerObj* arg0)
{
    background_objects[1].unk4 = 2;
    background_objects[1].unk40 = 0x200;
    arg0->base.unk6++;
}

void func_800D90BC(struct LayerObj* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

void func_800D90CC(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D910C(arg0);
    } else {
        func_800D9138(arg0);
    }
}

void func_800D910C(struct LayerObj* arg0)
{
    background_objects[1].unk4 = 5;
    background_objects[1].unk40 = 0xB60;
    arg0->base.unk6++;
}

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

void func_800D945C(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800D9470(struct LayerObj* arg0)
{
    arg0->base.unk5 = 5;
    arg0->base.unk6 = 0;
}

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

void func_800D94FC(struct LayerObj* arg0)
{
    switch (arg0->base.unk7) {
    case 0:
        if (func_800D9B08(arg0)) {
            background_objects[0].unk24 = 0x16B0;
            background_objects[0].unk26 = 0x16B0;
            func_80036AE4(0x14, 0x40);
            arg0->base.unk7 = 1;
            return;
        }
        return;
    case 1:
        if (func_8002BAD0(1, 0x40, 0x40) == 0x1E) {
            arg0->base.unk7 = 2;
            return;
        }
        break;
    case 2:
        if (func_8002BAD0(1, 0x40, 0x40) == 0x18) {
            arg0->base.unk7 = 0;
            arg0->base.unk6 = (u8)arg0->base.unk6 + 1;
        }
        break;
    }
}

void func_800D95F4(struct LayerObj* arg0)
{
    arg0->base.unk17 = 2;
    engine_obj.unk26 = 1;
    func_8001540C(5, 0xA, NULL);
    arg0->base.unk7 = 0;
    arg0->base.unk6++;
}

void func_800D964C(struct LayerObj* arg0)
{
    s32 temp_v1;

    if (arg0->base.unk7 == 0) {
        if (arg0->unk18.val != 0) {
            arg0->unk18.val -= 0x800;
            return;
        }
        background_objects[0].unk1C = 0x24E0;
        background_objects[0].unk24 = 0x24E0;
        func_80036B18();
        func_8001540C(5, 0xB, NULL);
        arg0->base.unk7 = 1;
        arg0->base.unk17 = 0;
        return;
    }
    if (g_Player.unkBC == 0) {
        temp_v1 = background_objects[0].x_pos.val - background_objects[0].unk14.val;
        background_objects[1].x_pos.val += temp_v1;
        background_objects[2].x_pos.val += temp_v1 >> 1;
    }
}

void func_800D9728(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D9768(arg0);
    } else {
        func_800D97F4(arg0);
    }
}

void func_800D9768(struct LayerObj* arg0)
{
    if (engine_obj.checkpoint != 3) {
        background_objects[0].unk26 = 0x1DE0;
        func_80036AE4(0x14, 0x40);
        func_8001540C(5, 9, NULL);
        arg0->unk18.val = FIXED(2);
    } else {
        arg0->unk18.val = FIXED(8);
    }

    arg0->base.unk17 = 1;
    engine_obj.unk26 = 0;
    arg0->base.unk7 = 0;
    arg0->base.unk6++;
}

void func_800D97F4(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26 && g_Player.unkC0 < 0) {
        func_80036B18();
    }
    if (arg0->unk18.val != 0x80000) {
        arg0->unk18.val += 0x400;
    } else {
        arg0->base.unk5 = 5;
        arg0->base.unk6 = 0;
    }
}

void func_800D986C(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D98AC(arg0);
    } else {
        func_800D98C0(arg0);
    }
}

void func_800D98AC(struct LayerObj* arg0)
{
    arg0->base.unk7 = 0;
    arg0->base.unk6++;
}

void func_800D98C0(struct LayerObj* arg0)
{
    arg0->base.unk5 = 5;
    arg0->base.unk6 = 0;
}

void func_800D98D0(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800D9910(arg0);
    } else {
        func_800D9924(arg0);
    }
}

void func_800D9910(struct LayerObj* arg0)
{
    arg0->base.unk7 = 0;
    arg0->base.unk6++;
}

void func_800D9924(struct LayerObj* arg0)
{
    arg0->base.unk5 = 5;
    arg0->base.unk6 = 0;
}

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

void func_800DA098(struct LayerObj* arg0)
{
    arg0->base.unk5 = 1;
    arg0->base.bg_offset = 2;
    arg0->base.state++;
    background_objects[0].unk2E = 0xA0;
    background_objects[0].unk2C = 0x50;
    func_800DA0EC(arg0);
}

void func_800DA0EC(struct LayerObj* arg0)
{
    arg0->base.unk15 = arg0->base.bg_offset;
    func_800DA230(arg0);
    D_8010FF94[arg0->base.unk5](arg0);
}

void func_800DA140(struct LayerObj* arg0)
{
    func_8002B108(arg0);
}

void func_800DA160(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800DA1A0(arg0);
    } else {
        func_800DA1B4(arg0);
    }
}

void func_800DA1A0(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800DA1B4(struct LayerObj* arg0)
{
    arg0->base.unk5 = 2;
    arg0->base.unk6 = 0;
}

void func_800DA1C4(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800DA204(arg0);
    } else {
        func_800DA218(arg0);
    }
}

void func_800DA204(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800DA218(struct LayerObj* arg0)
{
    arg0->base.unk5 = 2;
    arg0->base.unk6 = 0;
}

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

void func_800DA478(struct LayerObj* arg0)
{
    func_8002B108(arg0);
}

void func_800DA498(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800DA4D8(arg0);
    } else {
        func_800DA4EC(arg0);
    }
}

void func_800DA4D8(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800DA4EC(struct LayerObj* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

void func_800DA4FC(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800DA53C(arg0);
    } else {
        func_800DA550(arg0);
    }
}

void func_800DA53C(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800DA550(struct LayerObj* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

void func_800DA560(struct LayerObj* arg0)
{
    if (arg0->base.unk6 == 0) {
        func_800DA5A0(arg0);
    } else {
        func_800DA5B4(arg0);
    }
}

void func_800DA5A0(struct LayerObj* arg0)
{
    arg0->base.unk6++;
}

void func_800DA5B4(struct LayerObj* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

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

void func_800DA7FC(struct LayerObj* arg0)
{
    arg0->base.bg_offset = 0;
    arg0->base.unk15 = 0;
    arg0->base.unk16 = 0;
    arg0->base.state++;
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA818);

void func_800DA878(struct LayerObj* arg0)
{
    D_8010FFD0[arg0->base.state](arg0);
}

void func_800DA8B4(struct LayerObj* arg0)
{
    arg0->base.state++;
    background_objects[1].unk4D = 1;
    background_objects[1].unk4E = 6;
    *(s32*)&arg0->base.bg_offset = 0x8000;
    arg0->base.unk5 = 0;
    arg0->base.unk6 = 0;
    arg0->base.unk7 = 0;
    func_800DA90C(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA90C);

void func_800DA964(struct LayerObj* arg0)
{
    func_8002B108(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DA984);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DAB40);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DAB9C);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DABE4);

INCLUDE_ASM("asm/us/main/nonmatchings/C7F34", func_800DADA0);

void func_800DAE84(void)
{
}
