// MiscObj, misc_object_update_funcs[46]
// 800D1284..800D1990
#include "common.h"

void func_800D1284(struct MiscObj* arg0)
{
    D_8010F1A4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D12C0);

void func_800D1464(struct MiscObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010F1B0[arg0->unk5](UNK_OBJECT(arg0));
    if (arg0->unk5 < 8) {
        func_8002B318(BASE_OBJECT(arg0), 0x48, 0x48);
    }
}

void func_800D14D8(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800D14F8(struct UnkObj* arg0)
{
    if (background_objects[g_Player.bg_offset].x_pos.i.hi == g_Player.x_pos.i.hi - 0x30) {
        arg0->ext.timer = 0x3C;
        arg0->unk5 = 1;
    }
}

void func_800D154C(struct UnkObj* arg0)
{
    s8 timer;

    timer = arg0->ext.timer - 1;
    arg0->ext.timer = timer;
    if (timer == 0) {
        func_8001540C(2, 0x2A, arg0);
        arg0->unk4B = 1;
        arg0->unk5 = 2;
    }
}

void func_800D15A8(struct UnkObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->x_pos.i.hi < background_objects[g_Player.bg_offset].x_pos.i.hi + 0x134) {
        arg0->unk5 = 3;
    }
}

void func_800D1614(struct UnkObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->x_vel.val > 0) {
        arg0->unk4B = -1;
        func_80015D60(arg0, 0);
        arg0->ext.timer = 0x1E;
        arg0->unk5 = 4;
    }
}

void func_800D166C(struct UnkObj* arg0)
{
    u16 sound_id;
    u8 sound_type;

    if (--arg0->ext.timer != 0) {
        return;
    }
    sound_id = 0x1A;
    if (engine_obj.cur_character == 0) {
        sound_id = 0x1F;
        sound_type = 1;
    } else {
        sound_type = 3;
    }
    func_8002217C(sound_id, sound_type, 0);
    arg0->unk5 = 5;
}

void func_800D16E0(struct UnkObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->ext.timer = 0x1E;
        arg0->unk5 = 6;
    }
}

void func_800D1708(struct UnkObj* arg0)
{
    s8 timer;

    timer = arg0->ext.timer - 1;
    arg0->ext.timer = timer;
    if (timer == 0) {
        func_8001540C(2, 0x2A, arg0);
        arg0->x_vel.val = 0;
        arg0->unk28 = FIXED(1);
        func_80015D60(arg0, 1);
        arg0->ext.timer = 0x20;
        arg0->unk5 = 7;
    }
}

void func_800D177C(struct UnkObj* arg0)
{
    s8 timer;
    s32 delta;

    timer = arg0->ext.timer - 1;
    arg0->ext.timer = timer;
    if (timer == 0) {
        arg0->ext.timer = 0x3C;
        arg0->on_screen = 0;
        arg0->unk5 = 8;
        return;
    }
    delta = arg0->x_vel.val + arg0->unk28;
    arg0->x_vel.val = delta;
    if (arg0->ext.timer & 1) {
        arg0->x_pos.val += delta;
    } else {
        arg0->x_pos.val -= delta;
    }
}

void func_800D17F0(struct UnkObj* arg0)
{
    s8 temp_v0;
    u16 sound_id;
    u8 sound_type;

    temp_v0 = arg0->ext.timer - 1;
    arg0->ext.timer = temp_v0;
    if (temp_v0 == 0) {
        sound_id = 0x2B;
        if (engine_obj.cur_character == 0) {
            sound_id = 0x30;
            sound_type = 2;
        } else {
            sound_type = 4;
        }
        func_8002217C(sound_id, sound_type, 0);
        arg0->unk5 = 9;
    }
}

void func_800D1864(struct UnkObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->ext.timer = 0x3C;
        arg0->unk5 = 10;
    }
}

void func_800D188C(struct UnkObj* arg0)
{
    s8 timer = arg0->ext.timer - 1;
    arg0->ext.timer = timer;
    if (timer == 0) {
        engine_obj.unkF = 1;
        arg0->state = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D18C0);

union AnimationStep D_8010F194[1] = {
    { .packed = 0x00000101 },
};

union AnimationStep D_8010F198[1] = {
    { .packed = 0x01000101 },
};

union AnimationStep* D_8010F19C[2] = {
    D_8010F194,
    D_8010F198,
};

void (*D_8010F1A4[3])(struct MiscObj*) = {
    func_800D12C0,
    func_800D1464,
    func_800D14D8,
};

void (*D_8010F1B0[11])(struct UnkObj*) = {
    func_800D14F8,
    func_800D154C,
    func_800D15A8,
    func_800D1614,
    func_800D166C,
    func_800D16E0,
    func_800D1708,
    func_800D177C,
    func_800D17F0,
    func_800D1864,
    func_800D188C,
};
