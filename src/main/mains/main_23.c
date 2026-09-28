// MainObj, main_object_update_funcs[23]
// 80055E04..80056788
#include "common.h"
#include "func_tables.h"

void func_80055E04(struct MainObj* arg0)
{
    s8 step;
    u8 background_relative;
    u8 background_offset;

    step = arg0->unk6;
    if (step == 0) {
        arg0->unk6 = step + 1;
        func_80055C54(arg0);
        background_relative = arg0->ext.main_23.unk80;
        background_offset = background_relative & 0x7F;
        if (background_relative & 0x80) {
            arg0->unk15 ^= 0x40;
        }
        func_80015D60(arg0, background_offset + 0x12);
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk5 = 1;
        arg0->unk6 = 0;
    }
}

void func_80055E9C(struct MainObj* arg0)
{
    s8 step;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    step = arg0->unk6;
    if (step == 0) {
        arg0->unk6 = step + 1;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk24 = 0;
        arg0->unk67 = -1;
    }
    if (arg0->unk70 & 8) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk67 = 0;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80055F1C);

void func_80055FD0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_80056018(struct MainObj* arg0)
{
    D_800FCE88[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_80056054);

void func_80056230(struct MainObj* arg0)
{
    s32 velocity;

    arg0->unk6++;
    func_80055C54(arg0);
    velocity = FIXED(-4.5);
    if (arg0->unk15 != 0) {
        velocity = FIXED(4.5);
    }
    arg0->unk20 = velocity;
    func_80015D60(arg0, (arg0->ext.main_23.unk80 & 0x7F) + 4);
    func_8001540C(2, 0x3A, arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_800562AC);

void func_80056470(void)
{
}

void func_80056478(struct MainObj* arg0)
{
    D_800FCEA0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_23", func_800564B4);

void func_800565EC(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi >= 0xC1) {
        arg0->unk5 = 1;
    }
}

void func_80056618(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (arg0->unk67 == 0 && !(arg0->unk70 & 8)) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
    if (func_8002DD04(arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(7, D_800FCE80, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0x16);
    } else {
        func_8002D9BC(arg0);
        D_800FCEAC[arg0->unk5](arg0);
        if (func_8002B1E8(BASE_OBJECT(arg0), 0x60, 0x40) == 0) {
            func_8002B318(BASE_OBJECT(arg0), 0x30, 0x30);
            return;
        }
    }
    arg0->state = (u8)arg0->state + 1;
}

void func_80056718(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80056738(struct MainObj* arg0)
{
    D_800FCEC8[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

struct Unk_unk68 D_800FCB48[] = {
    { 0, 12, 16, 2 },
};

struct Unk_unk68 D_800FCB4C[2] = {
    { -11, -16, 21, 29 },
    { 3, 3, 3, 0 },
};

union AnimationStep D_800FCB54[] = {
    { 0x06000001 },
};

union AnimationStep D_800FCB58[] = {
    { 0x07010003 },
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A010009 },
    { 0x09010003 },
    { 0x08010003 },
    { 0x01000003 },
};

union AnimationStep D_800FCB74[] = {
    { 0x07010003 },
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F010009 },
    { 0x0E010003 },
    { 0x0D010003 },
    { 0x03000003 },
};

union AnimationStep D_800FCB90[] = {
    { 0x07010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14010009 },
    { 0x13010003 },
    { 0x12010003 },
    { 0x05000003 },
};

union AnimationStep D_800FCBAC[] = {
    { 0x00010003 },
    { 0x01FF0003 },
};

union AnimationStep D_800FCBB4[] = {
    { 0x02010003 },
    { 0x03FF0003 },
};

union AnimationStep D_800FCBBC[] = {
    { 0x04010003 },
    { 0x05FF0003 },
};

union AnimationStep D_800FCBC4[] = {
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A01000F },
    { 0x09010003 },
    { 0x08010003 },
    { 0x0B010003 },
    { 0x0C000003 },
};

union AnimationStep D_800FCBE0[] = {
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F01000F },
    { 0x0E010003 },
    { 0x0D010003 },
    { 0x10010003 },
    { 0x11000003 },
};

union AnimationStep D_800FCBFC[] = {
    { 0x12010003 },
    { 0x13010003 },
    { 0x1401000F },
    { 0x13010003 },
    { 0x12010003 },
    { 0x15010003 },
    { 0x16000003 },
};

union AnimationStep D_800FCC18[] = {
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x08000001 },
};

union AnimationStep D_800FCC2C[] = {
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F01000C },
    { 0x0E010003 },
    { 0x08000003 },
};

union AnimationStep D_800FCC40[] = {
    { 0x12010003 },
    { 0x13010003 },
    { 0x1401000C },
    { 0x13010003 },
    { 0x0D000003 },
};

union AnimationStep D_800FCC54[] = {
    { 0x24010003 },
    { 0x25010009 },
    { 0x24010003 },
    { 0x2B010003 },
    { 0x2C010003 },
    { 0x2D010015 },
    { 0x2C010003 },
    { 0x2B010003 },
    { 0x24010003 },
    { 0x25000003 },
};

union AnimationStep D_800FCC7C[] = {
    { 0x24010003 },
    { 0x25010009 },
    { 0x24010003 },
    { 0x26010003 },
    { 0x27010003 },
    { 0x28010015 },
    { 0x27010003 },
    { 0x26010003 },
    { 0x24010003 },
    { 0x25000003 },
};

union AnimationStep D_800FCCA4[] = {
    { 0x1E010003 },
    { 0x1F01000F },
    { 0x1E010003 },
    { 0x01010002 },
    { 0x01000101 },
};

union AnimationStep D_800FCCB8[] = {
    { 0x20010003 },
    { 0x2101000F },
    { 0x22010003 },
    { 0x05010002 },
    { 0x05000101 },
};

union AnimationStep D_800FCCCC[] = {
    { 0x22010003 },
    { 0x2301000F },
    { 0x22010003 },
    { 0x05010002 },
    { 0x05000101 },
};

union AnimationStep D_800FCCE0[] = {
    { 0x08010003 },
    { 0x17010003 },
    { 0x18010203 },
    { 0x19010003 },
    { 0x18010003 },
    { 0x1901000F },
    { 0x18010003 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C01000F },
    { 0x1B010003 },
    { 0x1A010003 },
    { 0x1D000103 },
};

union AnimationStep D_800FCD14[] = {
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F010009 },
    { 0x0E010003 },
    { 0x17010003 },
    { 0x18010203 },
    { 0x19010003 },
    { 0x18010003 },
    { 0x1901000F },
    { 0x18010003 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C01000F },
    { 0x1B010003 },
    { 0x1A010003 },
    { 0x1D000103 },
};

union AnimationStep D_800FCD54[] = {
    { 0x12010003 },
    { 0x13010003 },
    { 0x14010009 },
    { 0x13010003 },
    { 0x17010003 },
    { 0x18010203 },
    { 0x19010003 },
    { 0x18010003 },
    { 0x1901000F },
    { 0x18010003 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C01000F },
    { 0x1B010003 },
    { 0x1A010003 },
    { 0x1D000103 },
};

union AnimationStep D_800FCD94[] = {
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29FC0012 },
};

union AnimationStep D_800FCDA8[] = {
    { 0x2A000001 },
};

union AnimationStep D_800FCDAC[] = {
    { 0x2E010002 },
    { 0x2F010002 },
    { 0x30010002 },
    { 0x31010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010002 },
    { 0x36010002 },
    { 0x37010002 },
    { 0x38010002 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3CFF0002 },
};

union AnimationStep D_800FCDE8[] = {
    { 0x3D000001 },
};

union AnimationStep D_800FCDEC[] = {
    { 0x3E000001 },
};

union AnimationStep D_800FCDF0[] = {
    { 0x3F000001 },
};

union AnimationStep D_800FCDF4[] = {
    { 0x40000001 },
};

union AnimationStep D_800FCDF8[] = {
    { 0x41000001 },
};

union AnimationStep D_800FCDFC[] = {
    { 0x42000001 },
};

union AnimationStep D_800FCE00[] = {
    { 0x43000001 },
};

union AnimationStep* D_800FCE04[] = {
    D_800FCB54,
    D_800FCB58,
    D_800FCB74,
    D_800FCB90,
    D_800FCBAC,
    D_800FCBB4,
    D_800FCBBC,
    D_800FCBC4,
    D_800FCBE0,
    D_800FCBFC,
    D_800FCCE0,
    D_800FCD14,
    D_800FCD54,
    D_800FCC18,
    D_800FCC2C,
    D_800FCC40,
    D_800FCC54,
    D_800FCC7C,
    D_800FCCA4,
    D_800FCCB8,
    D_800FCCCC,
    D_800FCD94,
    D_800FCDA8,
    D_800FCDAC,
    D_800FCDE8,
    D_800FCDEC,
    D_800FCDF0,
    D_800FCDF4,
    D_800FCDF8,
    D_800FCDFC,
    D_800FCE00,
};

u8 D_800FCE80[] = {
    0x18,
    0x19,
    0x1A,
    0x1B,
    0x1C,
    0x1D,
    0x1E,
    0x00,
};

void (*D_800FCE88[])() = {
    func_80055F1C,
    func_80055FD0,
};

struct VisualSpawnOffset D_800FCE90[5] = {
    { -23, -5 },
    { -23, 2 },
    { -29, 1 },
    { -29, 4 },
    { -39, -2 },
};

struct Unk_unk68 D_800FCE9C[] = {
    { -1, -6, 246, 0 },
};

void (*D_800FCEA0[])() = {
    func_80056230,
    func_800562AC,
    func_80056470,
};

void (*D_800FCEAC[])() = {
    func_8009216C,
    func_80056478,
    func_80055E9C,
    func_80055E04,
    func_80056018,
    func_80056054,
    func_800565EC,
};

void (*D_800FCEC8[])() = {
    func_800564B4,
    func_80056618,
    func_80056718,
};
