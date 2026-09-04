// MainObj, main_object_update_funcs[10]
// 800498C8..8004A718
#include "common.h"

// didn't notice any differences when nopped out
void func_800498C8(struct Unk* arg0)
{
    D_800FB0F4[arg0->base.state](arg0);
}

void func_80049904(struct Unk* arg0)
{
    arg0->unk5C = 6;
    arg0->unk60 = 3;
    arg0->unk61 = 0;
    arg0->collision_data = D_80106770;
    arg0->base.bg_offset = g_Player.base.bg_offset;
    arg0->base.unk16 = 6;
    arg0->animation_table = D_800FB0BC;
    arg0->unk68 = &D_800FAEFC;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk54 = (s32)D_800FAEF0;
    arg0->unk50 = (s32)D_800FAEF0;
    arg0->unk62 = 0;
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    func_80015D60(arg0, 0);

    switch (arg0->base.unk2) {
    case 0:
        if (arg0->base.x_pos.val > g_Player.base.x_pos.val) {
            arg0->base.unk15 = 0;
        } else {
            arg0->base.unk15 = 0x40;
        }
        arg0->state_8c.unk8C = 1;
        arg0->unk90 = 1;
        break;
    case 1:
        arg0->unk7A = 1;
        arg0->base.unk15 = 0x40;
        arg0->state_8c.unk8C = 0;
        arg0->unk90 = 1;
        break;
    case 2:
        arg0->unk7A = 1;
        arg0->base.unk15 = 0;
        arg0->state_8c.unk8C = 0;
        arg0->unk90 = 1;
        break;
    case 3:
    case 4:
    case 9:
    case 10:
        arg0->unk7A = 1;
        arg0->state_8c.unk8C = 0;
        arg0->unk90 = 0;
        break;
    case 5:
    case 6:
    case 11:
    case 12:
        arg0->unk7A = 1;
        arg0->unk2C = -0x600;
        arg0->state_8c.unk8C = 0;
        arg0->unk90 = 0;
        break;
    case 7:
    case 8:
    case 13:
    case 14:
        arg0->unk7A = 1;
        arg0->unk2C = 0x600;
        arg0->state_8c.unk8C = 0;
        arg0->unk90 = 0;
        break;
    }
    arg0->unk7C = 1;
    arg0->base.state = 1;
    arg0->unk84 = 0;
    arg0->base.unk5 = 2;
    arg0->base.unk6 = 0;
}

void func_80049AA0(struct Unk* arg0)
{
    s8* temp_s1;
    s16 temp_v0;

    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;
    D_800FB104[arg0->base.unk5](arg0);
    if (arg0->state_8c.unk8C != 0) {
        if (arg0->unk90 != 0) {
            temp_s1 = &g_Player.unkBA;
            if ((*temp_s1 == 0) && (func_8002D9BC(arg0) != 0) && (*temp_s1 != 0)) {
                g_Player.unkA5 = arg0->base.unk15;
                arg0->state_8c.unk8C = 3;
            }
        }
        arg0->unk94 = arg0->base.unk5;
        if (func_8002DD04(arg0) < 0) {
            func_800AF808(arg0);
            func_800C813C(6, &D_800FB0EC, arg0);
            func_800BF60C(arg0, 0x11);
            arg0->base.state = 2;
        } else if (func_8002B1E8(arg0, 0x40, 0x40) == 0) {
            func_8002B318(arg0, 0x20, 0x20);
            if (--arg0->unk7C == 0) {
                func_8001540C(2, 0xD, arg0);
                arg0->unk7C = 0x3C;
            }
        } else {
            arg0->base.state = 2;
        }
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_80049C0C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_80049C78);

void func_80049CBC(struct Unk* arg0)
{
    arg0->base.unk5 = arg0->unk94;
}

void func_80049CC8(struct Unk* arg0)
{
    switch (arg0->base.unk2) {
    case 0:
        arg0->unk7A = 0;
        arg0->base.unk5 = 3;
        break;
    case 1:
        if (g_Player.base.x_pos.i.hi - arg0->base.x_pos.i.hi >= 0xC1) {
            arg0->state_8c.unk8C = 1;
            arg0->unk7A = 0;
            arg0->base.unk5 = 3;
        }
        break;
    case 2:
        if (arg0->base.x_pos.i.hi - g_Player.base.x_pos.i.hi >= 0xC1) {
            arg0->state_8c.unk8C = 1;
            arg0->unk7A = 0;
            arg0->base.unk5 = 3;
        }
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        if (g_Player.base.x_pos.i.hi - arg0->base.x_pos.i.hi >= 0xC1) {
            arg0->state_8c.unk8C = 1;
            arg0->unk7A = 0;
            arg0->base.unk15 = 0x40;
            if (!(arg0->base.unk2 & 1)) {
                arg0->unk20 = FIXED(8);
            } else {
                arg0->unk20 = FIXED(6);
            }
            arg0->base.unk5 = 6;
        }
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
        arg0->unk7A = 0;
        arg0->base.unk15 = 0;
        arg0->state_8c.unk8C = 1;
        if (!(arg0->base.unk2 & 1)) {
            arg0->unk20 = FIXED(-8);
        } else {
            arg0->unk20 = FIXED(-6);
        }
        arg0->base.unk5 = 6;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_80049DE8);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_80049E24);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_80049E68);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_80049F20);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_80049FE8);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_8004A0AC);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_8004A0FC);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_8004A178);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_8004A31C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_8004A378);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_8004A468);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_8004A5B0);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_8004A5E0);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_8004A644);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_8004A690);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_10", func_8004A6E8);

u8 D_800FAEF0[8] = { 0xEE, 0xEC, 0x2A, 0x24, 0xD7, 0xEA, 0x3F, 0x35 };

u32 D_800FAEF8 = 0x172009DB;

struct Unk_unk68 D_800FAEFC = { -24, 3, 0x0A, 0x02 };

u8 D_800FAF00[0xC] = {
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x00,
    0x01,
    0x01,
    0x01,
    0x01,
    0xFE,
    0x02,
};

u8 D_800FAF0C[0xF0] = {
    0x01,
    0x00,
    0x01,
    0x03,
    0x01,
    0x00,
    0x01,
    0x04,
    0x01,
    0x00,
    0x01,
    0x05,
    0x01,
    0x00,
    0x01,
    0x06,
    0x01,
    0x00,
    0x01,
    0x07,
    0x01,
    0x00,
    0x01,
    0x08,
    0x01,
    0x00,
    0x01,
    0x09,
    0x01,
    0x00,
    0x01,
    0x0A,
    0x01,
    0x00,
    0x01,
    0x0B,
    0x01,
    0x00,
    0x01,
    0x0C,
    0x01,
    0x00,
    0x01,
    0x0D,
    0x01,
    0x00,
    0x01,
    0x0E,
    0x01,
    0x00,
    0x01,
    0x0F,
    0x01,
    0x00,
    0x01,
    0x10,
    0x01,
    0x00,
    0x01,
    0x11,
    0x01,
    0x00,
    0x01,
    0x12,
    0x01,
    0x00,
    0x01,
    0x13,
    0x01,
    0x00,
    0x01,
    0x14,
    0x01,
    0x00,
    0x01,
    0x15,
    0x01,
    0x00,
    0x01,
    0x16,
    0x01,
    0x00,
    0x01,
    0x17,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x1B,
    0x01,
    0x00,
    0x01,
    0x1C,
    0x01,
    0x00,
    0x01,
    0x1D,
    0x01,
    0x00,
    0x01,
    0x1E,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x1F,
    0x01,
    0x00,
    0x01,
    0x20,
    0x01,
    0x00,
    0x01,
    0x21,
    0x01,
    0x00,
    0x01,
    0x22,
    0x01,
    0x00,
    0x01,
    0x23,
    0x01,
    0x00,
    0x01,
    0x24,
    0x01,
    0x00,
    0x01,
    0x25,
    0x01,
    0x00,
    0x01,
    0x26,
    0x01,
    0x00,
    0x01,
    0x27,
    0x01,
    0x00,
    0x01,
    0x28,
    0x01,
    0x00,
    0x01,
    0x29,
    0x01,
    0x00,
    0x01,
    0x2A,
    0x01,
    0x00,
    0x01,
    0x2B,
    0x01,
    0x00,
    0x01,
    0x2C,
    0x01,
    0x00,
    0x01,
    0x2D,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x01,
    0x00,
    0x1A,
};

u8 D_800FAFFC[0xC] = {
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0x01,
    0x19,
    0x01,
    0x01,
    0xFE,
    0x1A,
};

u8 D_800FB008[0x3C] = {
    0x01,
    0x00,
    0x01,
    0x2E,
    0x01,
    0x00,
    0x01,
    0x2F,
    0x01,
    0x00,
    0x01,
    0x30,
    0x01,
    0x00,
    0x01,
    0x31,
    0x01,
    0x00,
    0x01,
    0x32,
    0x01,
    0x00,
    0x01,
    0x30,
    0x01,
    0x00,
    0x01,
    0x31,
    0x01,
    0x00,
    0x01,
    0x33,
    0x01,
    0x00,
    0x01,
    0x34,
    0x01,
    0x00,
    0x01,
    0x35,
    0x01,
    0x00,
    0x01,
    0x36,
    0x01,
    0x00,
    0x01,
    0x37,
    0x01,
    0x00,
    0x01,
    0x38,
    0x01,
    0x00,
    0x01,
    0x36,
    0x01,
    0x01,
    0xFE,
    0x37,
};

u8 D_800FB044[0x3C] = {
    0x01,
    0x00,
    0x01,
    0x37,
    0x01,
    0x00,
    0x01,
    0x39,
    0x01,
    0x00,
    0x01,
    0x3A,
    0x01,
    0x00,
    0x01,
    0x3B,
    0x01,
    0x00,
    0x01,
    0x3C,
    0x01,
    0x00,
    0x01,
    0x3D,
    0x01,
    0x00,
    0x01,
    0x3E,
    0x01,
    0x00,
    0x01,
    0x3F,
    0x01,
    0x00,
    0x01,
    0x40,
    0x01,
    0x00,
    0x01,
    0x41,
    0x01,
    0x00,
    0x01,
    0x42,
    0x01,
    0x00,
    0x01,
    0x43,
    0x01,
    0x00,
    0x01,
    0x44,
    0x01,
    0x00,
    0x01,
    0x45,
    0x01,
    0x01,
    0xF5,
    0x46,
};

u8 D_800FB080[0x24] = {
    0x01,
    0x00,
    0x01,
    0x34,
    0x01,
    0x00,
    0x01,
    0x35,
    0x01,
    0x00,
    0x01,
    0x33,
    0x01,
    0x00,
    0x01,
    0x30,
    0x01,
    0x00,
    0x01,
    0x31,
    0x01,
    0x00,
    0x01,
    0x32,
    0x01,
    0x00,
    0x01,
    0x1A,
    0x01,
    0x00,
    0x01,
    0x18,
    0x01,
    0x00,
    0xFE,
    0x19,
};

u8 D_800FB0A4[4] = { 0x01, 0x01, 0x00, 0x47 };
u8 D_800FB0A8[4] = { 0x01, 0x01, 0x00, 0x48 };
u8 D_800FB0AC[4] = { 0x01, 0x01, 0x00, 0x49 };
u8 D_800FB0B0[4] = { 0x01, 0x01, 0x00, 0x4A };
u8 D_800FB0B4[4] = { 0x01, 0x01, 0x00, 0x4B };
u8 D_800FB0B8[4] = { 0x01, 0x01, 0x00, 0x4C };

const u8* D_800FB0BC[12] = {
    D_800FAF00,
    D_800FAF0C,
    D_800FAFFC,
    D_800FB008,
    D_800FB044,
    D_800FB080,
    D_800FB0A4,
    D_800FB0A8,
    D_800FB0AC,
    D_800FB0B0,
    D_800FB0B4,
    D_800FB0B8,
};

u8 D_800FB0EC[8] = { 6, 7, 8, 9, 10, 11, 0, 0 };

void (*D_800FB0F4[])(struct Unk*) = {
    func_80049904,
    func_80049AA0,
    func_80049C0C,
    func_80049C78,
};

void (*D_800FB104[])(struct Unk*) = {
    func_8009216C,
    func_80049CBC,
    func_80049CC8,
    func_80049DE8,
    func_8004A0AC,
    func_8004A5B0,
    func_8004A6E8,
};
