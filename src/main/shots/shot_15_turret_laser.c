// ShotObj, shot_object_update_funcs[15]
// 8009C0F0..8009C364
#include "common.h"

u8 turret_laser_hit_box[4] = { 0xFD, 0xFD, 0x06, 0x06 };

void turret_laser_update(struct ShotObj* self)
{
    turret_laser_state_funcs[self->state](self);
}

// turret_laser_init
void func_8009C12C(struct ShotObj* self)
{
    struct MainObj* owner = MAIN_OBJECT(self->unk7C);

    self->unk40 = owner->unk40;
    self->unk42 = owner->unk42 & 0x7FFF;
    self->animation_table = ANIMATED_OBJECT(owner)->animation_table;
    self->unk3C = ANIMATED_OBJECT(owner)->unk3C;
    self->unk15 = owner->unk15;
    self->bg_offset = owner->bg_offset;
    self->x_pos.val = owner->x_pos.val;
    self->y_pos.val = owner->y_pos.val;
    self->state++;
    self->unk5 = 2;
    set_velocity_from_angle(MOVING_OBJECT(self), angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);
    self->unk58.data = (const u8*)D_80106070;
    self->unk54 = turret_laser_hit_box;
    self->unk50.data = turret_laser_hit_box;
    self->unk5C = 1;
    self->unk60 = 3;
    self->unk16 = 0;
    self->unk68 = NULL;
    self->x_vel.val *= 2;
    self->y_vel.val *= 2;
    set_animation(self, 4);
}

void turret_laser_hit(struct ShotObj* self)
{
    enemy_hit_reaction(self);
}

void turret_laser_idle(struct ShotObj* arg)
{
}

void turret_laser_move(struct ShotObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
}

void turret_laser_main(struct ShotObj* self)
{
    s32 hit;

    hit = func_8002DD04(MAIN_OBJECT(self));
    if (hit < 0) {
        self->unk5 = 0;
        self->state++;
        spawn_explosion(BASE_OBJECT(self));
        return;
    }

    turret_laser_step_funcs[self->unk5](self);
    if (func_8002B1E8(BASE_OBJECT(self), 0xA, 0xA) == 0) {
        update_on_screen(BASE_OBJECT(self), 0xA, 0xA);
        return;
    }

    self->state++;
}

void turret_laser_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*turret_laser_state_funcs[])(struct ShotObj*) = {
    func_8009C12C,
    turret_laser_main,
    turret_laser_despawn,
};

void (*turret_laser_step_funcs[3])(struct ShotObj*) = {
    turret_laser_hit,
    turret_laser_idle,
    turret_laser_move,
};

extern u8 turret_laser_beam_box_data[11][4];

extern u8 turret_laser_full_beam_box[4];

extern u8* turret_laser_beam_boxes[12];
