// MainObj, main_object_update_funcs[63]
// 8007BFF4..8007C30C
#include "common.h"
#include "func_tables.h"

// hatch_turret_init
INCLUDE_ASM("main/nonmatchings/mains/main_63_hatch_turret", func_8007BFF4);

// hatch_turret_spawn_shot
INCLUDE_ASM("main/nonmatchings/mains/main_63_hatch_turret", func_8007C090);

// hatch_turret_main
INCLUDE_ASM("main/nonmatchings/mains/main_63_hatch_turret", func_8007C144);

void hatch_turret_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void hatch_turret_update(struct MainObj* self)
{
    hatch_turret_state_funcs[self->state](self);
}

union AnimationStep hatch_turret_anim_0[] = {
    { 0x00010007 },
    { 0x01010007 },
    { 0x02010007 },
    { 0x03010007 },
    { 0x03000001 },
};

union AnimationStep hatch_turret_anim_5[] = {
    { 0x03010007 },
    { 0x02010007 },
    { 0x01010007 },
    { 0x00010007 },
    { 0x00000001 },
};

union AnimationStep hatch_turret_anim_1[] = {
    { 0x04010001 },
    { 0x03010001 },
    { 0x05010001 },
    { 0x03010001 },
    { 0x06010001 },
    { 0x03010001 },
    { 0x07010001 },
    { 0x03010001 },
    { 0x08010001 },
    { 0x03010001 },
    { 0x09010001 },
    { 0x03010001 },
    { 0x0A010001 },
    { 0x03010001 },
    { 0x0B010001 },
    { 0x03010001 },
    { 0x0C010001 },
    { 0x03010001 },
    { 0x0D010001 },
    { 0x03010001 },
    { 0x0E010001 },
    { 0x03010001 },
    { 0x0F010001 },
    { 0x03010001 },
    { 0x10010001 },
    { 0x03010001 },
    { 0x11010001 },
    { 0x03010001 },
    { 0x12010001 },
    { 0x03010001 },
    { 0x13010001 },
    { 0x03010001 },
    { 0x14010001 },
    { 0x03010001 },
    { 0x15010001 },
    { 0x03010001 },
    { 0x16010001 },
    { 0x03010001 },
    { 0x17010001 },
    { 0x03010001 },
    { 0x18010001 },
    { 0x03010001 },
    { 0x19010001 },
    { 0x03010001 },
    { 0x1A010001 },
    { 0x03010001 },
    { 0x1B010001 },
    { 0x03000001 },
};

union AnimationStep hatch_turret_anim_2[] = {
    { 0x1C010001 },
    { 0x24010001 },
    { 0x1C010001 },
    { 0x24010001 },
    { 0x1D010001 },
    { 0x24010001 },
    { 0x1D010001 },
    { 0x24010001 },
    { 0x1D010001 },
    { 0x24010001 },
    { 0x1E010001 },
    { 0x24010001 },
    { 0x1E010001 },
    { 0x24010001 },
    { 0x1E010001 },
    { 0x24010001 },
    { 0x1E010001 },
    { 0x24010001 },
    { 0x1F010001 },
    { 0x24010001 },
    { 0x1F010001 },
    { 0x24010001 },
    { 0x1F010001 },
    { 0x24000001 },
};

union AnimationStep hatch_turret_anim_3[] = {
    { 0x1F010001 },
    { 0x24010001 },
    { 0x1F010001 },
    { 0x24010001 },
    { 0x1F010001 },
    { 0x24010001 },
    { 0x1E010001 },
    { 0x24010001 },
    { 0x1E010001 },
    { 0x24010001 },
    { 0x1E010001 },
    { 0x24010001 },
    { 0x1E010001 },
    { 0x24010001 },
    { 0x1D010001 },
    { 0x24010001 },
    { 0x1D010001 },
    { 0x24010001 },
    { 0x1D010001 },
    { 0x24010001 },
    { 0x1C010001 },
    { 0x24010001 },
    { 0x1C010001 },
    { 0x24000001 },
};

struct Unk_unk68 hatch_turret_anim_4[8] = {
    { 1, 0, 1, 32 },
    { 1, 0, 1, 36 },
    { 1, 0, 1, 33 },
    { 1, 0, 1, 36 },
    { 1, 0, 1, 34 },
    { 1, 0, 1, 36 },
    { 1, 0, 1, 35 },
    { 1, 0, -7, 36 },
};

union AnimationStep hatch_turret_anim_6[] = {
    { 0x25000001 },
};

union AnimationStep hatch_turret_anim_7[] = {
    { 0x26000001 },
};

union AnimationStep hatch_turret_anim_8[] = {
    { 0x27000001 },
};

union AnimationStep hatch_turret_anim_9[] = {
    { 0x28000001 },
};

union AnimationStep hatch_turret_anim_10[] = {
    { 0x29000001 },
};

union AnimationStep hatch_turret_anim_11[] = {
    { 0x2A000001 },
};

union AnimationStep hatch_turret_anim_12[] = {
    { 0x2B000001 },
};

void* hatch_turret_animations[13] = {
    hatch_turret_anim_0,
    hatch_turret_anim_1,
    hatch_turret_anim_2,
    hatch_turret_anim_3,
    hatch_turret_anim_4,
    hatch_turret_anim_5,
    hatch_turret_anim_6,
    hatch_turret_anim_7,
    hatch_turret_anim_8,
    hatch_turret_anim_9,
    hatch_turret_anim_10,
    hatch_turret_anim_11,
    hatch_turret_anim_12,
};

void (*hatch_turret_state_funcs[3])() = {
    func_8007BFF4,
    func_8007C144,
    hatch_turret_despawn,
};
