// ShotObj, shot_object_update_funcs[11]
// 8009B67C..8009B7F8
#include "common.h"
#include "main/shots/shot_11_enemy_bullet.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/collision_bounds.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

// enemy_bullet_state_funcs
extern void (*enemy_bullet_state_funcs[])(struct ShotObj*);

void enemy_bullet_fly(struct ShotObj*);
void enemy_bullet_despawn(struct ShotObj*);

u8 enemy_bullet_hit_box[4] = { 0xFC, 0xFD, 0x06, 0x05 };

void enemy_bullet_update(struct ShotObj* self)
{
    enemy_bullet_state_funcs[self->state](self);
}

// enemy_bullet_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009B6B8(struct ShotObj* arg0);
#endif

void func_8009B6B8(struct ShotObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk54 = enemy_bullet_hit_box;
    arg0->unk50.data = enemy_bullet_hit_box;
    arg0->unk58.collision_data = D_80106070;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk60 = 3;
    arg0->x_vel.val *= 3;
    arg0->y_vel.val *= 3;
    arg0->unk5C = 1;
    set_animation(ANIMATED_OBJECT(arg0), 0x11);
}

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
