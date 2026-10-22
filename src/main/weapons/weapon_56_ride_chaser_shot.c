// WeaponObj, weapon_object_update_funcs[56]
// 800985F4..80098838
#include "common.h"
#include "main/weapons/weapon_56_ride_chaser_shot.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

// ride_chaser_shot_state_funcs
extern void (*ride_chaser_shot_state_funcs[])(struct WeaponObj*);

void ride_chaser_shot_main(struct WeaponObj*);
void ride_chaser_shot_despawn(struct WeaponObj*);

extern struct Unk_unk68 ride_chaser_shot_hit_box[];
extern u16 ride_chaser_shot_offsets[5][2];
extern u8 ride_chaser_shot_angles[];
extern u8 ride_chaser_shot_animations[];

#include "weapon_resources.h"

void ride_chaser_shot_update(struct WeaponObj* arg0)
{
    ride_chaser_shot_state_funcs[arg0->state](arg0);
}

// ride_chaser_shot_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80098630(struct WeaponObj* arg0);
extern struct Unk_unk68 ride_chaser_shot_hit_box[];
extern u8 ride_chaser_shot_angles[];
extern u8 ride_chaser_shot_animations[];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80098630(struct WeaponObj* arg0)
{
    s32 dx;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk50 = (u8*)ride_chaser_shot_hit_box;
    dx = ride_chaser_shot_offsets[arg0->unk2][0];
    if (arg0->unk15 != 0)
        dx = -dx;
    arg0->x_pos.i.hi += dx;
    arg0->y_pos.i.hi += ride_chaser_shot_offsets[arg0->unk2][1];
    set_velocity_from_angle(MOVING_OBJECT(arg0), ride_chaser_shot_angles[arg0->unk2]);
    arg0->unk60 = 3;
    arg0->x_vel.val *= 8;
    arg0->unk5C = 1;
    arg0->y_vel.val *= 8;
    set_animation(arg0, ride_chaser_shot_animations[arg0->unk2]);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_56_ride_chaser_shot", func_80098630);
#endif

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

u16 ride_chaser_shot_offsets[5][2] = {
    { 0xFFCC, 0x0001 },
    { 0xFFD1, 0x0017 },
    { 0xFFD0, 0x000F },
    { 0xFFD6, 0xFFEA },
    { 0xFFCC, 0x0001 },
};

void (*ride_chaser_shot_state_funcs[])(struct WeaponObj*) = {
    func_80098630,
    ride_chaser_shot_main,
    ride_chaser_shot_despawn,
};

u8 ride_chaser_shot_angles[8] = { 2, 0x1E, 0, 4, 0, 0, 0, 0 };

u8 ride_chaser_shot_animations[8] = { 0x0F, 0x0E, 0x0D, 0x10, 0x0D, 0, 0, 0 };
