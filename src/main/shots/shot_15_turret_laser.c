// ShotObj, shot_object_update_funcs[15]
// 8009C0F0..8009C364
#include "common.h"

u8 turret_laser_hit_box[4] = { 0xFD, 0xFD, 0x06, 0x06 };

void turret_laser_update(struct ShotObj* self)
{
    turret_laser_state_funcs[self->state](self);
}

// turret_laser_init
INCLUDE_ASM("main/nonmatchings/shots/shot_15_turret_laser", func_8009C12C);

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
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
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
