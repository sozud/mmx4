// QuadObj, quad_object_update_funcs[14]
// 800D7A54..800D7CEC
#include "common.h"

void func_800D7A54(struct QuadObj* arg0)
{
    D_8010FE20[arg0->state](arg0);
}

void func_800D7A90(struct QuadObj* arg0)
{
    arg0->active = -0x6D;
    arg0->bg_offset = (u8)g_Player.bg_offset;
    arg0->unk34 = 0x11;
    arg0->unk36 = 2;
    arg0->x_pos.i.hi = 0;
    arg0->y_pos.i.hi = 0;
    func_800D7C70(arg0, (u8)arg0->unk2);
    arg0->unk5 = 0;
    arg0->state = (u8)arg0->state + 1;
}

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

void func_800D7BBC(struct QuadObj* arg0)
{
    arg0->unk14.i.hi = arg0->unk14.i.hi + 3;
    arg0->unk1C.i.hi = arg0->unk1C.i.hi - 3;
    arg0->unk24.i.hi = arg0->unk24.i.hi - 6;
    arg0->unk2C.i.hi = arg0->unk2C.i.hi + 6;
    if (arg0->unk24.i.hi - arg0->unk2C.i.hi >= 0) {
        if (arg0->unk24.i.hi - arg0->unk2C.i.hi < 0x40) {
            return;
        }
        arg0->unk5++;
    } else if (arg0->unk2C.i.hi - arg0->unk24.i.hi >= 0x40) {
        arg0->unk5++;
    }
}

void func_800D7C3C(struct QuadObj* arg0)
{
    if (arg0->unk5C->unk7 >= 8) {
        arg0->state++;
    }
}

void func_800D7C70(struct QuadObj* arg0, u8 arg1)
{
    if (arg1) {
        arg0->unk14.val = arg0->unk5C->x_pos.val + FIXED(-1);
    } else {
        arg0->unk14.val = g_Player.x_pos.val + FIXED(-1);
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
