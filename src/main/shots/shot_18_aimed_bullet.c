// ShotObj, shot_object_update_funcs[18]
// 8009CAC0..8009CC64
#include "common.h"

void aimed_bullet_update(struct ShotObj* self)
{
    aimed_bullet_state_funcs[self->state](self);
}

void aimed_bullet_init(struct ShotObj* arg0)
{
    struct ShotObj* self = arg0;

    self->state = 1;
    self->on_screen = 1;
    self->unk54 = aimed_bullet_hit_box;
    self->unk50.data = aimed_bullet_hit_box;
    self->unk16 = 0;
    self->unk68 = 0;
    self->unk58.data = (u8*)D_80106070;

    set_velocity_from_angle(
        MOVING_OBJECT(self),
        angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);

    self->unk60 = 3;
    self->unk5C = 1;
    self->x_vel.val *= 2;
    self->y_vel.val *= 2;
    set_animation(self, 0xC);
}

void aimed_bullet_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
    } else if (func_8002BB80(self, &g_Player) == 0 && func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
        return;
    }
    self->state = 2;
}

void aimed_bullet_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*aimed_bullet_state_funcs[])(struct ShotObj*) = {
    aimed_bullet_init,
    aimed_bullet_fly,
    aimed_bullet_despawn,
};
