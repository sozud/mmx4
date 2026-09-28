// MainObj, main_object_update_funcs[41]
// 800623C4..80062D60
#include "common.h"
#include "func_tables.h"

void func_800623C4(struct MainObj* arg0)
{
    D_800FEE38[arg0->state](arg0);
}

void func_80062400(struct MainObj* arg0)
{
    s8 mode = 2;

    arg0->state = 1;
    if (arg0->unk2 != 0) {
        mode = 6;
    }
    arg0->unk5 = mode;
    arg0->unk5C = 3;
    arg0->unk60 = 3;
    arg0->animation_table = (const u8* const*)D_800FEDE0;
    arg0->unk50 = &D_800FEE34;
    arg0->unk68 = &D_800FEE30;
    arg0->collision_data = D_801060F0;
    arg0->unk16 = 5;
    arg0->unk6 = 0;
    arg0->unk7C = 0;
    arg0->bg_offset = 0;
    arg0->unk61 = 0;
    arg0->unk54 = NULL;
    arg0->unk67 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->ext.main_41.unk84 = 0;
    arg0->ext.main_41.unk83 = 0;
    arg0->ext.main_41.unk82 = 0;
    arg0->unk7E = 0xF0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
}

void func_800624B4(struct MainObj* arg0)
{
    struct ItemObj* item;

    item = find_free_item_obj();
    if (item != NULL) {
        item->active = arg0->active;
        item->id = 0x13;
        item->unk2 = -0x80;
        item->animation_table = arg0->animation_table;
        item->sprite_frames = arg0->sprite_frames;
        item->unk40 = arg0->unk40;
        item->unk42 = arg0->unk42;
        item->x_pos = arg0->x_pos;
        item->y_pos = arg0->y_pos;
        item->unk15 = arg0->unk15;
        item->ext.owner = arg0;
    }
}

void func_80062550(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->ext.main_41.unk84 = 0;
        arg0->ext.main_41.unk83 = 1;
        func_80015D60(arg0, arg0->ext.main_41.unk82 + 5);
    }
    if (!(arg0->unk70 & 8)) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        return;
    }
    func_80015DC8(arg0);
}

void func_800625C4(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->ext.main_41.unk84 = 1;
        arg0->ext.main_41.unk83 = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.2578125);
        func_80015D60(arg0, 4);
    }
    if (arg0->unk70 & 8) {
        arg0->unk5 = 4;
        arg0->unk6 = 0;
    } else {
        func_80015DC8(arg0);
        func_8002B694(ANIMATED_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062650);

void func_800626F0(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk7C = 1;
        arg0->ext.main_41.unk84 = 0;
        arg0->ext.main_41.unk83 = 1;
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80062650(arg0);
        if (arg0->ext.main_41.unk80 != 0) {
            arg0->unk5 = 5;
        } else {
            arg0->unk5 = 2;
        }
        arg0->unk6 = 0;
        return;
    }
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062778);

void func_80062910(struct MainObj* self)
{
    s16 timer;

    switch (self->unk6) {
    case 0:
        self->unk6 = 1;
        self->ext.main_41.unk84 = 0;
        self->ext.main_41.unk83 = 0;
        self->unk7C = 0;
        func_80015D60(self, 2);
        break;
    case 1:
        if (self->animation_step.fields.relative_step < 0) {
            self->unk6 = 2;
            func_80015D60(self, 3);
            return;
        }
        func_80015DC8(ANIMATED_OBJECT(self));
        break;
    case 2:
        timer = self->unk7C;
        if (timer >= 6) {
            self->unk5 = 2;
            self->unk6 = 0;
            if (self->on_screen != 0) {
                func_8001540C(2, 0xEB, self);
            }
            return;
        }
        if (self->animation_step.fields.relative_step < 0) {
            self->unk7C = timer + 1;
        }
        func_80015DC8(ANIMATED_OBJECT(self));
        break;
    }
}

void func_80062A0C(struct MainObj* self)
{
    s16 animation_count;
    s8 state;

    state = self->unk6;
    switch (state) {
    case 0:
        self->unk6 = 1;
        self->ext.main_41.unk84 = 0;
        self->ext.main_41.unk83 = 0;
        self->unk7C = 0;
        func_80015D60(self, 0xB);
        return;
    case 1:
        animation_count = self->unk7C;
        if (animation_count >= 6) {
            self->unk6 = 2;
            func_80015D60(self, 0xC);
            return;
        }
        if (self->animation_step.fields.relative_step < 0) {
            self->unk7C = animation_count + 1;
        }
        break;
    case 2:
        if (self->animation_step.fields.relative_step < 0) {
            self->state = 2;
            self->unk5 = 0;
            self->unk6 = 0;
            return;
        }
        break;
    default:
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062AEC);

INCLUDE_ASM("main/nonmatchings/mains/main_41", func_80062BBC);

void func_80062D18(struct MainObj* arg0)
{
}

void func_80062D20(struct MainObj* arg0)
{
    if (arg0->unk2 == 0) {
        func_8002B0C8(OBJECT_HEADER(arg0));
    } else {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

union AnimationStep D_800FEAA4[] = {
    { 0x00010005 },
    { 0x01010105 },
    { 0x02010205 },
    { 0x03010305 },
    { 0x04010405 },
    { 0x05FB0505 },
};

union AnimationStep D_800FEABC[] = {
    { 0x62010002 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0BFB0002 },
};

union AnimationStep D_800FEAD8[] = {
    { 0x0F010001 },
    { 0x3B010001 },
    { 0x0F010001 },
    { 0x3B010001 },
    { 0x0F010001 },
    { 0x3B010001 },
    { 0x10010001 },
    { 0x3B010001 },
    { 0x11010001 },
    { 0x3B010001 },
    { 0x12010001 },
    { 0x3B010001 },
    { 0x13010001 },
    { 0x3B010001 },
    { 0x14010001 },
    { 0x3B010001 },
    { 0x15010001 },
    { 0x3BEF0001 },
};

union AnimationStep D_800FEB20[] = {
    { 0x16010001 },
    { 0x17010001 },
    { 0x18FE0001 },
};

union AnimationStep D_800FEB2C[] = {
    { 0x00010004 },
    { 0x0C010005 },
    { 0x0D010006 },
    { 0x0E010007 },
    { 0x0D010006 },
    { 0x0C010005 },
    { 0x1C010004 },
    { 0x1D000001 },
};

union AnimationStep D_800FEB4C[] = {
    { 0x19010005 },
    { 0x1A010006 },
    { 0x1B010007 },
    { 0x1C010008 },
    { 0x1D000009 },
};

union AnimationStep D_800FEB60[] = {
    { 0x1E010005 },
    { 0x1F010006 },
    { 0x20010007 },
    { 0x21010008 },
    { 0x22000009 },
};

union AnimationStep D_800FEB74[] = {
    { 0x23010005 },
    { 0x24010006 },
    { 0x25010007 },
    { 0x26010008 },
    { 0x27000009 },
};

union AnimationStep D_800FEB88[] = {
    { 0x28010005 },
    { 0x29010006 },
    { 0x2A010007 },
    { 0x2B010008 },
    { 0x2C000009 },
};

union AnimationStep D_800FEB9C[] = {
    { 0x2D010005 },
    { 0x2E010006 },
    { 0x2F010007 },
    { 0x30010008 },
    { 0x31000009 },
};

union AnimationStep D_800FEBB0[] = {
    { 0x32010005 },
    { 0x33010006 },
    { 0x34010007 },
    { 0x35010008 },
    { 0x36000009 },
};

union AnimationStep D_800FEBC4[] = {
    { 0x16010001 },
    { 0x3C010001 },
    { 0x3DFE0001 },
};

union AnimationStep D_800FEBD0[] = {
    { 0x16010001 },
    { 0x3B010001 },
    { 0x15010001 },
    { 0x3B010001 },
    { 0x14010001 },
    { 0x3B010001 },
    { 0x13010001 },
    { 0x3B010001 },
    { 0x12010001 },
    { 0x3B010001 },
    { 0x11010001 },
    { 0x3B010001 },
    { 0x10010001 },
    { 0x3B010001 },
    { 0x0F010001 },
    { 0x3B010001 },
    { 0x0F010001 },
    { 0x3BEF0001 },
};

union AnimationStep D_800FEC18[] = {
    { 0x1D000001 },
};

union AnimationStep D_800FEC1C[] = {
    { 0x4A010001 },
    { 0x4B010001 },
    { 0x4A010001 },
    { 0x4B010001 },
    { 0x4A010001 },
    { 0x4C010001 },
    { 0x4A010001 },
    { 0x4C010001 },
    { 0x4D010001 },
    { 0x4C010001 },
    { 0x4D010001 },
    { 0x4C010001 },
    { 0x4E010001 },
    { 0x4C010001 },
    { 0x4E010001 },
    { 0x4F010001 },
    { 0x4E010001 },
    { 0x4F010001 },
    { 0x4E010001 },
    { 0x50010001 },
    { 0x4E010001 },
    { 0x50010001 },
    { 0x51010001 },
    { 0x50010001 },
    { 0x51010001 },
    { 0x50010001 },
    { 0x52010001 },
    { 0x50010001 },
    { 0x52010001 },
    { 0x53010001 },
    { 0x52010001 },
    { 0x53010001 },
    { 0x52010001 },
    { 0x54010001 },
    { 0x52010001 },
    { 0x54010001 },
    { 0x55010001 },
    { 0x54010001 },
    { 0x55010001 },
    { 0x54010001 },
    { 0x56010001 },
    { 0x54010001 },
    { 0x56010001 },
    { 0x57010001 },
    { 0x56010001 },
    { 0x57010001 },
    { 0x56010001 },
    { 0x58010001 },
    { 0x56010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x58010001 },
    { 0x59010001 },
    { 0x58010001 },
    { 0x5A010001 },
    { 0x58010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5A010001 },
    { 0x5B010001 },
    { 0x5A010001 },
    { 0x5C010001 },
    { 0x5A010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x5C010001 },
    { 0x5D010001 },
    { 0x5C010001 },
    { 0x5E010001 },
    { 0x5C010001 },
    { 0x5E010001 },
    { 0x5F010001 },
    { 0x5E010001 },
    { 0x5F010001 },
    { 0x5E010001 },
    { 0x60010001 },
    { 0x5E010001 },
    { 0x60010001 },
    { 0x61010001 },
    { 0x60010001 },
    { 0x61010001 },
    { 0x60010001 },
    { 0x3B010001 },
    { 0x60010001 },
    { 0x3B000001 },
};

union AnimationStep D_800FED70[] = {
    { 0x37010001 },
    { 0x38010001 },
    { 0x39010001 },
    { 0x3A010001 },
    { 0x39010001 },
    { 0x38010001 },
    { 0x37000001 },
};

union AnimationStep D_800FED8C[] = {
    { 0x3E010001 },
    { 0x3F010001 },
    { 0x40010001 },
    { 0x41010001 },
    { 0x40010001 },
    { 0x3F010001 },
    { 0x3E000001 },
};

union AnimationStep D_800FEDA8[] = {
    { 0x42010001 },
    { 0x43010001 },
    { 0x44010001 },
    { 0x45010001 },
    { 0x44010001 },
    { 0x43010001 },
    { 0x42000001 },
};

union AnimationStep D_800FEDC4[] = {
    { 0x46010001 },
    { 0x47010001 },
    { 0x48010001 },
    { 0x49010001 },
    { 0x48010001 },
    { 0x47010001 },
    { 0x46000001 },
};

union AnimationStep* D_800FEDE0[19] = {
    D_800FEAA4,
    D_800FEABC,
    D_800FEAD8,
    D_800FEB20,
    D_800FEB2C,
    D_800FEB4C,
    D_800FEB60,
    D_800FEB74,
    D_800FEB88,
    D_800FEB9C,
    D_800FEBB0,
    D_800FEBC4,
    D_800FEBD0,
    D_800FEC18,
    D_800FEC1C,
    D_800FEDA8,
    D_800FED70,
    D_800FEDC4,
    D_800FED8C,
};

struct Unk_unk68 D_800FEE2C = { 14, 15, 16, 17 };

struct Unk_unk68 D_800FEE30 = { 0, 0, 25, 23 };

struct Unk_unk68 D_800FEE34 = { -23, -24, 45, 49 };

void (*D_800FEE38[])(struct MainObj*) = {
    func_80062400,
    func_80062BBC,
    func_80062D20,
};

void (*D_800FEE44[8])() = {
    func_8009216C,
    func_80062D18,
    func_80062550,
    func_800625C4,
    func_800626F0,
    func_80062778,
    func_80062910,
    func_80062A0C,
};
