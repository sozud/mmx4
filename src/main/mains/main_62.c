// MainObj, main_object_update_funcs[62]
// 8007B90C..8007BFF4
#include "common.h"
#include "func_tables.h"

INCLUDE_ASM("main/nonmatchings/mains/main_62", func_8007B90C);

INCLUDE_ASM("main/nonmatchings/mains/main_62", func_8007BABC);

void func_8007BB90(struct MainObj* arg0)
{
    if (func_8007BABC(arg0) == 0) {
#ifdef MMX4_PC
        if ((arg0->unk2 >= 4) || (arg0->ext.main_62.unk80->animation_step.fields.event != 0)) {
#else
        if ((arg0->ext.main_62.unk80->animation_step.fields.event != 0) || (arg0->unk2 >= 4)) {
#endif
            func_80015D60(arg0, 2);
            arg0->unk5 = 2;
            arg0->state++;
        }
    }
}

void func_8007BC0C(struct BarObj* arg0)
{
    D_80102214[arg0->unk5](arg0);
}

void func_8007BC48(struct MainObj* arg0)
{
}

void func_8007BC50(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5++;
        arg0->unk7E = (u16)arg0->unk7C;
    }
    if (arg0->animation_step.fields.frame_index != 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
        arg0->ext.main_62.unk86 = (u8)arg0->on_screen;
    }
}

void func_8007BCC4(struct MainObj* arg0)
{
    s16 timer;

    timer = arg0->unk7E;
    if (timer == 0) {
        if (func_8007BABC(arg0) == 0) {
            arg0->unk5--;
            func_80015D60(arg0, 2);
            if (arg0->ext.main_62.unk86 != 0) {
                func_8001540C(2, 0xA2, arg0);
            }
        }
    } else {
        arg0->unk7E = timer - 1;
    }
}

void func_8007BD4C(struct MainObj* self)
{
    s32 result;
    u8 frame_index;

    D_8010221C[self->unk5](self);
    frame_index = self->animation_step.fields.frame_index;
    if ((3 <= frame_index) && (frame_index < 12)) {
        self->unk54 = D_80102130[frame_index - 3];
        self->unk50 = D_80102154[self->animation_step.fields.frame_index - 3];
    } else {
        self->unk54 = NULL;
        self->unk50 = NULL;
    }
    result = func_8002DD04(self);
    if ((result == 3) || (result == 0xC) || (result == 0x22)) {
        self->unk7E = 0x14;
        self->unk5 = 0;
        self->state++;
        self->unk42 = (self->unk42 & 0x7FFF) + 2;
    } else {
        func_8002D9BC(self);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_62", func_8007BE40);

void func_8007BF74(void)
{
}

void func_8007BF7C(struct BarObj* arg0)
{
    D_80102254[arg0->unk5](arg0);
}

void func_8007BFB8(struct MainObj* arg0)
{
    arg0->on_screen = 0;
    D_8010225C[arg0->state](arg0);
}

struct Unk_unk68 D_801020E4 = { 88, -26, 14, 18 };

struct Unk_unk68 D_801020E8 = { 71, -44, 14, 24 };

struct Unk_unk68 D_801020EC = { 53, -61, 20, 22 };

struct Unk_unk68 D_801020F0 = { 22, -72, 38, 14 };

struct Unk_unk68 D_801020F4 = { -21, -74, 68, 15 };

struct Unk_unk68 D_801020F8 = { -44, -64, 23, 16 };

struct Unk_unk68 D_801020FC = { -99, -32, 23, 25 };

struct Unk_unk68 D_80102100 = { -101, -18, 37, 8 };

struct Unk_unk68 D_80102104 = { -91, -18, 20, 8 };

struct Unk_unk68 D_80102108 = { 83, -32, 25, 25 };

struct Unk_unk68 D_8010210C = { 66, -48, 37, 47 };

struct Unk_unk68 D_80102110 = { 49, -64, 65, 50 };

struct Unk_unk68 D_80102114 = { 11, -83, 89, 63 };

struct Unk_unk68 D_80102118 = { -28, -88, 125, 44 };

struct Unk_unk68 D_8010211C = { -65, -93, -126, 62 };

struct Unk_unk68 D_80102120 = { -114, -53, 63, 51 };

struct Unk_unk68 D_80102124 = { -117, -35, 80, 32 };

struct Unk_unk68 D_80102128 = { -107, -30, 59, 26 };

struct Unk_unk68 D_8010212C = { 72, -35, 49, 38 };

struct Unk_unk68* D_80102130[9] = {
    &D_80102108,
    &D_8010210C,
    &D_80102110,
    &D_80102114,
    &D_80102118,
    &D_8010211C,
    &D_80102120,
    &D_80102124,
    &D_80102128,
};

struct Unk_unk68* D_80102154[9] = {
    &D_801020E4,
    &D_801020E8,
    &D_801020EC,
    &D_801020F0,
    &D_801020F4,
    &D_801020F8,
    &D_801020FC,
    &D_80102100,
    &D_80102104,
};

union AnimationStep D_80102178[] = {
    { 0x00010002 },
    { 0x01010101 },
    { 0x01000102 },
};

union AnimationStep D_80102184[] = {
    { 0x02000006 },
};

union AnimationStep D_80102188[] = {
    { 0x00010007 },
    { 0x03010007 },
    { 0x04010007 },
    { 0x05010007 },
    { 0x06010007 },
    { 0x07010007 },
    { 0x08010007 },
    { 0x09010007 },
    { 0x0A010007 },
    { 0x0B010007 },
    { 0x0C010007 },
    { 0x13010007 },
    { 0x14010006 },
    { 0x14000001 },
};

union AnimationStep D_801021C0[] = {
    { 0x0D000001 },
};

union AnimationStep D_801021C4[] = {
    { 0x0E000001 },
};

union AnimationStep D_801021C8[] = {
    { 0x0F000001 },
};

union AnimationStep D_801021CC[] = {
    { 0x10000001 },
};

union AnimationStep D_801021D0[] = {
    { 0x11000001 },
};

union AnimationStep D_801021D4[] = {
    { 0x12000001 },
};

union AnimationStep* D_801021D8[9] = {
    D_80102178,
    D_80102184,
    D_80102188,
    D_801021C0,
    D_801021C4,
    D_801021C8,
    D_801021CC,
    D_801021D0,
    D_801021D4,
};

struct Unk_unk68 D_801021FC[2] = {
    { 3, 4, 3, 4 },
    { 3, 4, 0, 0 },
};

struct Unk_unk68 D_80102204[2] = {
    { 5, 6, 7, 8 },
    { 5, 6, 7, 8 },
};

u8 D_8010220C[8] = { 0x14, 0x14, 0x28, 0x28, 0x14, 0x14, 0x28, 0x28 };

void (*D_80102214[2])() = {
    func_8007B90C,
    func_8007BB90,
};

void (*D_8010221C[4])() = {
    func_8009216C,
    func_8007BC48,
    func_8007BC50,
    func_8007BCC4,
};

s16 D_8010222C[20] = {
    (s16)0x005F,
    (s16)0xFFEF,
    (s16)0x0051,
    (s16)0xFFE4,
    (s16)0x0051,
    (s16)0xFFE4,
    (s16)0x0042,
    (s16)0xFFD1,
    (s16)0x0023,
    (s16)0xFFBF,
    (s16)0xFFFC,
    (s16)0xFFBE,
    (s16)0xFFDB,
    (s16)0xFFC8,
    (s16)0xFFA6,
    (s16)0xFFED,
    (s16)0xFFAD,
    (s16)0xFFF3,
    (s16)0xFFAD,
    (s16)0xFFF3,
};

void (*D_80102254[2])() = {
    func_8007BE40,
    func_8007BF74,
};

void (*D_8010225C[3])() = {
    func_8007BC0C,
    func_8007BD4C,
    func_8007BF7C,
};
