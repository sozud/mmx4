// QuadObj, quad_object_update_funcs[5]
// 800D553C..800D5934
#include "common.h"

void func_800D553C(struct QuadObj* arg0)
{
    D_8010FAD4[arg0->state](arg0);
}

void func_800D5578(struct QuadObj* arg0)
{
    arg0->unk36 = 4;
    arg0->unk34 = 0x7EC0;
    arg0->state = 1;
    arg0->ext.quad_5.scale = 0x100;
    arg0->ext.quad_5.index = 0;
    arg0->bg_offset = 0;
    arg0->ext.quad_5.update_timer = 0;
    arg0->active |= 0x80;
    arg0->ext.quad_5.data = D_8010FAB4[arg0->ext.quad_5.index];
    func_800D56C8(arg0);
}

void func_800D55E4(struct QuadObj* arg0)
{
    u16 temp_v0;
    u16 temp_v1;

    temp_v1 = arg0->ext.quad_5.update_timer;
    if (temp_v1 < 2U) {
        arg0->ext.quad_5.update_timer = temp_v1 + 1;
    } else {
        temp_v1 = arg0->ext.quad_5.index;
        temp_v0 = arg0->ext.quad_5.scale;
        arg0->ext.quad_5.update_timer = 0;
        temp_v1 = (temp_v1 + 1) & 7;
        temp_v0 += 0x40;
        arg0->ext.quad_5.scale = temp_v0;
        arg0->ext.quad_5.index = temp_v1;
        if ((u32)temp_v0 >= 0x501U) {
            arg0->ext.quad_5.scale = 0x100;
        }
    }

    arg0->ext.quad_5.data = D_8010FAB4[arg0->ext.quad_5.index];
    func_800D56C8(arg0);
    if ((func_800D57A8(arg0) << 16) != 0) {
        arg0->on_screen = 1;
        return;
    }

    arg0->on_screen = 0;
    arg0->state = 2;
    arg0->unk5 = 0;
}

void func_800D56A8(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D56C8(struct QuadObj* arg0)
{
    s32* p = arg0->ext.quad_5.data;

    arg0->unk14.val = *p++ * arg0->ext.quad_5.scale;
    arg0->unk18.val = *p++ * arg0->ext.quad_5.scale;
    arg0->unk1C.val = *p++ * arg0->ext.quad_5.scale;
    arg0->unk20.val = *p++ * arg0->ext.quad_5.scale;
    arg0->unk24.val = *p++ * arg0->ext.quad_5.scale;
    arg0->unk28.val = *p++ * arg0->ext.quad_5.scale;
    arg0->unk2C.val = p[0] * arg0->ext.quad_5.scale;
    arg0->unk30.val = p[1] * arg0->ext.quad_5.scale;
}

s32 func_800D57A8(struct QuadObj* arg0)
{
    u16 x, y, x2, y2;
    u16 width, height;
    s32 x_p, y_p;
    s32 result;

    result = 0;
    x = arg0->x_pos.u.hi - background_objects[arg0->bg_offset].x_pos.u.hi;
    y = arg0->y_pos.u.hi - background_objects[arg0->bg_offset].y_pos.u.hi;
    width = ABS(arg0->unk1C.i.hi, arg0->unk14.i.hi);
    height = ABS(arg0->unk30.i.hi, arg0->unk18.i.hi);
    if (ON_SCREEN_X(x, width)) {
        if (ON_SCREEN_Y(y, height)) {
            result = 1;
        }
    }
    x_p = arg0->x_pos.u.hi + arg0->unk14.u.hi;
    y_p = arg0->y_pos.u.hi + arg0->unk18.u.hi;
    x2 = x_p + (u16)(width >> 1) - background_objects[arg0->bg_offset].x_pos.u.hi;
    y2 = y_p + (u16)(height >> 1) - background_objects[arg0->bg_offset].y_pos.u.hi;
    if (ON_SCREEN_X(x2, width)) {
        if (ON_SCREEN_Y(y2, height)) {
            result = 1;
        }
    }
    return result;
}
