// MainObj, main_object_update_funcs[11]
// 8004A718..8004B8C0
#include "common.h"
#include "func_tables.h"

void func_8004A718(struct MainObj* arg0)
{
    D_800FB51C[arg0->state](arg0);
    if ((arg0->unk2 == 0) || (engine_obj.character_state.fields.active == 1)) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004A78C);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004A9F4);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AB6C);

void func_8004ACDC(struct MainObj* arg0)
{
    arg0->state++;
}

void func_8004ACF0(struct MainObj* arg0)
{
    arg0->state = 0;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AD18);

void func_8004ADE8(struct MainObj* arg0)
{
    arg0->unk5 = SP_CUR_MAIN_OBJ->ext.main_11.saved_unk5;
}

void func_8004AE00(struct MainObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004AE20);

void func_8004B040(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk15 ^= 0x40;
        func_80015D60(arg0, 0);
        if (arg0->unk2 == 0) {
            arg0->unk5 = 2;
        } else {
            arg0->unk5 = 4;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B0A0);

void func_8004B280(struct MainObj* arg0)
{
    D_800FB550[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B2BC);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B418);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B514);

INCLUDE_ASM("main/nonmatchings/mains/main_11", func_8004B668);

void func_8004B748(struct MainObj* self)
{
    u8 flags;

    if (self->unk2 == 0) {
        flags = SP_CUR_MAIN_OBJ->ext.main_11.unk80;
        if (flags & 3) {
            if (flags & 2) {
                self->unk15 = 0x40;
            } else {
                self->unk15 = 0;
            }
            func_80015D60(self, 0);
        } else {
            func_80015D60(self, 1);
        }
        self->unk5 = 2;
    } else {
        func_80015D60(self, 1);
        SP_CUR_MAIN_OBJ->ext.main_11.unk80 = 4;
        self->unk24 = FIXED(3);
        self->unk20 = 0;
        self->unk5 = 6;
    }
    self->unk6 = 0;
}

void func_8004B808(struct MainObj* arg0)
{
    struct MainObj* current;
    u8 flags;

    current = SP_CUR_MAIN_OBJ;
    if (current->ext.main_11.unk80 & 3) {
        flags = arg0->unk70;
        if (flags & 4) {
            if (flags & 8) {
                if (flags & 2) {
                    if (!(flags & 1)) {
                        current->ext.main_11.unk80 = 2;
                    }
                } else {
                    current->ext.main_11.unk80 = 1;
                }
            } else {
                current->ext.main_11.unk80 = 8;
            }
        } else {
            current->ext.main_11.unk80 = 4;
        }
    } else {
        flags = arg0->unk70;
        if (flags & 2) {
            if (flags & 1) {
                if (flags & 4) {
                    if (!(flags & 8)) {
                        current->ext.main_11.unk80 = 8;
                    }
                } else {
                    current->ext.main_11.unk80 = 4;
                }
            } else {
                current->ext.main_11.unk80 = 2;
            }
        } else {
            current->ext.main_11.unk80 = 1;
        }
    }
}

union AnimationStep D_800FB144[] = {
    { 0x00010001 },
    { 0x01010002 },
    { 0x2F010003 },
    { 0x01010002 },
    { 0x00010001 },
    { 0x30010002 },
    { 0x31010003 },
    { 0x30010002 },
    { 0x00F80001 },
};

union AnimationStep D_800FB168[] = {
    { 0x02010001 },
    { 0x03FF0001 },
};

union AnimationStep D_800FB170[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x06010001 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x08010001 },
    { 0x09010101 },
    { 0x02000001 },
};

union AnimationStep D_800FB1F4[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x0A010101 },
    { 0x0BFF0101 },
};

union AnimationStep D_800FB23C[] = {
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x03010101 },
    { 0x02FF0101 },
};

union AnimationStep D_800FB284[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0E010101 },
    { 0x0FFF0101 },
};

union AnimationStep D_800FB2CC[] = {
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x03010101 },
    { 0x02FF0101 },
};

union AnimationStep D_800FB314[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x04010101 },
    { 0x05FF0101 },
};

union AnimationStep D_800FB33C[] = {
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x03010101 },
    { 0x02FF0101 },
};

union AnimationStep D_800FB364[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x0C010101 },
    { 0x0DFF0101 },
};

union AnimationStep D_800FB38C[] = {
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x03010101 },
    { 0x02FF0101 },
};

union AnimationStep D_800FB3B4[] = {
    { 0x10010001 },
    { 0x11010001 },
    { 0x12010001 },
    { 0x13FD0001 },
};

union AnimationStep D_800FB3C4[] = {
    { 0x1F000001 },
};

union AnimationStep D_800FB3C8[] = {
    { 0x20000001 },
};

union AnimationStep D_800FB3CC[] = {
    { 0x21000001 },
};

union AnimationStep D_800FB3D0[] = {
    { 0x22000001 },
};

union AnimationStep D_800FB3D4[] = {
    { 0x23000001 },
};

union AnimationStep D_800FB3D8[] = {
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x02010001 },
    { 0x03010001 },
    { 0x24010201 },
    { 0x25010001 },
    { 0x02010101 },
    { 0x03FF0101 },
};

union AnimationStep D_800FB400[] = {
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x26010201 },
    { 0x27010001 },
    { 0x04010101 },
    { 0x05FF0101 },
};

union AnimationStep D_800FB428[] = {
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x0A010001 },
    { 0x0B010001 },
    { 0x28010201 },
    { 0x29010001 },
    { 0x0A010101 },
    { 0x0BFF0101 },
};

union AnimationStep D_800FB450[] = {
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x0C010001 },
    { 0x0D010001 },
    { 0x2A010201 },
    { 0x2B010001 },
    { 0x0C010101 },
    { 0x0DFF0101 },
};

union AnimationStep D_800FB478[] = {
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x0E010001 },
    { 0x0F010001 },
    { 0x2C010201 },
    { 0x2D010001 },
    { 0x0E010101 },
    { 0x0FFF0101 },
};

union AnimationStep D_800FB4A0[] = {
    { 0x2E000001 },
};

union AnimationStep D_800FB4A4[] = {
    { 0x34000001 },
};

union AnimationStep D_800FB4A8[] = {
    { 0x32010001 },
    { 0x33000001 },
};

union AnimationStep* D_800FB4B0[] = {
    D_800FB144,
    D_800FB168,
    D_800FB170,
    D_800FB1F4,
    D_800FB23C,
    D_800FB284,
    D_800FB2CC,
    D_800FB314,
    D_800FB33C,
    D_800FB364,
    D_800FB38C,
    D_800FB3B4,
    D_800FB3C4,
    D_800FB3C8,
    D_800FB3CC,
    D_800FB3D0,
    D_800FB3D4,
    D_800FB3D8,
    D_800FB400,
    D_800FB428,
    D_800FB450,
    D_800FB478,
    D_800FB4A0,
    D_800FB4A4,
    D_800FB4A8,
};

u8 D_800FB514[] = {
    0x0C,
    0x0D,
    0x0E,
    0x0F,
    0x10,
    0x00,
    0x00,
    0x00,
};

void (*D_800FB51C[])(struct MainObj*) = {
    func_8004A78C,
    func_8004A9F4,
    func_8004AB6C,
    func_8004ACDC,
    func_8004ACF0,
};

void (*D_800FB530[])() = {
    func_8009216C,
    func_8004ADE8,
    func_8004AE20,
    func_8004B040,
    func_8004B0A0,
    func_8004B280,
    func_8004AE00,
    func_8004AD18,
};

void (*D_800FB550[])() = {
    func_8004B2BC,
    func_8004B418,
    func_8004B514,
    func_8004B668,
    func_8004B748,
};

struct Unk_unk68 D_800FB564 = { -9, -9, 23, 18 };

struct Unk_unk68 D_800FB568 = { 0, 7, 13, 24 };

struct Unk_unk68 D_800FB56C = { 0, 0, 11, 11 };
