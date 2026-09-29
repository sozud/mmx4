// WeaponObj, weapon_object_update_funcs[56]
// 800985F4..80098838
#include "common.h"

void ride_chaser_shot_update(struct WeaponObj* arg0)
{
    ride_chaser_shot_state_funcs[arg0->state](arg0);
}

// ride_chaser_shot_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_56", func_80098630);

void ride_chaser_shot_main(struct WeaponObj* arg0)
{
    ride_chaser_shot_follow_scroll(arg0);
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0 && arg0->unk98 == 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }
    arg0->state = 2;
    arg0->on_screen = 0;
}

void ride_chaser_shot_despawn(struct WeaponObj* arg0)
{
    struct PlayerObj* temp_v1;

    temp_v1 = arg0->owner;
    temp_v1->shot_count--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void ride_chaser_shot_follow_scroll(struct WeaponObj* arg0)
{
    if (background_objects[0].unk4 == 1) {
        arg0->x_pos.u.hi += background_objects[0].x_pos.u.hi - background_objects[0].unk14.u.hi;
        arg0->y_pos.u.hi += background_objects[0].y_pos.u.hi - background_objects[0].unk18.u.hi;
    }
}

struct Unk_unk68 ride_chaser_shot_hit_box[] = {
    { -9, -11, 0x1A, 0x14 },
};

u16 ride_chaser_shot_offsets[] = {
    0xFFCC,
    0x0001,
    0xFFD1,
    0x0017,
    0xFFD0,
    0x000F,
    0xFFD6,
    0xFFEA,
    0xFFCC,
    0x0001,
};

void (*ride_chaser_shot_state_funcs[])(struct WeaponObj*) = {
    func_80098630,
    ride_chaser_shot_main,
    ride_chaser_shot_despawn,
};
