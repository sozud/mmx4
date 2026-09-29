// ShotObj, shot_object_update_funcs[7]
// 8009AD30..8009AEE4
#include "common.h"

u8 dropped_bomb_hit_box[4] = { 0xFE, 0x16, 0x07, 0x0E };
u8 dropped_bomb_terrain_box[4] = { 0xF8, 0x0A, 0x0D, 0x1A };

void dropped_bomb_update(struct ShotObj* self)
{
    dropped_bomb_state_funcs[self->state](self);
}

// dropped_bomb_init
INCLUDE_ASM("main/nonmatchings/shots/shot_07_dropped_bomb", func_8009AD6C);

void dropped_bomb_fall(struct ShotObj* arg0)
{
    struct ShotObj* self = arg0;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
    } else {
        func_8002D9BC(self);
        CollisionRelated(self);
        if (self->unk70 != 0) {
            self->y_pos.i.hi = (u16)self->y_pos.i.hi + 0x20;
            spawn_explosion(BASE_OBJECT(self));
        } else if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
            update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
            return;
        }
    }
    self->state++;
}

void dropped_bomb_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void dropped_bomb_idle(struct ShotObj* self)
{
}

void (*dropped_bomb_state_funcs[])(struct ShotObj*) = {
    func_8009AD6C,
    dropped_bomb_fall,
    dropped_bomb_despawn,
    dropped_bomb_idle,
};
