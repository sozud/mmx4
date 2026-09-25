// MainObj, main_object_update_funcs[7]
// 800473C8..80047C88
#include "common.h"
#include "func_tables.h"

void func_800473C8(struct MainObj* arg0)
{
    D_800FA6F0[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_07", func_80047404);

void func_80047660(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FA6FC[arg0->unk5](arg0);
    if (arg0->ext.main_7.unk90 != 0) {
        func_8002D9BC(arg0);
        arg0->ext.main_7.saved_unk5 = arg0->unk5;
        if (func_8002DD04(arg0) < 0) {
            func_800AF808(BASE_OBJECT(arg0));
            func_800C813C(5, D_800FA6E0, arg0);
            if (!(arg0->unk2 & 1)) {
                func_800BF638(BASE_OBJECT(arg0), 0xE, arg0->x_pos.u.hi - 0xA, arg0->y_pos.i.hi);
            } else {
                func_800BF638(BASE_OBJECT(arg0), 0xE, arg0->x_pos.u.hi + 0xA, arg0->y_pos.i.hi);
            }
            arg0->state = 2;
            return;
        }
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) == 0) {
        if (arg0->unk5 != 2 || arg0->unk6 != 0) {
            func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
        }
    } else {
        arg0->state = 2;
    }
}

void func_80047794(struct MainObj* arg0)
{
    arg0->unk7A = 0;
    arg0->ext.main_7.unk80 = 0;
    arg0->ext.main_7.unk84 = 0;
    arg0->ext.main_7.saved_x_velocity = 0;
    arg0->ext.main_7.saved_y_velocity = 0;
    arg0->ext.main_7.unk90 = 0;
    arg0->ext.main_7.saved_unk5 = 0;
    arg0->unk61 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_800477D0(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_7.saved_unk5;
}

void func_800477DC(struct MainObj* arg0)
{
    D_800FA710[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_07", func_80047818);

void func_80047900(struct MainObj* arg0)
{
    arg0->unk61 = 0;
    arg0->ext.main_7.unk90 = 1;
    func_800C7DA4(8, D_800FA6E8, arg0,
        arg0->unk15 == 0 ? FIXED(-3) : FIXED(3));
    func_8001540C(2, 0x15, arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 2;
}

void func_80047974(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, 0x16, arg0);
    }
    if (arg0->animation_step.fields.event == 1) {
        func_80015D60(arg0, 1);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800479E4(struct MainObj* arg0)
{
    D_800FA71C[arg0->unk6](arg0);
}

void func_80047A20(struct MainObj* arg0)
{
    arg0->unk7C = 0x28;
    arg0->unk6 = 1;
}

void func_80047A34(struct MainObj* arg0)
{
    if (arg0->unk7C == 0) {
        func_8002B93C(
            MOVING_OBJECT(arg0),
            func_8002B7DC(
                OBJECT_HEADER(arg0),
                OBJECT_HEADER(&g_Player))
                & 0xFF);

        if ((arg0->unk15 == 0 && arg0->unk20 < 0) || (arg0->unk15 != 0 && arg0->unk20 > 0)) {
            arg0->ext.main_7.saved_x_velocity = arg0->unk20;
            arg0->ext.main_7.saved_y_velocity = arg0->unk24;
            func_80015D60(arg0, 2);
            arg0->unk5 = 4;
            arg0->unk6 = 2;
        } else {
            arg0->unk7C = 0x3C;
        }

        arg0->unk20 = 0;
        arg0->unk24 = 0;
    } else {
        arg0->unk7C--;
    }
}

void func_80047B04(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 2) {
        struct ShotObj* shot;

        func_8001540C(2, 0x17, arg0);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 2;
            shot->unk40 = arg0->unk40;
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)arg0->animation_table;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->unk2 = (u8)arg0->unk2 & 1;
            shot->unk15 = arg0->unk15;
            shot->bg_offset = arg0->bg_offset;
            shot->x_pos.val = arg0->x_pos.val;
            shot->y_pos.val = arg0->y_pos.val;
            func_8002B93C(MOVING_OBJECT(arg0),
                func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)) & 0xFF);
            if ((arg0->unk15 == 0 && arg0->unk20 < 0) || (arg0->unk15 != 0 && arg0->unk20 > 0)) {
                shot->x_vel.val = arg0->unk20;
                shot->y_vel.val = arg0->unk24;
            } else {
                shot->x_vel.val = arg0->ext.main_7.saved_x_velocity;
                shot->y_vel.val = arg0->ext.main_7.saved_y_velocity;
            }
            arg0->unk20 = 0;
            arg0->unk24 = 0;
        }
    }
    if (arg0->animation_step.fields.event == 1) {
        func_80015D60(arg0, 1);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

struct Unk_unk68 D_800FA568 = { -13, -12, 25, 24 };

union AnimationStep D_800FA56C[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03010006 },
    { 0x04010006 },
    { 0x05010004 },
    { 0x06010005 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010201 },
    { 0x0E010005 },
    { 0x0F010003 },
    { 0x10010003 },
    { 0x11010003 },
    { 0x0E010006 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010001 },
    { 0x15010006 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010006 },
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1B010006 },
    { 0x1C010005 },
    { 0x1D010008 },
    { 0x1C010005 },
    { 0x1B010004 },
    { 0x1B000101 },
};

union AnimationStep D_800FA5F8[] = {
    { 0x1B000101 },
};

union AnimationStep D_800FA5FC[] = {
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x22010001 },
    { 0x1B010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x22010001 },
    { 0x1B010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010001 },
    { 0x26010001 },
    { 0x27010001 },
    { 0x1C010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010001 },
    { 0x26010001 },
    { 0x27010001 },
    { 0x28010201 },
    { 0x29010001 },
    { 0x2A010001 },
    { 0x2B010002 },
    { 0x2C010003 },
    { 0x2D010004 },
    { 0x2E010004 },
    { 0x2E000101 },
};

union AnimationStep D_800FA678[] = {
    { 0x34000101 },
};

union AnimationStep D_800FA67C[] = {
    { 0x35000101 },
};

union AnimationStep D_800FA680[] = {
    { 0x36000101 },
};

union AnimationStep D_800FA684[] = {
    { 0x37010002 },
    { 0x38010003 },
    { 0x39010003 },
    { 0x3A010003 },
    { 0x3B010002 },
    { 0x3C010001 },
    { 0x3D010001 },
    { 0x3E000101 },
};

union AnimationStep D_800FA6A4[] = {
    { 0x3F000101 },
};

union AnimationStep D_800FA6A8[] = {
    { 0x2F010001 },
    { 0x30010001 },
    { 0x31010001 },
    { 0x32010001 },
    { 0x33FC0101 },
};

union AnimationStep* D_800FA6BC[] = {
    D_800FA56C,
    D_800FA5F8,
    D_800FA5FC,
    D_800FA678,
    D_800FA67C,
    D_800FA680,
    D_800FA684,
    D_800FA6A4,
    D_800FA6A8,
};

u8 D_800FA6E0[] = {
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x00,
    0x00,
    0x00,
};

u8 D_800FA6E8[] = {
    0x01,
    0x02,
    0x03,
    0x04,
    0x01,
    0x02,
    0x03,
    0x04,
};

void (*D_800FA6F0[])(struct MainObj*) = {
    func_80047404,
    func_80047660,
    func_80047794,
};

void (*D_800FA6FC[5])() = {
    func_8009216C,
    func_800477D0,
    func_800477DC,
    func_800479E4,
    func_80047B04,
};

void (*D_800FA710[3])() = {
    func_80047818,
    func_80047900,
    func_80047974,
};

void (*D_800FA71C[2])(struct MainObj*) = {
    func_80047A20,
    func_80047A34,
};
