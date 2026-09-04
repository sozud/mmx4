// LayerObj, layer_object_update_funcs[2]
// 800D9218..800D9C84
#include "common.h"

void func_800D9218(struct LayerObj* arg0)
{
    D_8010FF60[arg0->base.state](arg0);
    func_800D9B48(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_02", func_800D9268);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_02", func_800D9330);

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
            arg0->base.unk6++;
        }
        break;
    }
}

void func_800D95F4(struct LayerObj* arg0)
{
    arg0->base.unk17 = 2;
    engine_obj.character_state.bytes[0] = 1;
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
    engine_obj.character_state.bytes[0] = 0;
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

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_02", func_800D993C);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_02", func_800D99B0);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_02", func_800D9A04);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_02", func_800D9A58);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_02", func_800D9B08);

INCLUDE_ASM("asm/us/main/nonmatchings/layers/layer_02", func_800D9B48);

void (*D_8010FF60[])(struct LayerObj*) = {
    func_800D9268,
    func_800D9330,
    func_800D93FC,
};
