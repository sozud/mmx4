// MainObj, main_object_update_funcs[34]
// 8005E570..8005EC58
#include "common.h"

extern union AnimationStep* D_800FE0FC[27];
#include "func_tables.h"

void func_8005E570(struct MainObj* arg0)
{
    D_800FE168[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005E5C0);

void func_8005E754(struct MainObj* arg0)
{
    D_800FE174[arg0->unk5](arg0);
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->state = 2;
    arg0->unk5 = 0;
}

void func_8005E7CC(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8005E7EC(struct MainObj* arg0)
{
    if (D_800FDFBC[arg0->unk2] >= arg0->x_pos.i.hi) {
        SP_CUR_MAIN_OBJ->ext.main_34.unk80 = 1;
        func_80015D60(arg0, 0);
        arg0->unk5 = 1;
    }
    func_8002B718(MOVING_OBJECT(arg0));
}

void func_8005E860(struct MainObj* arg0)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_34.unk80 <= 0) {
        func_80015D60(arg0, 2);
        arg0->unk5 = 2;
    }
}

void func_8005E8B4(struct MainObj* arg0)
{
    D_800FE19C[arg0->unk6](arg0);
}

void func_8005E8F0(struct MainObj* arg0)
{
    struct ShotObj* shot;

    if (arg0->animation_step.fields.event == 1) {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x13;
            shot->unk40 = arg0->unk40;
            shot->animation_table = (u32**)D_800FE0FC;
            shot->unk42 = arg0->unk42;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->unk2 = 0;
            shot->bg_offset = arg0->bg_offset;
            shot->x_pos.val = arg0->x_pos.val - 0x10;
            shot->y_pos.val = arg0->y_pos.val - 0x20;
            shot->unk7C = arg0->backref;
            SP_CUR_MAIN_OBJ->ext.main_34.unk82 = 0;
            arg0->unk6++;
        }
    }
}

void func_8005E9C0(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 2) {
        if (arg0->unk2 == arg0->animation_step.fields.event) {
            arg0->unk68 = &D_800FDFB8;
        }
        arg0->unk6++;
        func_80015D60(arg0, 3);
    }
}

void func_8005EA18(struct MainObj* arg0)
{
    s32 value20;
    s32 value24;

    value20 = FIXED(-0.9375);
    value24 = FIXED(1.75);
    arg0->unk24 = value24;
    arg0->unk2C = FIXED(0.5);
    arg0->unk20 = value20;
    arg0->unk67 = 1;
    func_8002B694(ANIMATED_OBJECT(arg0));
    arg0->unk6++;
}

void func_8005EA78(struct MainObj* arg0)
{
    s8 step;
    u8 count;

    if (arg0->unk70 & 8) {
        arg0->unk67 = 0;
        count = SP_CUR_MAIN_OBJ->ext.main_34.unk82 + 1;
        SP_CUR_MAIN_OBJ->ext.main_34.unk82 = count;
        if (count == 3) {
            step = arg0->unk6 + 1;
        } else {
            step = arg0->unk6 - 1;
        }
        arg0->unk6 = step;
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_8005EAF8(struct MainObj* arg0)
{
    func_80015D60(arg0, 4);
    SP_CUR_MAIN_OBJ->ext.main_34.unk80 = 0x30;
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

INCLUDE_ASM("main/nonmatchings/mains/main_34", func_8005EB40);

void func_8005EBF4(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->y_pos.i.hi >= 0x210) {
        arg0->state = 2;
        arg0->unk5 = 0;
    }
}

void func_8005EC38(struct MainObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
}

struct Unk_unk68 D_800FDFB8 = { 0, 0, 16, 21 };

u16 D_800FDFBC[4] = { 0x09D0, 0x0E28, 0x14D8, 0x1B48 };

union AnimationStep D_800FDFC4[] = {
    { 0x00000001 },
};

union AnimationStep D_800FDFC8[] = {
    { 0x01010004 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x05010004 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08F90003 },
};

union AnimationStep D_800FDFE8[] = {
    { 0x09010002 },
    { 0x0A010004 },
    { 0x0B010003 },
    { 0x0C010102 },
    { 0x0D000212 },
};

union AnimationStep D_800FDFFC[] = {
    { 0x0D010006 },
    { 0x0EFF0004 },
};

union AnimationStep D_800FE004[] = {
    { 0x0F010004 },
    { 0x10FF0004 },
};

union AnimationStep D_800FE00C[] = {
    { 0x10000004 },
};

union AnimationStep D_800FE010[] = {
    { 0x11000004 },
};

union AnimationStep D_800FE014[] = {
    { 0x0001000F },
    { 0x1201000E },
    { 0x0001000F },
    { 0x13FD0010 },
};

union AnimationStep D_800FE024[] = {
    { 0x0001000B },
    { 0x1401000A },
    { 0x1501000A },
    { 0x1601000B },
    { 0x1501000A },
    { 0x14FD000A },
};

union AnimationStep D_800FE03C[] = {
    { 0x17010102 },
    { 0x18010003 },
    { 0x19010005 },
    { 0x1A010006 },
    { 0x1B000007 },
};

union AnimationStep D_800FE050[] = {
    { 0x1C010008 },
    { 0x27FF0009 },
};

union AnimationStep D_800FE058[] = {
    { 0x1D01000A },
    { 0x1E010007 },
    { 0x18000006 },
};

union AnimationStep D_800FE064[] = {
    { 0x1F010006 },
    { 0x2000000A },
};

union AnimationStep D_800FE06C[] = {
    { 0x2001000A },
    { 0x1F000006 },
};

union AnimationStep D_800FE074[] = {
    { 0x21010014 },
    { 0x22010310 },
    { 0x22000010 },
};

union AnimationStep D_800FE080[] = {
    { 0x23010014 },
    { 0x24010310 },
    { 0x24000010 },
};

union AnimationStep D_800FE08C[] = {
    { 0x25010014 },
    { 0x26010310 },
    { 0x26000010 },
};

union AnimationStep D_800FE098[] = {
    { 0x28010002 },
    { 0x29010003 },
    { 0x2AFF0005 },
};

union AnimationStep D_800FE0A4[] = {
    { 0x2B010004 },
    { 0x2C010005 },
    { 0x2D010006 },
    { 0x2E010006 },
    { 0x2F010005 },
    { 0x30000004 },
};

union AnimationStep D_800FE0BC[] = {
    { 0x31010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x3AFD0002 },
};

union AnimationStep D_800FE0CC[] = {
    { 0x34000002 },
};

union AnimationStep D_800FE0D0[] = {
    { 0x35000002 },
};

union AnimationStep D_800FE0D4[] = {
    { 0x36000002 },
};

union AnimationStep D_800FE0D8[] = {
    { 0x37000002 },
};

union AnimationStep D_800FE0DC[] = {
    { 0x38000002 },
};

union AnimationStep D_800FE0E0[] = {
    { 0x39000002 },
};

union AnimationStep D_800FE0E4[] = {
    { 0x09010008 },
    { 0x0A010005 },
    { 0x0B010004 },
    { 0x0C010003 },
    { 0x0D010112 },
    { 0x0D000003 },
};

union AnimationStep* D_800FE0FC[27] = {
    D_800FDFC4,
    D_800FDFC8,
    D_800FDFE8,
    D_800FDFFC,
    D_800FE004,
    D_800FE00C,
    D_800FE010,
    D_800FE014,
    D_800FE024,
    D_800FE050,
    D_800FE064,
    D_800FE06C,
    D_800FE074,
    D_800FE080,
    D_800FE08C,
    D_800FE098,
    D_800FE0BC,
    D_800FE0CC,
    D_800FE0D0,
    D_800FE0D4,
    D_800FE0D8,
    D_800FE0DC,
    D_800FE0E0,
    D_800FE058,
    D_800FE0A4,
    D_800FE03C,
    D_800FE0E4,
};

void (*D_800FE168[3])() = {
    func_8005E5C0,
    func_8005E754,
    func_8005E7CC,
};

void (*D_800FE174[6])(struct MainObj*) = {
    func_8005E7EC,
    func_8005E860,
    func_8005E8B4,
    func_8005EB40,
    func_8005EBF4,
    func_8005EC38,
};

u16 D_800FE18C[8] = {
    0x0A48,
    0x0140,
    0x0EA8,
    0x0170,
    0x1528,
    0x014A,
    0x1BC8,
    0x0170,
};

void (*D_800FE19C[5])() = {
    func_8005E8F0,
    func_8005E9C0,
    func_8005EA18,
    func_8005EA78,
    func_8005EAF8,
};
