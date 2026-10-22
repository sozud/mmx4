// ShotObj, shot_object_update_funcs[7]
// 8009AD30..8009AEE4
#include "common.h"
#include "main/shots/shot_07_dropped_bomb.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/collision_bounds.h"
#endif

// dropped_bomb_state_funcs
extern void (*dropped_bomb_state_funcs[])(struct ShotObj*);

void dropped_bomb_fall(struct ShotObj*);
void dropped_bomb_despawn(struct ShotObj*);
void dropped_bomb_idle(struct ShotObj*);

u8 dropped_bomb_hit_box[4] = { 0xFE, 0x16, 0x07, 0x0E };
u8 dropped_bomb_terrain_box[4] = { 0xF8, 0x0A, 0x0D, 0x1A };

void dropped_bomb_update(struct ShotObj* self)
{
    dropped_bomb_state_funcs[self->state](self);
}

// dropped_bomb_init
#ifdef MMX4_PC
void func_8009AD6C(struct ShotObj* arg0);
#endif

#ifdef MMX4_PC
void func_8009AD6C(struct ShotObj* arg0)
{
    arg0->y_vel.val = -0x10000;
    arg0->unk2C = 0x3000;
    arg0->unk68 = (struct Unk_unk68*)dropped_bomb_hit_box;
    arg0->unk54 = dropped_bomb_terrain_box;
    arg0->unk50.data = dropped_bomb_terrain_box;
    arg0->unk58.data = (const u8*)D_80105FF0;
    arg0->unk60 = 5;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    set_animation(arg0, 2);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_07_dropped_bomb", func_8009AD6C);
#endif

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
