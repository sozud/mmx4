// WeaponObj, weapon_object_update_funcs[60]
// 80098F4C..800992FC
#include "common.h"

void ride_armor_missile_update(struct WeaponObj* arg0)
{
    ride_armor_missile_state_funcs[arg0->state](arg0);
}

// ride_armor_missile_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_60", func_80098F88);

// ride_armor_missile_main
INCLUDE_ASM("main/nonmatchings/weapons/weapon_60", func_80099118);

void ride_armor_missile_despawn(struct WeaponObj* arg0)
{
    struct PlayerObj* temp_a2;

    temp_a2 = arg0->owner;
    temp_a2->input.bytes.previous_high ^= 1 << arg0->unk2;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 ride_armor_missile_hit_box[4] = { 0xFC, 0xFD, 6, 5 };

struct Weapon60SpawnOffset ride_armor_missile_offsets[3] = {
    { -0x28, 0 },
    { -0x28, 0 },
    { -0x28, 0 },
};

void (*ride_armor_missile_state_funcs[])(struct WeaponObj*) = {
    func_80098F88,
    func_80099118,
    ride_armor_missile_despawn,
};
