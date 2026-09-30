// VisualObj, visual_object_update_funcs[29]
// 800B41CC..800B4610
#include "common.h"

void peacock_target_update(struct VisualObj* arg0)
{
    peacock_target_state_funcs[arg0->state](arg0);
}

void peacock_target_init(struct VisualObj* arg0)
{
    arg0->state = 1;
    arg0->unk5 = 0;
    arg0->on_screen = 1;
    arg0->unk16 = 2;
    arg0->unk54 = 0x3C;
    arg0->unk56 = 4;
    arg0->unk2C = 0;
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->x_vel.val = 0;
    set_animation(arg0, 0xA);
    is_on_screen(BASE_OBJECT(arg0));
}

void peacock_target_track(struct VisualObj* arg0)
{
    u16 x_distance;
    u16 y_distance;

    if (--arg0->unk54 != 0) {
        if (--arg0->unk56 == 0) {
            arg0->unk56 = 1;
            x_distance = ABS(arg0->x_pos.i.hi, g_Player.x_pos.i.hi);
            y_distance = ABS(arg0->y_pos.i.hi, g_Player.y_pos.i.hi);
            set_velocity_from_angle(MOVING_OBJECT(arg0), (u8)angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player)));
            // pursuit/homing missile?
            if (x_distance > 16 || y_distance > 16) {
                arg0->x_vel.val *= 4;
                arg0->y_vel.val *= 4;
            } else if (x_distance > 8 || y_distance > 8) {
                arg0->x_vel.val *= 3;
                arg0->y_vel.val *= 3;
            } else if (x_distance > 4 || y_distance > 4) {
                arg0->x_vel.val *= 2;
                arg0->y_vel.val *= 2;
            } else if (x_distance > 2 || y_distance > 2) {
                arg0->x_vel.val *= 1;
                arg0->y_vel.val *= 1;
            } else {
                arg0->x_pos.val = g_Player.x_pos.val;
                arg0->y_pos.val = g_Player.y_pos.val;
            }
        }
        move_with_gravity(ANIMATED_OBJECT(arg0));
        animate_object(ANIMATED_OBJECT(arg0));
    } else {
        arg0->unk5++;
        set_animation(arg0, 0xB);
    }
}

void peacock_target_lock(struct VisualObj* arg0)
{
    arg0->unk5++;
    arg0->unk50->input.buttons.held = 0;
    animate_object(arg0);
}

void peacock_target_fire(struct VisualObj* arg0)
{
    struct ShotObj* shot;

    if ((s16)arg0->unk50->input.buttons.previous != 0) {
        arg0->unk5++;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = (u8)arg0->active;
            shot->id = 0x2A;
            shot->unk2 = (u8)arg0->unk2;
            shot->x_pos.val = arg0->x_pos.val;
            shot->y_pos.val = arg0->y_pos.val;
            shot->animation_table = arg0->animation_table;
            shot->unk40 = arg0->unk40;
            shot->unk3C = arg0->unk3C;
            shot->unk42 = arg0->unk42 & 0x7FFF;
            shot->unk16 = arg0->unk16;
            shot->unk15 = 0;
            shot->unk7C = WEAPON_OBJECT(arg0);
        }
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void peacock_target_hold(struct VisualObj* arg0)
{
    animate_object(arg0);
}

void peacock_target_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void peacock_target_main(struct VisualObj* arg0)
{
    if (arg0->unk50->state != 1) {
        ZeroObjectState(arg0);
    } else {
        peacock_target_step_funcs[arg0->unk5](arg0);
        is_on_screen(arg0);
    }
}

void (*peacock_target_state_funcs[])(struct VisualObj*) = {
    peacock_target_init,
    peacock_target_main,
    peacock_target_despawn,
};

void (*peacock_target_step_funcs[])(struct VisualObj*) = {
    peacock_target_track,
    peacock_target_lock,
    peacock_target_fire,
    peacock_target_hold,
};
