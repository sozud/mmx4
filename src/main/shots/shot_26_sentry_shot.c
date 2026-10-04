// ShotObj, shot_object_update_funcs[26]
// 8009EE68..8009F240
#include "common.h"

u8 sentry_shot_hit_boxes[8] = { 0xFD, 0xFA, 8, 8, 0xF7, 0xF6, 0x10, 0x13 };
u8 sentry_shot_terrain_box[4] = { 0, 0, 4, 4 };
s8 sentry_shot_spawn_offsets[16] = {
    -0x0D,
    0,
    0x0D,
    0,
    -0x0A,
    -0x0C,
    0x0A,
    -0x0C,
    0,
    -0x10,
    0,
    0x10,
    -0x0A,
    0x0C,
    0x0A,
    0x0C,
};

void sentry_shot_update(struct ShotObj* self)
{
    if (self->unk84.value == 0) {
        CollisionRelated(self);
    }
    sentry_shot_state_funcs[self->state](self);
}

// sentry_shot_init
void func_8009EEC8(struct ShotObj* shot)
{
    shot->on_screen = 1;
    shot->unk68 = (struct Unk_unk68*)sentry_shot_terrain_box;
    shot->unk54 = sentry_shot_hit_boxes;
    shot->unk50.data = sentry_shot_hit_boxes;
    shot->unk58.data = (u8*)D_80105FF0;
    shot->unk28 = 0;
    shot->unk2C = 0;
    shot->unk67 = 0;
    shot->unk16 = 1;
    shot->state++;
    shot->unk40 = shot->unk7C->unk40;
    shot->unk42 = shot->unk7C->unk42 & 0x7FFF;
    shot->animation_table = shot->unk7C->animation_table;
    shot->unk3C = shot->unk7C->unk3C;
    shot->unk15 = shot->unk7C->unk15;
    shot->bg_offset = shot->unk7C->bg_offset;
    shot->unk60 = 3;
    shot->unk5C = 1;
    shot->x_vel.val *= 2;
    shot->y_vel.val *= 2;
    switch (shot->unk2 & 0xFE) {
    case 2:
    case 4:
    case 6:
        shot->x_pos.i.hi += sentry_shot_spawn_offsets[6];
        shot->y_pos.i.hi += sentry_shot_spawn_offsets[7];
        break;
    case 10:
    case 12:
    case 14:
        shot->x_pos.i.hi += sentry_shot_spawn_offsets[4];
        shot->y_pos.i.hi += sentry_shot_spawn_offsets[5];
        break;
    case 8:
        shot->x_pos.i.hi += sentry_shot_spawn_offsets[8];
        shot->y_pos.i.hi += sentry_shot_spawn_offsets[9];
        break;
    case 18:
    case 20:
    case 22:
        shot->x_pos.i.hi += sentry_shot_spawn_offsets[12];
        shot->y_pos.i.hi += sentry_shot_spawn_offsets[13];
        break;
    case 26:
    case 28:
    case 30:
        shot->x_pos.i.hi += sentry_shot_spawn_offsets[14];
        shot->y_pos.i.hi += sentry_shot_spawn_offsets[15];
        break;
    case 24:
        shot->x_pos.i.hi += sentry_shot_spawn_offsets[10];
        shot->y_pos.i.hi += sentry_shot_spawn_offsets[11];
        break;
    default:
        if (shot->unk15 & 0x40) {
            shot->x_pos.i.hi += sentry_shot_spawn_offsets[2];
            shot->y_pos.i.hi += sentry_shot_spawn_offsets[3];
        } else {
            shot->x_pos.i.hi += sentry_shot_spawn_offsets[0];
            shot->y_pos.i.hi += sentry_shot_spawn_offsets[1];
        }
        break;
    }
    set_animation(shot, 6);
}

void sentry_shot_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state++;
        return;
    }
    if (func_8002BB80(self, &g_Player) == 0) {
        if (self->unk70 != 0) {
            spawn_explosion(BASE_OBJECT(self));
            self->state++;
            return;
        }
        if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
            update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
            return;
        }
    }
    self->state++;
    return;
}

void sentry_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void sentry_shot_idle(struct ShotObj* self)
{
}

void (*sentry_shot_state_funcs[])(struct ShotObj*) = {
    func_8009EEC8,
    sentry_shot_fly,
    sentry_shot_despawn,
    sentry_shot_idle,
};
