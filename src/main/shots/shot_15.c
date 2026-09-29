// ShotObj, shot_object_update_funcs[15]
// 8009C0F0..8009C364
#include "common.h"

u8 turret_laser_hit_box[4] = { 0xFD, 0xFD, 0x06, 0x06 };

void turret_laser_update(struct ShotObj* self)
{
    turret_laser_state_funcs[self->state](self);
}

// turret_laser_init
INCLUDE_ASM("main/nonmatchings/shots/shot_15", func_8009C12C);

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

u8 turret_laser_beam_box_data[11][4] = {
    { 0xF3, 0xFD, 0x0A, 0x05 },
    { 0xE4, 0xFD, 0x1A, 0x05 },
    { 0xCC, 0xFD, 0x31, 0x05 },
    { 0xAB, 0xFD, 0x5D, 0x05 },
    { 0xFD, 0xF4, 0x05, 0x0B },
    { 0xFD, 0xE8, 0x05, 0x17 },
    { 0xFD, 0xCD, 0x05, 0x31 },
    { 0xFD, 0xAE, 0x05, 0x42 },
    { 0xFD, 0xFE, 0x05, 0x0D },
    { 0xFD, 0xFE, 0x05, 0x16 },
    { 0xFD, 0xFE, 0x05, 0x34 },
};

u8 turret_laser_full_beam_box[4] = { 0xFD, 0xFE, 0x05, 0x50 };

u8* turret_laser_beam_boxes[12] = {
    turret_laser_beam_box_data[0],
    turret_laser_beam_box_data[1],
    turret_laser_beam_box_data[2],
    turret_laser_beam_box_data[3],
    turret_laser_beam_box_data[4],
    turret_laser_beam_box_data[5],
    turret_laser_beam_box_data[6],
    turret_laser_beam_box_data[7],
    turret_laser_beam_box_data[8],
    turret_laser_beam_box_data[9],
    turret_laser_beam_box_data[10],
    turret_laser_full_beam_box,
};
