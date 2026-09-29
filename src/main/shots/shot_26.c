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
INCLUDE_ASM("main/nonmatchings/shots/shot_26", func_8009EEC8);

void sentry_shot_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
    } else {
        if (func_8002BB80(self, &g_Player) != 0) {
            self->state++;
            return;
        }
        if (self->unk70 != 0) {
            spawn_explosion(BASE_OBJECT(self));
            self->state++;
            return;
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
