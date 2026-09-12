#include "common.h"
#include "func_tables.h"

void (*D_800F9988[13])(struct MainObj*) = {
    background_dragon_reset,
    background_dragon_wait_for_animation,
    background_dragon_fireball,
    background_dragon_projectile_attack,
    background_dragon_multi_shot,
    background_dragon_sequence,
    func_800419B8,
    background_dragon_fly_to_route_start,
    background_dragon_fly_offscreen,
    background_dragon_fly_to_staging_position,
    background_dragon_attach_to_background,
    background_dragon_noop,
    func_80040CCC,
};

u16 D_800F99BC[4] = { 0x6A0, 0x8A0, 0xAA0, 0 };
