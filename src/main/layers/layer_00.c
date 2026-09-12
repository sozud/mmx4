// LayerObj, layer_object_update_funcs[0]
// 800D8648..800D8ED4
#include "common.h"

void func_800D8BB4(struct LayerObj* arg0);

void func_800D8648(struct LayerObj* arg0)
{
    D_8010FF08[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/layers/layer_00", func_800D8684);

void func_800D872C(struct LayerObj* arg0)
{
    arg0->unk15 = arg0->bg_offset;
    func_800D8BB4(arg0);
    D_8010FF14[arg0->unk5](arg0);
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
    if (arg0->unk6 == 0) {
        func_800D8820(arg0);
    } else {
        func_800D8834(arg0);
    }
}

void func_800D8820(struct LayerObj* arg0)
{
    arg0->unk6++;
}

void func_800D8834(struct LayerObj* arg0)
{
    arg0->unk5 = 5;
    arg0->unk6 = 0;
}

void func_800D8844(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
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
        arg0->unk7 = 0;
        arg0->unk6++;
    }
}

void func_800D88E4(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        D_8010FF2C[arg0->unk7](arg0);
    }
}

void func_800D8934(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
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
        arg0->unk7 = 0;
        arg0->unk6++;
    }
}

void func_800D89D4(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        D_8010FF2C[arg0->unk7](arg0);
    }
}

void func_800D8A24(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
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
        D_8010FF2C[arg0->unk7](arg0);
    }
}

void func_800D8ABC(struct LayerObj* arg0)
{
    if (arg0->unk6 == 0) {
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
        arg0->unk7 = 0;
        arg0->unk6++;
    }
}

void func_800D8B5C(struct LayerObj* arg0)
{
    if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        D_8010FF2C[arg0->unk7](arg0);
    }
}

void func_800D8BAC(struct LayerObj* arg0)
{
}

void func_800D8BB4(struct LayerObj* arg0)
{
    s16 player_x = g_Player.x_pos.i.hi;
    s8 offset = 0;

    while (1) {
        if (player_x - D_8010FF00[offset] < 0) {
            break;
        }
        offset++;
        if (offset >= 4) {
            break;
        }
    }
    arg0->bg_offset = offset;
    if (offset != arg0->unk15) {
        arg0->unk5 = offset;
        arg0->unk6 = 0;
    }
}

void func_800D8C24(struct LayerObj* arg0)
{
    struct BaseObj* temp_v0;

    temp_v0 = (struct BaseObj*)find_free_main_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x41;
        temp_v0->id = 0x22;
        temp_v0->unk2 = arg0->bg_offset - 1;
        temp_v0->backref = arg0;
    }
    arg0->unk7++;
}

void func_800D8C84(struct LayerObj* arg0)
{
    struct BaseObj* temp_v0;

    if (arg0->private_state.signed_byte == 1) {
        arg0->unk7++;
        temp_v0 = (struct BaseObj*)find_free_item_obj();
        if (temp_v0 != NULL) {
            temp_v0->active = 0x41;
            temp_v0->id = 0xC;
            temp_v0->unk2 = arg0->bg_offset - 1;
            temp_v0->state = 0;
        }
    }
}

void func_800D8CF4(struct LayerObj* arg0)
{
    u8 temp = arg0->bg_offset;
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
    arg0->unk7++;
}

INCLUDE_ASM("main/nonmatchings/layers/layer_00", func_800D8DE0);

void func_800D8E40(struct LayerObj* arg0)
{
    if (--arg0->unk16 == 0) {
        func_80028BAC(0x30, 2, 1);
        arg0->unk16 = 0x78;
    }
}

u8 func_800D8E94(struct LayerObj* arg0)
{
    f32 x_pos;
    s16 threshold;

    threshold = D_8010FF00[(u8)arg0->bg_offset - 1];
    x_pos = g_Player.x_pos;
    if (x_pos.i.hi >= threshold && (16 + threshold) >= x_pos.i.hi)
        return 1;
    return 0;
}

void (*D_8010FF08[])(struct LayerObj*) = {
    func_800D8684,
    func_800D872C,
    func_800D87C0,
};

void (*D_8010FF14[])(struct LayerObj*) = {
    func_800D87E0,
    func_800D8844,
    func_800D8934,
    func_800D8A24,
    func_800D8ABC,
    func_800D8BAC,
};

void (*D_8010FF2C[])(struct LayerObj*) = {
    func_800D8C24,
    func_800D8C84,
    func_800D8CF4,
    func_800D8DE0,
};

s16 D_8010FF3C[2] = { 0x450, 0xA00 };
