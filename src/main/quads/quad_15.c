// QuadObj, quad_object_update_funcs[15]
// 800D7CEC..800D802C
#include "common.h"

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
        if (engine_obj.cur_character == CHARACTER_X) {
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

s8 D_8010FE38[4] = { -6, -3, 6, 3 };

void (*D_8010FE3C[])(struct QuadObj*) = {
    func_800D7D60,
    func_800D7DA4,
    func_800D7EA8,
};

void (*D_8010FE48[])(struct QuadObj*) = {
    func_800D7CEC,
    func_800D7F64,
    func_800D7FD0,
};
