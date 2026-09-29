// ShotObj, shot_object_update_funcs[11]
// 8009B67C..8009B7F8
#include "common.h"

u8 enemy_bullet_hit_box[4] = { 0xFC, 0xFD, 0x06, 0x05 };

void enemy_bullet_update(struct ShotObj* self)
{
    enemy_bullet_state_funcs[self->state](self);
}

// enemy_bullet_init
INCLUDE_ASM("main/nonmatchings/shots/shot_11", func_8009B6B8);

void enemy_bullet_fly(struct ShotObj* self)
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

void enemy_bullet_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*enemy_bullet_state_funcs[])(struct ShotObj*) = {
    func_8009B6B8,
    enemy_bullet_fly,
    enemy_bullet_despawn,
};
