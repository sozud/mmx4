// ShotObj, shot_object_update_funcs[14]
// 8009BF14..8009C0F0
#include "common.h"

u8 dash_gunner_shot_hit_box[4] = { 0xFD, 0xFE, 0x05, 0x04 };

void dash_gunner_shot_update(struct ShotObj* self)
{
    dash_gunner_shot_state_funcs[self->state](self);
}

void dash_gunner_shot_init(struct ShotObj* self)
{
    s16 x_pos;

    self->state = 1;
    self->on_screen = 1;
    self->unk58.collision_data = D_80106070;
    self->unk16 = 0;
    self->unk42 &= 0x7FFF;
    if (self->unk15 == 0) {
        x_pos = (u16)self->x_pos.i.hi - 6;
    } else {
        x_pos = (u16)self->x_pos.i.hi + 6;
    }
    self->x_pos.i.hi = x_pos;
    self->unk54 = dash_gunner_shot_hit_box;
    self->unk50.data = dash_gunner_shot_hit_box;
    self->unk5C = 1;
    self->unk68 = NULL;
    self->unk60 = 3;
    set_animation(self, 5);
}

void dash_gunner_shot_fly(struct ShotObj* self)
{
    s32 in_range;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (engine_obj.stage == 3) {
        if ((u8)self->unk2 < 4) {
            in_range = g_Player.x_pos.i.hi < 0x7B7;
        } else {
            in_range = g_Player.x_pos.i.hi < 0x9B7;
        }
        if (in_range != 0) {
            func_8002D9BC(self);
        }
    } else {
        func_8002D9BC(self);
    }
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 2;
    } else {
        self->unk42 &= 0x7FFF;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
    } else {
        self->state = 2;
    }
}

void dash_gunner_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*dash_gunner_shot_state_funcs[])(struct ShotObj*) = {
    dash_gunner_shot_init,
    dash_gunner_shot_fly,
    dash_gunner_shot_despawn,
};
