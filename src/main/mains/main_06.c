// MainObj, main_object_update_funcs[6]
// 80046B30..800473C8
#include "common.h"
#include "func_tables.h"

void bulldozer_update(struct MainObj* arg0)
{
    bulldozer_state_funcs[arg0->state](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_06", func_80046B80);

INCLUDE_ASM("main/nonmatchings/mains/main_06", func_80046C8C);

void bulldozer_cleanup(struct MainObj* arg0)
{
    arg0->ext.main_6.armor_broken = 0;
    arg0->ext.main_6.ground_probe_distance = 0;
    arg0->ext.main_6.armor_health = 0;
    arg0->ext.main_6.core_health = 0;
    arg0->ext.main_6.hitbox_toggle = 0;
    arg0->ext.main_6.saved_step = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
    func_80015930(2, 2);
}

void bulldozer_resume_step(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_6.saved_step;
}

void bulldozer_rev(struct MainObj* arg0)
{
    bulldozer_rev_funcs[arg0->unk6](arg0);
}

void bulldozer_rev_begin(struct MainObj* arg0)
{
    if (arg0->ext.main_6.armor_broken == 0) {
        arg0->ext.main_6.ground_probe_distance = 0x48;
        func_80015D60(arg0, 0);
    } else {
        arg0->ext.main_6.ground_probe_distance = 8;
        func_80015D60(arg0, 1);
    }
    arg0->unk7C = 0x28;
    arg0->unk6 = 1;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 2, arg0);
}

void func_80047140(struct MainObj* arg0)
{
    if (arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    } else {
        arg0->unk7C--;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void bulldozer_charge(struct MainObj* arg0)
{
    bulldozer_charge_funcs[arg0->unk6](arg0);
}

void func_800471C4(struct MainObj* arg0)
{
    if (arg0->unk15 & 0x40) {
        if (arg0->ext.main_6.armor_broken != 0) {
            arg0->unk20 = FIXED(2);
        } else {
            arg0->unk20 = FIXED(0.5);
        }
    } else {
        if (arg0->ext.main_6.armor_broken != 0) {
            arg0->unk20 = FIXED(-2);
        } else {
            arg0->unk20 = FIXED(-0.5);
        }
    }
    arg0->unk6 = 1;
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80047244(struct MainObj* arg0)
{
    s16 x;
    s16 y;

    if (arg0->unk15 != 0) {
        x = arg0->x_pos.u.hi + (s8)(u8)arg0->unk68->unk0 + arg0->ext.main_6.ground_probe_distance;
    } else {
        x = (arg0->x_pos.u.hi - (s8)(u8)arg0->unk68->unk0) - arg0->ext.main_6.ground_probe_distance;
    }

    y = arg0->unk68->unk3 + (arg0->y_pos.u.hi + (s8)(u8)arg0->unk68->unk1);
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) == 0x38) {
        func_8002B718(MOVING_OBJECT(arg0));
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80047314(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 0;
        return;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_80047378(struct MainObj* arg0)
{
    if (arg0->unk67 == 0 && !(arg0->unk70 & 8)) {
        arg0->unk5 = 4;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 1;
    }
}

struct Unk_unk68 D_800FA424 = { 1, -28, 47, 45 };

struct Unk_unk68 D_800FA428[2] = {
    { -50, -69, 46, 86 },
    { -18, -18, 68, 34 },
};

struct Unk_unk68 D_800FA430 = { -15, -1, 34, 18 };

struct Unk_unk68 D_800FA434[2] = {
    { -18, -18, 68, 34 },
    { -18, -18, 68, 34 },
};

union AnimationStep D_800FA43C[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x05010003 },
    { 0x06010003 },
    { 0x07F90003 },
};

union AnimationStep D_800FA45C[] = {
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0BFD0002 },
};

union AnimationStep D_800FA46C[] = {
    { 0x0C000001 },
};

union AnimationStep D_800FA470[] = {
    { 0x0D000001 },
};

union AnimationStep D_800FA474[] = {
    { 0x0E000001 },
};

union AnimationStep D_800FA478[] = {
    { 0x0F000001 },
};

union AnimationStep D_800FA47C[] = {
    { 0x10010003 },
    { 0x11010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14010003 },
    { 0x15010003 },
    { 0x16010003 },
    { 0x17010003 },
    { 0x18010003 },
    { 0x19010003 },
    { 0x1A010003 },
    { 0x1BF50003 },
};

union AnimationStep D_800FA4AC[] = {
    { 0x1C000001 },
};

union AnimationStep D_800FA4B0[] = {
    { 0x1D000001 },
};

union AnimationStep D_800FA4B4[] = {
    { 0x1E000001 },
};

union AnimationStep D_800FA4B8[] = {
    { 0x1F000001 },
};

union AnimationStep D_800FA4BC[] = {
    { 0x20000001 },
};

union AnimationStep D_800FA4C0[] = {
    { 0x21000001 },
};

union AnimationStep D_800FA4C4[] = {
    { 0x22000001 },
};

union AnimationStep D_800FA4C8[] = {
    { 0x23010003 },
    { 0x24010003 },
    { 0x25010003 },
    { 0x26FD0003 },
};

union AnimationStep D_800FA4D8[] = {
    { 0x27010003 },
    { 0x28010003 },
    { 0x29010003 },
    { 0x2AFD0003 },
};

union AnimationStep* D_800FA4E8[] = {
    D_800FA43C,
    D_800FA45C,
    D_800FA46C,
    D_800FA470,
    D_800FA474,
    D_800FA478,
    D_800FA47C,
    D_800FA4AC,
    D_800FA4B0,
    D_800FA4B4,
    D_800FA4B8,
    D_800FA4BC,
    D_800FA4C0,
    D_800FA4C4,
    D_800FA4C8,
    D_800FA4D8,
};

u8 D_800FA528[16] = {
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x0F,
    0x08,
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x0F,
    0x00,
};

void (*bulldozer_state_funcs[])() = {
    func_80046B80,
    func_80046C8C,
    bulldozer_cleanup,
};

void (*D_800FA544[])() = {
    func_8009216C,
    bulldozer_resume_step,
    bulldozer_rev,
    bulldozer_charge,
    func_80047314,
};

void (*bulldozer_rev_funcs[])() = {
    bulldozer_rev_begin,
    func_80047140,
};

void (*bulldozer_charge_funcs[])() = {
    func_800471C4,
    func_80047244,
};
