// MainObj, main_object_update_funcs[71]
// 80089AA4..8008ADFC
#include "common.h"
#include "func_tables.h"

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089AA4);

void func_80089B58(struct VisualObj* arg0, u8 arg1)
{
    struct VisualObj* obj;
    u8 active;
    u8 unk16;
    u8 unk15;

    obj = find_free_visual_obj();
    if (obj == NULL) {
        return;
    }
    active = arg0->active;
    obj->id = 0xC;
    obj->unk2 = arg1;
    obj->active = active;
    obj->x_pos.val = arg0->x_pos.val;
    obj->y_pos.val = arg0->y_pos.val;
    obj->animation_table = arg0->animation_table;
    obj->unk40 = arg0->unk40;
    obj->unk3C = arg0->unk3C;
    obj->unk42 = arg0->unk42 & 0x7FFF;
    unk16 = arg0->unk16;
    obj->unk16 = unk16;
    unk15 = arg0->unk15;
    obj->unk50 = (struct PlayerObj*)arg0;
    obj->unk15 = unk15;
}

s32 func_80089C0C(struct MainObj* arg0)
{
    u8 flags;

    if (arg0->unk2 == 0) {
        flags = arg0->ext.main_71.unk8A;
        if (flags != 0) {
            if (flags & 1) {
                arg0->unk15 = 0x40;
            } else {
                arg0->unk15 = 0;
            }
            return 1;
        }
    } else {
        if ((arg0->x_pos.i.hi - g_Player.x_pos.i.hi) < 0) {
            arg0->unk15 = 0x40;
        } else {
            arg0->unk15 = 0;
        }
    }

    return 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089C7C);

void func_80089EBC(struct BaseObj* arg0, s8 arg1)
{
    arg0->unk5 = arg1;
    arg0->unk6 = 0;
}

void func_80089EC8(struct MainObj* arg0)
{
    if (arg0->unk5 < 2) {
        return;
    }
    if (arg0->unk5 == 6) {
        return;
    }
    if (arg0->unk5 == 7) {
        return;
    }
    if (arg0->unk5 == 0xB) {
        return;
    }
    if (arg0->ext.main_71.unk88 == 0) {
        return;
    }
    if (arg0->ext.main_71.unk8D & 8) {
        return;
    }
    if (arg0->unk67 != 0) {
        return;
    }
    if (arg0->ext.main_71.unk86 == 0) {
        func_80089EBC(BASE_OBJECT(arg0), 6);
    }
}

void func_80089F58(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->unk54 = D_80104CDC;
    arg0->unk50 = D_80104CE0;
    arg0->unk6 = 0;
    arg0->ext.main_71.unk88 = 0;
    arg0->ext.main_71.unk86 = 0;
    arg0->ext.main_71.unk87 = 0;
    arg0->unk60 = 5;
}

void func_80089F94(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->unk20;
}

void func_80089FAC(struct MainObj* arg0)
{
    if (arg0->unk15 != 0) {
        arg0->unk20 = FIXED(1.375);
    } else {
        arg0->unk20 = FIXED(-1.375);
    }
}

void func_80089FD4(struct MainObj* arg0)
{
    s32 velocity;

    if (func_80089C0C(arg0) & 0xFF) {
        velocity = arg0->ext.main_71.unk84 << 8;
        if (arg0->unk15 == 0) {
            velocity = -velocity;
        }
        arg0->unk20 = velocity;
    }
}

void func_8008A024(struct MainObj* arg0)
{
    s32 var_v1;
    u8 temp_a1;

    temp_a1 = arg0->ext.main_71.unk8A;
    if (temp_a1 != 0) {
        var_v1 = arg0->ext.main_71.unk84 << 8;
        if (!(temp_a1 & 1)) {
            var_v1 = -var_v1;
        }
        arg0->unk20 = var_v1;
    }
}

void func_8008A05C(struct MainObj* arg0, s32 arg1, s32 arg2)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A064);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A180);

void func_8008A2E0(struct MainObj* arg0)
{
    s8 event;

    if (arg0->unk6 == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 9);
        func_8008A05C(arg0, 2, 0);
        func_8001540C(2, 0x41, arg0);
    }

    if (arg0->animation_step.fields.relative_step == 0) {
        func_80089F58(arg0);
        arg0->ext.main_71.unk87 = 0;
        return;
    }

    event = arg0->animation_step.fields.event;
    if (event == 1) {
        arg0->unk50 = &D_80104CEC;
        arg0->unk60 = 6;
    } else if (event == 2) {
        arg0->unk50 = D_80104CE0;
        arg0->unk60 = 5;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A3B0);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A4D8);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A60C);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A778);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A8E4);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A9F4);

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008AAF4);

void func_8008AC20(struct MainObj* arg0)
{
    func_80089F58(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008AC40);

void func_8008AD48(struct MainObj* arg0)
{
    arg0->unk42 &= 0x7FFF;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8008AD74(void)
{
}

void func_8008AD7C(void)
{
}

void func_8008AD84(struct MainObj* arg0)
{
    D_80104D28[arg0->unk5](arg0);
}

void func_8008ADC0(struct MainObj* arg0)
{
    D_80104D34[arg0->state](arg0);
}

struct Unk_unk68 D_80104A54[13] = {
    { 100, 0, 1, 0 },
    { 7, 0, 1, 11 },
    { 1, 1, 1, 12 },
    { 49, 0, 1, 12 },
    { 8, 0, -4, 11 },
    { 6, 0, 1, 1 },
    { 6, 1, 1, 2 },
    { 6, 0, 1, 3 },
    { 10, 0, 1, 4 },
    { 6, 0, 1, 5 },
    { 6, 0, 1, 6 },
    { 6, 0, 1, 7 },
    { 10, 0, -8, 8 },
};

union AnimationStep D_80104A88[] = {
    { 0x09000006 },
};

union AnimationStep D_80104A8C[] = {
    { 0x0A000006 },
};

union AnimationStep D_80104A90[] = {
    { 0x0B010002 },
    { 0x0C010008 },
    { 0x0B010007 },
    { 0x00000008 },
};

union AnimationStep D_80104AA0[] = {
    { 0x0D010004 },
    { 0x0E000008 },
};

union AnimationStep D_80104AA8[] = {
    { 0x0D000004 },
};

union AnimationStep D_80104AAC[] = {
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x10010003 },
    { 0x0F000006 },
};

u8 D_80104ACC[16] = { 2, 0, 1, 17, 2, 0, 1, 18, 2, 17, 1, 17, 2, 17, 255, 18 };

union AnimationStep D_80104ADC[] = {
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1B010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010001 },
    { 0x20010101 },
    { 0x21010001 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x20010001 },
    { 0x21000010 },
    { 0x12000205 },
    { 0x0F000005 },
};

union AnimationStep D_80104B5C[] = {
    { 0x09010001 },
    { 0x22010001 },
    { 0x23010001 },
    { 0x24010001 },
    { 0x25010001 },
    { 0x26010001 },
    { 0x27010001 },
    { 0x28010001 },
    { 0x29010001 },
    { 0x28010001 },
    { 0x29010001 },
    { 0x28010001 },
    { 0x29010006 },
    { 0x2A000006 },
    { 0x2B000006 },
};

union AnimationStep D_80104B98[] = {
    { 0x16010005 },
    { 0x17000004 },
};

union AnimationStep D_80104BA0[] = {
    { 0x18010001 },
    { 0x19010001 },
    { 0x1A000001 },
};

union AnimationStep D_80104BAC[] = {
    { 0x10010001 },
    { 0x12010001 },
    { 0x11000001 },
};

u8 D_80104BB8[12] = { 1, 0, 1, 17, 1, 0, 1, 20, 1, 0, 255, 21 };

union AnimationStep D_80104BC4[] = {
    { 0x11010005 },
    { 0x12010002 },
    { 0x0F000002 },
};

union AnimationStep D_80104BD0[] = {
    { 0x2C010005 },
    { 0x2D010005 },
    { 0x2E010005 },
    { 0x2F010005 },
    { 0x30010005 },
    { 0x31010005 },
    { 0x32010005 },
    { 0x33010005 },
    { 0x34000005 },
};

struct Unk_unk68 D_80104BF4[12] = {
    { 2, 0, 1, 53 },
    { 2, 0, 1, 54 },
    { 2, 0, 1, 55 },
    { 2, 0, 1, 56 },
    { 2, 0, 1, 57 },
    { 2, 0, 1, 58 },
    { 1, 0, 1, 53 },
    { 1, 0, 1, 54 },
    { 1, 0, 1, 55 },
    { 1, 0, 1, 56 },
    { 1, 0, 1, 57 },
    { 1, 0, -11, 58 },
};

union AnimationStep D_80104C24[] = {
    { 0x3B000002 },
};

union AnimationStep D_80104C28[] = {
    { 0x3C000002 },
};

union AnimationStep D_80104C2C[] = {
    { 0x3D000002 },
};

union AnimationStep D_80104C30[] = {
    { 0x3E000002 },
};

union AnimationStep D_80104C34[] = {
    { 0x3F000002 },
};

union AnimationStep D_80104C38[] = {
    { 0x40000002 },
};

union AnimationStep D_80104C3C[] = {
    { 0x41000002 },
};

struct Unk_unk68 D_80104C40[4] = {
    { 1, 0, 1, 66 },
    { 2, 0, 1, 67 },
    { 1, 0, 1, 66 },
    { 2, 0, -3, 67 },
};

struct Unk_unk68 D_80104C50[4] = {
    { 1, 0, 1, 68 },
    { 2, 0, 1, 69 },
    { 1, 0, 1, 68 },
    { 2, 0, -3, 69 },
};

void* D_80104C60[31] = {
    D_80104A54,
    &D_80104A54[5],
    D_80104A88,
    D_80104A8C,
    D_80104A90,
    D_80104AA0,
    D_80104AA8,
    D_80104AAC,
    D_80104ACC,
    D_80104ADC,
    D_80104B5C,
    D_80104B98,
    D_80104BA0,
    D_80104BAC,
    D_80104BB8,
    D_80104BC4,
    D_80104BD0,
    D_80104BF4,
    D_80104BF4,
    D_80104BF4,
    D_80104BD0,
    D_80104BF4,
    D_80104C40,
    D_80104C50,
    D_80104C24,
    D_80104C28,
    D_80104C2C,
    D_80104C30,
    D_80104C34,
    D_80104C38,
    D_80104C3C,
};

u8 D_80104CDC[4] = { 0xED, 0xDD, 40, 69 };

u8 D_80104CE0[4] = { 0xF4, 0xE7, 24, 56 };

struct Unk_unk68 D_80104CE4 = { 0, -1, 15, 33 };

struct Unk_unk68 D_80104CE8 = { -39, -16, 49, 48 };

struct Unk_unk68 D_80104CEC = { -55, -47, 65, 77 };

struct Unk_unk68 D_80104CF0[2] = {
    { 24, 25, 26, 27 },
    { 28, 29, 30, 0 },
};

void (*D_80104CF8[12])() = {
    func_8009216C,
    func_8008AC20,
    func_8008A064,
    func_8008A180,
    func_8008AAF4,
    func_8008A4D8,
    func_8008A778,
    func_8008A8E4,
    func_8008A3B0,
    func_8008A2E0,
    func_8008A60C,
    func_8008A9F4,
};

void (*D_80104D28[3])() = {
    func_8008AD48,
    func_8008AD74,
    func_8008AD7C,
};

void (*D_80104D34[3])() = {
    func_80089AA4,
    func_8008AC40,
    func_8008AD84,
};
