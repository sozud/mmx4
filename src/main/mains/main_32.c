// MainObj, main_object_update_funcs[32]
// 8005C824..8005D1F4
#include "common.h"
#include "func_tables.h"

void func_8005C824(struct MainObj* arg0)
{
    D_800FDD2C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005C860);

void func_8005C960(struct MainObj* arg0)
{
    s32 hit;
    u8 i;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FDD40[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (arg0->unk5 != 0) {
        arg0->ext.main_32.saved_unk5 = arg0->unk5;
    }
    for (i = 0; i < 2 - arg0->ext.main_32.unk88; i++) {
        arg0->unk54 = (const u8*)D_800FDD38[i];
        hit = func_8002DD04(arg0);
        if (hit < 0) {
            if (i == 0 && arg0->ext.main_32.unk88 == 0) {
                func_8005D148(arg0);
            }
            func_800AF808(BASE_OBJECT(arg0));
            func_800C813C(4, D_800FDD28, arg0);
            func_800BF60C(BASE_OBJECT(arg0), 8);
            arg0->state++;
            return;
        }
        if (hit != 0) {
            break;
        }
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
    } else {
        arg0->state++;
    }
}

void func_8005CADC(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8005CAFC(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_32.saved_unk5;
}

void func_8005CB08(struct MainObj* arg0)
{
    func_8005D118(arg0);
    D_800FDD5C[arg0->unk6](arg0);
}

void func_8005CB54(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->unk7C = 0xC8;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CB90);

void func_8005CC6C(struct MainObj* arg0)
{
    D_800FDD64[arg0->unk6](arg0);
}

void func_8005CCA8(struct MainObj* arg0)
{
    func_80015D60(arg0, 1);
    arg0->ext.main_32.unk80 = 5;
    arg0->unk20 = 0;
    arg0->unk54 = (const u8*)&D_800FDC80;
    arg0->unk50 = (const u8*)&D_800FDC80;
    arg0->unk6++;
}

void func_8005CCFC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_32.unk80 == 0) {
        arg0->ext.main_32.unk88 = 1;
        func_8005D148(arg0);
        arg0->ext.main_32.unk80 = 13;
        arg0->unk6++;
    }
}

void func_8005CD5C(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->ext.main_32.unk80 == 0) {
        func_80015D60(arg0, 3);
        arg0->unk5 = 4;
        arg0->unk6 = 0;
    }
}

void func_8005CDB0(struct MainObj* arg0)
{
    D_800FDD64[arg0->unk6 + 2](arg0);
}

void func_8005CDEC(struct MainObj* arg0)
{
    s32* velocity;
    s32 selected;
    u8 step;

    func_80015D60(arg0, 3);
    velocity = D_800FDC90;
    if (arg0->unk15 & 0x40) {
        velocity++;
    }
    selected = *velocity;
    step = arg0->unk6;
    arg0->unk24 = FIXED(0.3125);
    arg0->unk20 = selected;
    arg0->unk6 = step + 1;
}

void func_8005CE50(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8005CE80(struct MainObj* arg0)
{
    D_800FDD64[arg0->unk6 + 4](arg0);
}

void func_8005CEBC(struct MainObj* arg0)
{
    s32* velocity;
    s32 selected;

    func_80015D60(arg0, 3);
    velocity = D_800FDC90;
    if (arg0->unk15 & 0x40) {
        velocity++;
    }
    selected = *velocity;
    arg0->unk50 = (const u8*)&D_800FDC80;
    arg0->unk24 = 0;
    arg0->ext.main_32.unk88 = 1;
    arg0->unk20 = selected;
    arg0->unk6++;
}

void func_8005CF30(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8005CF60(struct MainObj* arg0)
{
    D_800FDD7C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_32", func_8005CF9C);

void func_8005D0A0(struct MainObj* arg0)
{
    s32 unused[1];
    s16 timer = arg0->unk7C;
    if (timer == 0) {
        arg0->unk6++;
    } else {
        arg0->unk7C = timer - 1;
    }
}

void func_8005D0D8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    arg0->unk24 += 0x100;
}

void func_8005D118(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

void func_8005D148(struct MainObj* arg0)
{
    struct ShotObj* temp_v0;

    temp_v0 = find_free_shot_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x41;
        temp_v0->id = 7;
        temp_v0->unk2 = 0;
        temp_v0->unk40 = arg0->unk40;
        temp_v0->unk42 = arg0->unk42;
        temp_v0->animation_table = (u32**)arg0->animation_table;
        temp_v0->unk3C = (u8*)arg0->sprite_frames;
        temp_v0->bg_offset = arg0->bg_offset;
        temp_v0->unk15 = arg0->unk15;
        temp_v0->x_pos.val = arg0->x_pos.val;
        temp_v0->y_pos.val = arg0->y_pos.val;
        temp_v0->unk7C = WEAPON_OBJECT(arg0);
        temp_v0->unk16 = 6;
    }
}

struct Unk_unk68 D_800FDC80 = { -11, -10, 21, 23 };

struct Unk_unk68 D_800FDC84 = { -9, 13, 16, 19 };

struct Unk_unk68 D_800FDC88[2] = {
    { -11, -10, 20, 42 },
    { -10, 27, 26, 3 },
};

s32 D_800FDC90[2] = { (s32)0xFFFD0000, (s32)0x00030000 };

s32 D_800FDC98[2] = { (s32)0xFFFC8000, (s32)0x00038000 };

union AnimationStep D_800FDCA0[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010004 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x05FB0005 },
};

union AnimationStep D_800FDCB8[] = {
    { 0x06010002 },
    { 0x07010002 },
    { 0x03010002 },
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A000003 },
};

union AnimationStep D_800FDCD0[] = {
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0B010002 },
    { 0x0DFD0002 },
};

union AnimationStep D_800FDCE0[] = {
    { 0x0E010005 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010005 },
    { 0x12010003 },
    { 0x13FB0003 },
};

union AnimationStep D_800FDCF8[] = {
    { 0x14000001 },
};

union AnimationStep D_800FDCFC[] = {
    { 0x15000001 },
};

union AnimationStep D_800FDD00[] = {
    { 0x16000001 },
};

union AnimationStep D_800FDD04[] = {
    { 0x17000001 },
};

union AnimationStep* D_800FDD08[8] = {
    D_800FDCA0,
    D_800FDCB8,
    D_800FDCD0,
    D_800FDCE0,
    D_800FDCF8,
    D_800FDCFC,
    D_800FDD00,
    D_800FDD04,
};

u8 D_800FDD28[4] = { 0x04, 0x05, 0x06, 0x07 };

void (*D_800FDD2C[3])() = {
    func_8005C860,
    func_8005C960,
    func_8005CADC,
};

struct Unk_unk68* D_800FDD38[2] = {
    &D_800FDC80,
    &D_800FDC84,
};

void (*D_800FDD40[7])() = {
    func_8009216C,
    func_8005CAFC,
    func_8005CB08,
    func_8005CC6C,
    func_8005CDB0,
    func_8005CE80,
    func_8005CF60,
};

void (*D_800FDD5C[2])() = {
    func_8005CB54,
    func_8005CB90,
};

void (*D_800FDD64[6])() = {
    func_8005CCA8,
    func_8005CCFC,
    func_8005CDEC,
    func_8005CE50,
    func_8005CEBC,
    func_8005CF30,
};

void (*D_800FDD7C[3])() = {
    func_8005CF9C,
    func_8005D0A0,
    func_8005D0D8,
};
