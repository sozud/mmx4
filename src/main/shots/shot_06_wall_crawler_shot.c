// ShotObj, shot_object_update_funcs[6]
// 8009A984..8009AD30
#include "common.h"

u8 wall_crawler_shot_hit_boxes[8] = { 0xFD, 0xFA, 8, 8, 0xF7, 0xF6, 0x10, 0x13 };
u8 wall_crawler_shot_terrain_box[4] = { 0, 0, 4, 4 };
s8 wall_crawler_shot_spawn_offsets[16] = {
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

void wall_crawler_shot_update(struct ShotObj* self)
{
    if (self->unk84.value == 0) {
        CollisionRelated(self);
    }
    wall_crawler_shot_state_funcs[self->state](self);
}

// wall_crawler_shot_init
void func_8009A9E4(struct ShotObj* shot)
{
    shot->unk68 = (struct Unk_unk68*)wall_crawler_shot_terrain_box;
    shot->unk54 = wall_crawler_shot_hit_boxes;
    shot->unk50.data = wall_crawler_shot_hit_boxes;
    shot->on_screen = 1;
    shot->unk58.data = (u8*)D_80105FF0;
    shot->state++;
    shot->unk28 = 0;
    shot->unk5C = 1;
    shot->unk2C = 0;
    shot->unk67 = 0;
    shot->unk16 = 0;
    shot->unk60 = 2;
    shot->unk42 &= 0x7FFF;
    shot->x_vel.val *= 3;
    shot->y_vel.val *= 3;
    switch (shot->unk2 & 0xFE) {
    case 2:
    case 4:
    case 6:
        shot->x_pos.i.hi += wall_crawler_shot_spawn_offsets[6];
        shot->y_pos.i.hi += wall_crawler_shot_spawn_offsets[7];
        break;
    case 10:
    case 12:
    case 14:
        shot->x_pos.i.hi += wall_crawler_shot_spawn_offsets[4];
        shot->y_pos.i.hi += wall_crawler_shot_spawn_offsets[5];
        break;
    case 8:
        shot->x_pos.i.hi += wall_crawler_shot_spawn_offsets[8];
        shot->y_pos.i.hi += wall_crawler_shot_spawn_offsets[9];
        break;
    case 18:
    case 20:
    case 22:
        shot->x_pos.i.hi += wall_crawler_shot_spawn_offsets[12];
        shot->y_pos.i.hi += wall_crawler_shot_spawn_offsets[13];
        break;
    case 26:
    case 28:
    case 30:
        shot->x_pos.i.hi += wall_crawler_shot_spawn_offsets[14];
        shot->y_pos.i.hi += wall_crawler_shot_spawn_offsets[15];
        break;
    case 24:
        shot->x_pos.i.hi += wall_crawler_shot_spawn_offsets[10];
        shot->y_pos.i.hi += wall_crawler_shot_spawn_offsets[11];
        break;
    default:
        if (shot->unk15 & 0x40) {
            shot->x_pos.i.hi += wall_crawler_shot_spawn_offsets[2];
            shot->y_pos.i.hi += wall_crawler_shot_spawn_offsets[3];
        } else {
            shot->x_pos.i.hi += wall_crawler_shot_spawn_offsets[0];
            shot->y_pos.i.hi += wall_crawler_shot_spawn_offsets[1];
        }
        break;
    }
    set_animation(shot, 0xB);
}

void wall_crawler_shot_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
    } else {
        if (self->unk84.value == 0) {
            if (func_8002BB80(self, &g_Player) != 0) {
                self->state++;
                return;
            }
            if (self->unk70 != 0) {
                spawn_explosion(BASE_OBJECT(self));
                self->state++;
                return;
            }
        }
        if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) != 0) {
            self->state++;
            return;
        }
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
        return;
    }
    self->state++;
}

void wall_crawler_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void wall_crawler_shot_idle(struct ShotObj* self)
{
}

void (*wall_crawler_shot_state_funcs[])(struct ShotObj*) = {
    func_8009A9E4,
    wall_crawler_shot_fly,
    wall_crawler_shot_despawn,
    wall_crawler_shot_idle,
};
