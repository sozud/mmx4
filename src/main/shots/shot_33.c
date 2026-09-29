// ShotObj, shot_object_update_funcs[33]
// 800A03B8..800A16FC
#include "common.h"

void falling_rock_update(struct ShotObj* self)
{
    falling_rock_state_funcs[self->state](self);
}

// falling_rock_a_init
INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A03F4);

// falling_rock_a_fall
INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A068C);

void falling_rock_a_despawn(struct ShotObj* self)
{
    self->unk62 = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

// falling_rock_b_init
INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A0A38);

// falling_rock_b_fall
INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A0C4C);

void falling_rock_b_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

// falling_rock_c_init
INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A0FE8);

// falling_rock_c_fall
INCLUDE_ASM("main/nonmatchings/shots/shot_33", func_800A12EC);

void falling_rock_c_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

struct Unk_unk68 falling_rock_box_0[] = {
    { -20, -23, 0x23, 0x22 },
};

struct Unk_unk68 falling_rock_box_1[] = {
    { -17, -20, 0x23, 0x26 },
};

struct Unk_unk68 falling_rock_box_2[] = {
    { -17, -18, 0x23, 0x26 },
};

struct Unk_unk68 falling_rock_box_3[] = {
    { -3, -6, 0x12, 0x12 },
};

struct Unk_unk68 falling_rock_box_4[] = {
    { 0, -1, 0x14, 0x13 },
};

struct Unk_unk68 falling_rock_box_5[] = {
    { 0, -1, 0x14, 0x13 },
};

u8 falling_rock_debris_0[] = {
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_1[] = {
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_2[] = {
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_3[] = {
    0x08,
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_4[] = {
    0x04,
    0x05,
    0x06,
    0x07,
    0x08,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_5[] = {
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_6[] = {
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x00,
};

union AnimationStep D_801092B8[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03FD0102 },
};

union AnimationStep D_801092C8[] = {
    { 0x04010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0AFA0102 },
};

union AnimationStep D_801092E4[] = {
    { 0x0B010002 },
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0D000101 },
};

union AnimationStep D_801092F4[] = {
    { 0x0E000101 },
};

union AnimationStep D_801092F8[] = {
    { 0x0F000101 },
};

union AnimationStep D_801092FC[] = {
    { 0x10000101 },
};

union AnimationStep D_80109300[] = {
    { 0x11000101 },
};

union AnimationStep D_80109304[] = {
    { 0x12000101 },
};

union AnimationStep D_80109308[] = {
    { 0x13000101 },
};

union AnimationStep D_8010930C[] = {
    { 0x14000101 },
};

union AnimationStep D_80109310[] = {
    { 0x15000101 },
};

union AnimationStep D_80109314[] = {
    { 0x16000101 },
};

union AnimationStep D_80109318[] = {
    { 0x17000101 },
};

union AnimationStep D_8010931C[] = {
    { 0x18000101 },
};

union AnimationStep* falling_rock_a_animations[] = {
    D_801092B8,
    D_801092C8,
    D_801092E4,
    D_801092F4,
    D_801092F8,
    D_801092FC,
    D_80109300,
    D_80109304,
    D_80109308,
    D_8010930C,
    D_80109310,
    D_80109314,
    D_80109318,
    D_8010931C,
};

union AnimationStep D_80109358[] = {
    { 0x00010005 },
    { 0x01010005 },
    { 0x02010005 },
    { 0x03010005 },
    { 0x04FC0105 },
};

union AnimationStep D_8010936C[] = {
    { 0x05010004 },
    { 0x06010004 },
    { 0x07010004 },
    { 0x08010004 },
    { 0x09010004 },
    { 0x0A010004 },
    { 0x0B010004 },
    { 0x0CF90104 },
};

union AnimationStep D_8010938C[] = {
    { 0x0D000101 },
};

union AnimationStep D_80109390[] = {
    { 0x0E000101 },
};

union AnimationStep D_80109394[] = {
    { 0x0F000101 },
};

union AnimationStep D_80109398[] = {
    { 0x10000101 },
};

union AnimationStep D_8010939C[] = {
    { 0x11000101 },
};

union AnimationStep D_801093A0[] = {
    { 0x12000101 },
};

union AnimationStep D_801093A4[] = {
    { 0x13000101 },
};

union AnimationStep D_801093A8[] = {
    { 0x14000101 },
};

union AnimationStep D_801093AC[] = {
    { 0x15000101 },
};

union AnimationStep D_801093B0[] = {
    { 0x16000101 },
};

union AnimationStep D_801093B4[] = {
    { 0x17000101 },
};

union AnimationStep* falling_rock_b_animations[] = {
    D_80109358,
    D_8010936C,
    D_8010938C,
    D_80109390,
    D_80109394,
    D_80109398,
    D_8010939C,
    D_801093A0,
    D_801093A4,
    D_801093A8,
    D_801093AC,
    D_801093B0,
    D_801093B4,
};

union AnimationStep D_801093EC[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03FD0102 },
};

union AnimationStep D_801093FC[] = {
    { 0x04010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0BF90102 },
};

union AnimationStep D_8010941C[] = {
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0FFD0102 },
};

union AnimationStep D_8010942C[] = {
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17F90102 },
};

union AnimationStep D_8010944C[] = {
    { 0x18000101 },
};

union AnimationStep D_80109450[] = {
    { 0x19000101 },
};

union AnimationStep D_80109454[] = {
    { 0x1A000101 },
};

union AnimationStep D_80109458[] = {
    { 0x1B000101 },
};

union AnimationStep D_8010945C[] = {
    { 0x1C000101 },
};

union AnimationStep D_80109460[] = {
    { 0x1D000101 },
};

union AnimationStep D_80109464[] = {
    { 0x1E000101 },
};

union AnimationStep D_80109468[] = {
    { 0x1F000101 },
};

union AnimationStep D_8010946C[] = {
    { 0x20000101 },
};

union AnimationStep D_80109470[] = {
    { 0x21000101 },
};

union AnimationStep D_80109474[] = {
    { 0x22000101 },
};

union AnimationStep* falling_rock_c_animations[] = {
    D_801093EC,
    D_801093FC,
    D_8010941C,
    D_8010942C,
    D_8010944C,
    D_80109450,
    D_80109454,
    D_80109458,
    D_8010945C,
    D_80109460,
    D_80109464,
    D_80109468,
    D_8010946C,
    D_80109470,
    D_80109474,
};

union AnimationStep D_801094B4[] = {
    { 0x00000101 },
};

union AnimationStep D_801094B8[] = {
    { 0x01000101 },
};

union AnimationStep D_801094BC[] = {
    { 0x02000101 },
};

union AnimationStep D_801094C0[] = {
    { 0x03000101 },
};

union AnimationStep D_801094C4[] = {
    { 0x04000101 },
};

union AnimationStep D_801094C8[] = {
    { 0x05000101 },
};

union AnimationStep D_801094CC[] = {
    { 0x06000101 },
};

union AnimationStep* falling_rock_d_animations[] = {
    D_801094B4,
    D_801094B8,
    D_801094BC,
    D_801094C0,
    D_801094C4,
    D_801094C8,
    D_801094CC,
};

void (*falling_rock_state_funcs[])(struct ShotObj*) = {
    func_800A03F4,
    func_800A068C,
    falling_rock_a_despawn,
    func_800A0A38,
    func_800A0C4C,
    falling_rock_b_despawn,
    func_800A0FE8,
    func_800A12EC,
    falling_rock_c_despawn,
};
