// WeaponObj, weapon_object_update_funcs[59]
// 80098ABC..80098F4C
#include "common.h"

void ride_armor_shot_update(struct WeaponObj* arg0)
{
    ride_armor_shot_state_funcs[arg0->state](arg0);
}

// ride_armor_shot_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_59", func_80098AF8);

void ride_armor_shot_main(struct WeaponObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    if ((func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) && (arg0->unk98 == 0)) {
        update_on_screen(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }
    arg0->state = 2;
    arg0->on_screen = 0;
    arg0->unk50 = 0;
}

void ride_armor_shot_despawn(struct WeaponObj* arg0)
{
    struct PlayerObj* owner = arg0->owner;
    u8 timer = owner->air_action;
    if (timer != 0) {
        owner->air_action = timer - 1;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void enemy_ride_armor_shot_main(struct WeaponObj* arg0)
{
    struct WeaponObj* self = arg0;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);

    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(self);
        self->on_screen = 0;
    } else if (func_8002BB80(self, &g_Player) == 0 && func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
        return;
    } else {
        self->on_screen = 0;
    }

    ZeroObjectState(OBJECT_HEADER(self));
}

void enemy_ride_armor_shot_update(struct ShotObj* arg0)
{
    enemy_ride_armor_shot_state_funcs[arg0->state](arg0);
}

// ride_armor_missile_find_target
INCLUDE_ASM("main/nonmatchings/weapons/weapon_59", func_80098DA0);

// ride_armor_missile_spawn_smoke
INCLUDE_ASM("main/nonmatchings/weapons/weapon_59", func_80098EA8);

u8 ride_armor_shot_hit_box[4] = { 0xFC, 0xFD, 6, 5 };

s16 ride_armor_shot_offsets[2][2] = {
    { -0x2B, 0 },
    { -0x2C, 0x19 },
};

void (*ride_armor_shot_state_funcs[])(struct WeaponObj*) = {
    func_80098AF8,
    ride_armor_shot_main,
    ride_armor_shot_despawn,
};

void (*enemy_ride_armor_shot_state_funcs[])(struct WeaponObj*) = {
    func_80098AF8,
    enemy_ride_armor_shot_main,
    ride_armor_shot_despawn,
};
