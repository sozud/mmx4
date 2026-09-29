// ShotObj, shot_object_update_funcs[8]
// 8009AEE4..8009B07C
#include "common.h"

u8 shell_crawler_shot_hit_box[4] = { 0xFB, 0xFC, 0x09, 0x07 };

void shell_crawler_shot_init(struct ShotObj* self)
{
    s32 temp_v1;
    s32 var_v0;
    s32 var_a1;

    var_a1 = FIXED(-2.5);
    self->on_screen = 1;
    self->state = (u8)self->state + 1;
    if (self->unk15 != 0) {
        var_a1 = FIXED(2.5);
    }
    temp_v1 = *(s16*)&self->x_pos.i.hi;
    self->x_vel.val = var_a1;
    self->unk28 = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    if (self->unk15 != 0) {
        var_v0 = temp_v1 + 0x10;
    } else {
        var_v0 = temp_v1 - 0x10;
    }
    self->x_pos.i.hi = var_v0;
    self->unk16 = 6;
    self->unk54 = shell_crawler_shot_hit_box;
    self->unk50.data = shell_crawler_shot_hit_box;
    self->unk58.data = (u8*)D_80106070;
    self->unk68 = 0;
    self->unk60 = 2;
    self->y_pos.i.hi = (u16)self->y_pos.i.hi + 3;
    set_animation(self, 8);
}

void shell_crawler_shot_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);

    if (func_8002DD04(MAIN_OBJECT(self)) != 0) {
        self->state = 2;
    }

    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
        return;
    }

    self->state++;
}

void shell_crawler_shot_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void shell_crawler_shot_update(struct ShotObj* self)
{
    shell_crawler_shot_state_funcs[self->state](self);
}

void (*shell_crawler_shot_state_funcs[])(struct ShotObj*) = {
    shell_crawler_shot_init,
    shell_crawler_shot_fly,
    shell_crawler_shot_despawn,
};
