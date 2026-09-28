// MainObj, main_object_update_funcs[38]
// 80060A88..80061590
#include "common.h"
#include "func_tables.h"

void func_80060A88(struct MainObj* arg0)
{
    D_800FE8EC[arg0->state](arg0);
}

void func_80060AC4(struct MainObj* obj)
{
    obj->active = 0x41;
    obj->unk5C = 0x12;
    obj->unk60 = 6;
    obj->unk61 = 0;
    obj->bg_offset = g_Player.bg_offset;
    obj->collision_data = &D_801074F4;
    obj->animation_table = (const u8* const*)D_800FE890;
    obj->unk16 = 5;
    obj->unk68 = &D_800FE73C;
    obj->unk54 = &D_800FE734;
    obj->unk15 = 0;
    obj->unk20 = 0;
    obj->unk24 = 0;
    obj->unk28 = 0;
    obj->unk2C = 0;
    obj->unk67 = 0;
    obj->unk50 = &D_800FE738;
    obj->unk18.val = obj->x_pos.val;
    obj->unk1C.val = obj->y_pos.val;
    func_80015D60(obj, 0);
    obj->unk7E = 0xA;
    obj->ext.main_38.saved_unk5 = 0;
    obj->ext.main_38.unk84 = 0;
    obj->ext.main_38.unk88 = 0;
    obj->ext.main_38.unk8C = 0;
    obj->ext.main_38.unk90 = 0;
    obj->ext.main_38.unk94 = 0;
    obj->unk7C = 0;
    obj->unk5 = 2;
    obj->unk6 = 0;
    obj->state++;
}

void func_80060BC4(struct MainObj* arg0)
{
    s32 collision;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FE8FC[arg0->unk5](arg0);
    collision = func_8002DD04(arg0);
    func_8002D9BC(arg0);
    func_8002E184(PLAYER_OBJECT(arg0));
    if (arg0->unk5 != 0) {
        arg0->ext.main_38.saved_unk5 = arg0->unk5;
    }
    if (collision < 0) {
        func_800C813C(6, D_800FE8E4, arg0);
        if (engine_obj.stage == 8) {
            func_800DABE4(0xB, (s16)(arg0->x_pos.i.hi - 0x28), arg0->y_pos.i.hi);
        }
        arg0->ext.main_38.unk88 = 2;
        arg0->ext.main_38.unk8C = 1;
        arg0->unk7C = 0x20;
        arg0->unk7E = 5;
        arg0->on_screen = 0;
        arg0->state++;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x50, 0x40) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x40, 0x20);
        return;
    }
    if (arg0->unk5 != 4) {
        if (g_Player.x_pos.val > arg0->x_pos.val) {
            arg0->state += 2;
        } else {
            arg0->unk5 = 2;
        }
    }
}

void func_80060D3C(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_800BF60C(BASE_OBJECT(arg0), 8);
        arg0->state++;
    }
    if (--arg0->unk7E == 0) {
        func_800AF878(BASE_OBJECT(arg0), 0, 0x18, 0x10);
        arg0->unk7E = 5;
    }
}

void func_80060DC8(struct MainObj* arg0)
{
    arg0->ext.main_38.unk88 = 2;
    if (arg0->ext.main_38.unk8C != 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    } else {
        func_8002B0C8(OBJECT_HEADER(arg0));
    }
}

void func_80060E08(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_38.saved_unk5;
}

void func_80060E14(struct MainObj* arg0)
{
    D_800FE918[arg0->unk6](arg0);
}

void func_80060E50(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(ANIMATED_OBJECT(arg0), 0);
    arg0->unk6++;
}

void func_80060E94(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7E == 0) {
        switch (arg0->ext.main_38.unk84) {
        case 0:
            arg0->unk5 = 3;
            arg0->unk7E = 0x14;
            break;
        case 1:
            arg0->unk5 = 5;
            arg0->unk7E = 0x14;
            break;
        case 2:
            arg0->unk5 = 5;
            arg0->unk7E = 0xA;
            break;
        }
        arg0->unk6 = 0;
        if (arg0->ext.main_38.unk84 != 2) {
            arg0->ext.main_38.unk84++;
        } else {
            arg0->ext.main_38.unk84 = 0;
        }
    }
}

void func_80060F5C(struct MainObj* arg0)
{
    D_800FE920[arg0->unk6](arg0);
}

void func_80060F98(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 1);
    func_8001540C(2, 0x60, arg0);
    func_800614E8(VISUAL_OBJECT(arg0));
    arg0->unk7C = 0x50;
    arg0->unk6++;
}

void func_80060FF8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 4;
        arg0->ext.main_38.unk88 = 1;
        arg0->unk6 = 0;
    }
}

void func_8006104C(struct MainObj* arg0)
{
    D_800FE928[arg0->unk6](arg0);
}

void func_80061088(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0x61, arg0);
    func_80015D60(arg0, 2);
    arg0->ext.main_38.unk88 = 2;
    func_8006135C(arg0);
    arg0->unk7C = 0x6E;
    arg0->unk6++;
}

void func_800610F0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 0);
        arg0->ext.main_38.unk88 = 0;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_8006114C(struct MainObj* arg0)
{
    D_800FE930[arg0->unk6](arg0);
}

void func_80061188(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0x62, arg0);
    func_80015D60(arg0, 5);
    arg0->unk7C = 0xA;
    arg0->unk6++;
}

void func_800611E0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80061424(arg0);
        arg0->unk7C = 0x14;
        arg0->unk6++;
    }
}

void func_80061240(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 6;
        arg0->unk6 = 0;
    }
}

void func_8006128C(struct MainObj* arg0)
{
    D_800FE93C[arg0->unk6](arg0);
}

void func_800612C8(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    func_80015D60(arg0, 6);
    arg0->unk7C = 0x28;
    arg0->unk6++;
}

void func_80061310(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_8006135C(struct PlayerObj* arg0)
{
    s32 is_zero;
    struct ShotObj* shot;
    u8 i;
    for (i = 0; i < 2; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x14;
            shot->unk2 = i;
            shot->unk7C = WEAPON_OBJECT(arg0);
            shot->unk42 = arg0->unk42;
            shot->animation_table = D_800FE890;
            shot->unk3C = arg0->unk3C;
            shot->unk40 = arg0->unk40;
            shot->unk15 = arg0->unk15;
            shot->bg_offset = arg0->bg_offset;
            is_zero = (arg0->unk2 == 0);
            shot->unk16 = is_zero ? 2 : 1;
        }
    }
}

void func_80061424(struct MainObj* arg0)
{
    s32 is_zero;
    struct ShotObj* shot;
    u8 i;
    for (i = 0; i < 2; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x15;
            shot->unk2 = i;
            shot->unk7C = WEAPON_OBJECT(arg0);
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)D_800FE890;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->unk40 = arg0->unk40;
            shot->unk15 = arg0->unk15;
            shot->bg_offset = arg0->bg_offset;
            is_zero = (i == 0);
            shot->unk16 = is_zero ? 4 : 6;
        }
    }
}

void func_800614E8(struct VisualObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x10;
        obj->unk2 = 0;
        obj->unk50 = (struct PlayerObj*)arg0;
        obj->unk42 = arg0->unk42;
        obj->animation_table = D_800FE890;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 4;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}

struct Unk_unk68 D_800FE734 = { -54, -9, 90, 25 };

struct Unk_unk68 D_800FE738 = { -52, -11, 86, 25 };

struct Unk_unk68 D_800FE73C = { -10, 8, 45, 11 };

union AnimationStep D_800FE740[] = {
    { 0x00000001 },
};

union AnimationStep D_800FE744[] = {
    { 0x00010001 },
    { 0x01010006 },
    { 0x02010005 },
    { 0x03010004 },
    { 0x04010004 },
    { 0x05010004 },
    { 0x06010004 },
    { 0x07FD0004 },
};

union AnimationStep D_800FE764[] = {
    { 0x0C010002 },
    { 0x0DFF0002 },
};

union AnimationStep D_800FE76C[] = {
    { 0x0F01000A },
    { 0x10010008 },
    { 0x11010004 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010001 },
    { 0x15FD0001 },
};

union AnimationStep D_800FE788[] = {
    { 0x1601000A },
    { 0x17010008 },
    { 0x18010004 },
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1B010001 },
    { 0x1CFD0001 },
};

union AnimationStep D_800FE7A4[] = {
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010002 },
    { 0x20010003 },
    { 0x21010004 },
    { 0x22000005 },
};

union AnimationStep D_800FE7DC[] = {
    { 0x22010005 },
    { 0x23010005 },
    { 0x2401000A },
    { 0x25010005 },
    { 0x2601000A },
    { 0x27000005 },
};

union AnimationStep D_800FE7F4[] = {
    { 0x28000001 },
};

union AnimationStep D_800FE7F8[] = {
    { 0x29000001 },
};

union AnimationStep D_800FE7FC[] = {
    { 0x2A000001 },
};

union AnimationStep D_800FE800[] = {
    { 0x2B000001 },
};

union AnimationStep D_800FE804[] = {
    { 0x14010001 },
    { 0x13010001 },
    { 0x12010001 },
    { 0x11010004 },
    { 0x10010008 },
    { 0x0F00000A },
};

union AnimationStep D_800FE81C[] = {
    { 0x1B010001 },
    { 0x1A010001 },
    { 0x19010001 },
    { 0x18010004 },
    { 0x17010008 },
    { 0x1600000A },
};

union AnimationStep D_800FE834[] = {
    { 0x2C000001 },
};

union AnimationStep D_800FE838[] = {
    { 0x2D000001 },
};

union AnimationStep D_800FE83C[] = {
    { 0x2E000001 },
};

union AnimationStep D_800FE840[] = {
    { 0x2F000001 },
};

union AnimationStep D_800FE844[] = {
    { 0x30000001 },
};

union AnimationStep D_800FE848[] = {
    { 0x31000001 },
};

union AnimationStep D_800FE84C[] = {
    { 0x08010003 },
    { 0x09010004 },
    { 0x0A010005 },
    { 0x09010004 },
    { 0x08FC0003 },
};

union AnimationStep D_800FE860[] = {
    { 0x37010003 },
    { 0x0B010003 },
    { 0x37010003 },
    { 0x32010003 },
    { 0x37010003 },
    { 0x33010003 },
    { 0x37010003 },
    { 0x34010003 },
    { 0x37010003 },
    { 0x35010003 },
    { 0x37010003 },
    { 0x36F60003 },
};

union AnimationStep* D_800FE890[21] = {
    D_800FE740,
    D_800FE744,
    D_800FE764,
    D_800FE76C,
    D_800FE788,
    D_800FE7A4,
    D_800FE7DC,
    D_800FE7F4,
    D_800FE7F8,
    D_800FE7FC,
    D_800FE800,
    D_800FE804,
    D_800FE81C,
    D_800FE834,
    D_800FE838,
    D_800FE83C,
    D_800FE840,
    D_800FE844,
    D_800FE848,
    D_800FE84C,
    D_800FE860,
};

u8 D_800FE8E4[8] = { 13, 14, 15, 16, 17, 18, 0, 0 };

void (*D_800FE8EC[])(struct MainObj*) = {
    func_80060AC4,
    func_80060BC4,
    func_80060D3C,
    func_80060DC8,
};

void (*D_800FE8FC[7])() = {
    func_8009216C,
    func_80060E08,
    func_80060E14,
    func_80060F5C,
    func_8006104C,
    func_8006114C,
    func_8006128C,
};

void (*D_800FE918[2])() = { func_80060E50, func_80060E94 };

void (*D_800FE920[2])() = { func_80060F98, func_80060FF8 };

void (*D_800FE928[2])(struct MainObj*) = { func_80061088, func_800610F0 };

void (*D_800FE930[3])(struct MainObj*) = { func_80061188, func_800611E0, func_80061240 };

void (*D_800FE93C[2])() = { func_800612C8, func_80061310 };
