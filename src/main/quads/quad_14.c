// QuadObj, quad_object_update_funcs[14]
// 800D7A54..800D7CEC
#include "common.h"

void func_800D7A54(struct QuadObj* arg0)
{
    D_8010FE20[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_14", func_800D7A90);

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

INCLUDE_ASM("asm/us/main/nonmatchings/quads/quad_14", func_800D7BBC);

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

void (*D_8010FE20[])(struct QuadObj*) = {
    func_800D7A90,
    func_800D7AF8,
    func_800D7B50,
};

void (*D_8010FE2C[])(struct QuadObj*) = {
    func_800D7B70,
    func_800D7BBC,
    func_800D7C3C,
};
