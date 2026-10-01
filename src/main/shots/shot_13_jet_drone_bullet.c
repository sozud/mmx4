// ShotObj, shot_object_update_funcs[13]
// 8009BD28..8009BF14
#include "common.h"

u8 jet_drone_bullet_hit_box[4] = { 0xFD, 0xFE, 0x05, 0x04 };

void jet_drone_bullet_update(struct ShotObj* self)
{
    jet_drone_bullet_state_funcs[self->state](self);
}

void jet_drone_bullet_init(struct ShotObj* arg0)
{
    struct ShotObj* self = arg0;

    self->state = 1;
    self->on_screen = 1;
    self->unk58.collision_data = D_80106070;
    self->unk42 &= 0x7FFF;
    set_velocity_from_angle(
        MOVING_OBJECT(self),
        angle_to_object(
            OBJECT_HEADER(self),
            OBJECT_HEADER(&g_Player))
            & 0xFF);
    self->unk54 = jet_drone_bullet_hit_box;
    self->unk50.data = jet_drone_bullet_hit_box;
    self->unk16 = 0;
    self->unk68 = 0;
    self->unk5C = 1;
    self->unk60 = 3;
    self->x_vel.val *= 2;
    self->y_vel.val *= 2;
    set_animation(self, 3);
}

void jet_drone_bullet_fly(struct ShotObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if ((engine_obj.stage != 0x3 || engine_obj.substage != 0) || engine_obj.checkpoint != 0 || g_Player.x_pos.i.hi <= 0x7B6) {
        func_8002D9BC(self);
    }
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(self);
        self->state = 2;
    } else {
        self->unk42 &= 0x7FFF;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
        return;
    }
    self->state = 2;
}

void jet_drone_bullet_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*jet_drone_bullet_state_funcs[])(struct ShotObj*) = {
    jet_drone_bullet_init,
    jet_drone_bullet_fly,
    jet_drone_bullet_despawn,
};
