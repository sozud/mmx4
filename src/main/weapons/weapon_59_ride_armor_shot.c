// WeaponObj, weapon_object_update_funcs[59]
// 80098ABC..80098F4C
#include "common.h"
#include "main/objects.h"
#include "main/weapons/weapon_59_ride_armor_shot.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"

// ride_armor_shot_state_funcs
extern void (*ride_armor_shot_state_funcs[])(struct WeaponObj*);

void ride_armor_shot_main(struct WeaponObj*);
void ride_armor_shot_despawn(struct WeaponObj*);

// enemy_ride_armor_shot_state_funcs
extern void (*enemy_ride_armor_shot_state_funcs[])(struct WeaponObj*);

void enemy_ride_armor_shot_main(struct WeaponObj*);
void ride_armor_shot_despawn(struct WeaponObj*);

extern u8 ride_armor_shot_hit_box[4];
extern s16 ride_armor_shot_offsets[2][2];

#include "weapon_resources.h"

void ride_armor_shot_update(struct WeaponObj* arg0)
{
    ride_armor_shot_state_funcs[arg0->state](arg0);
}

// ride_armor_shot_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80098AF8(struct WeaponObj* arg0);
static s32 weapon_59_distance(s32 x0, s32 y0, s32 x1, s32 y1);
void func_80098DA0(struct WeaponObj* arg0);
extern u8 ride_armor_shot_hit_box[4];
extern s16 ride_armor_shot_offsets[2][2];
static s32 weapon_59_distance(s32 x0, s32 y0, s32 x1, s32 y1)
{
    s32 dx = x0 - x1;
    s32 dy = y0 - y1;

    if (dx < 0)
        dx = x1 - x0;
    if (dy < 0)
        dy = y1 - y0;
    return dx + dy;
}
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80098AF8(struct WeaponObj* arg0)
{
    s32 dx;
    s32 direction;

    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 3;
    arg0->unk68 = NULL;
    arg0->unk54 = NULL;
    arg0->unk50 = ride_armor_shot_hit_box;
    dx = (u16)ride_armor_shot_offsets[arg0->unk2][0];
    if (arg0->unk15 != 0)
        dx = -dx;
    arg0->x_pos.i.hi += dx;
    arg0->y_pos.i.hi += ride_armor_shot_offsets[arg0->unk2][1];
    if (arg0->unk2 == 0)
        direction = arg0->unk15 == 0 ? 0x10 : 0;
    else
        direction = arg0->unk15 != 0 ? 0x1C : 0x14;
    set_velocity_from_angle(MOVING_OBJECT(arg0), direction);
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->x_vel.val *= 8;
    arg0->y_vel.val *= 8;
    set_animation(arg0, arg0->unk2 + 0x1F);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_59_ride_armor_shot", func_80098AF8);
#endif

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
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/weapons/weapon_59_ride_armor_shot", func_80098DA0);
#else
void func_80098DA0(struct WeaponObj* arg0)
{
    struct MainObj* main;
    struct MainObj* target;
    s32 found = 0;
    s32 dx;
    s32 dy;
    s32 tx;
    s32 ty;

    for (main = main_objects; main < main_objects + COUNT(main_objects); main++) {
        if (main->active == 0 || main->on_screen == 0 || main->unk7A != 0)
            continue;
        target = arg0->ext.target;
        if (target != NULL) {
            dx = ABS(arg0->x_pos.val, main->x_pos.val);
            dy = ABS(arg0->y_pos.val, main->y_pos.val);
            tx = ABS(arg0->x_pos.val, target->x_pos.val);
            ty = ABS(arg0->y_pos.val, target->y_pos.val);
            dx += dy;
            tx += ty;
            if (dx < tx) {
                arg0->ext.target = main;
            }
        } else {
            arg0->ext.target = main;
        }
        found = 1;
    }
    if (!found)
        arg0->ext.target = NULL;
}
#endif

// ride_armor_missile_spawn_smoke
void func_80098EA8(struct WeaponObj* shot)
{
    struct VisualObj* visual;

    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = shot->active;
        visual->id = 0x16;
        visual->unk2 = 0;
        visual->x_pos.u.hi = shot->x_pos.u.hi;
        visual->y_pos.u.hi = shot->y_pos.u.hi;
        visual->animation_table = shot->animation_table;
        visual->unk40 = shot->unk40;
        visual->unk3C = shot->unk3C;
        visual->unk42 = shot->unk42;
        visual->unk16 = shot->unk16;
        visual->unk50 = PLAYER_OBJECT(shot);
        visual->unk15 = shot->unk15;
    }
}

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
