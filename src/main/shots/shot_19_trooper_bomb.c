// ShotObj, shot_object_update_funcs[19]
// 8009CC64..8009CF38
#include "common.h"
#include "main/shots/shot_19_trooper_bomb.h"
#include "main/collision.h"
#include "main/mains/main_50_train_crate.h"
#include "main/misc/misc_02_rubble.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/stage_objects.h"
#include "main/55C4.h"

// trooper_bomb_state_funcs
extern void (*trooper_bomb_state_funcs[])(struct ShotObj*);

void trooper_bomb_fall(struct ShotObj*);
void trooper_bomb_explode(struct ShotObj*);
void trooper_bomb_despawn(struct ShotObj*);
#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/55C4.h"
#endif

u8 trooper_bomb_terrain_box[4] = { 0, 0, 4, 4 };
u8 trooper_bomb_debris[8] = { 3, 5, 4, 6, 4, 6, 3, 5 };
s8 trooper_bomb_offsets[4] = { 0, 0, 0, 0 };

void trooper_bomb_update(struct ShotObj* self)
{
    trooper_bomb_state_funcs[self->state](self);
    CollisionRelated(self);
}

// trooper_bomb_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009CCB4(struct ShotObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009CCB4(struct ShotObj* arg0)
{
    arg0->unk68 = (struct Unk_unk68*)trooper_bomb_terrain_box;
    arg0->unk60 = 2;
    arg0->unk2C = 0x2000;
    arg0->on_screen = 1;
    arg0->unk5C = 1;
    arg0->y_vel.val = 0x1F000;
    arg0->unk28 = 0;
    arg0->unk67 = 0;
    arg0->unk16 = 0;
    arg0->unk54 = NULL;
    arg0->unk50.data = NULL;
    arg0->unk58.data = NULL;
    arg0->x_vel.val = -0x1C000;
    arg0->state++;
    arg0->unk42 &= 0x7FFF;
    arg0->x_pos.i.hi += trooper_bomb_offsets[0];
    arg0->y_pos.i.hi += trooper_bomb_offsets[1];
    set_animation(arg0, 6);
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_19_trooper_bomb", func_8009CCB4);
#endif

void trooper_bomb_fall(struct ShotObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->unk70 != 0) {
        self->state++;
        self->unk84.value = 0x40;
        self->on_screen = 0;
        return;
    }
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

void trooper_bomb_explode(struct ShotObj* self)
{
    if (--self->unk84.value != 0) {
        if (self->unk84.value == 0x20) {
            self->unk7C->unk1C.bytes[0] = 1;
        }
        if (!(WEAPON_FRAME_COUNTER & 7)) {
            if (self->unk84.value >= 0x34) {
                func_800C842C(8, trooper_bomb_debris, self, 0x28, train_crate_animations);
                self->x_pos.i.hi += 0x20;
                func_800C842C(8, trooper_bomb_debris, self, 0x28, train_crate_animations);
                self->x_pos.i.hi -= 0x20;
            }
            func_800AF878(BASE_OBJECT(self), 1, 0x30, 0x20);
            func_800AF878(BASE_OBJECT(self), 1, 0x18, 0x10);
            start_screen_shake_y(8, 4, 1);
        }
    } else {
        self->state++;
    }
}

void trooper_bomb_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*trooper_bomb_state_funcs[])(struct ShotObj*) = {
    func_8009CCB4,
    trooper_bomb_fall,
    trooper_bomb_explode,
    trooper_bomb_despawn,
};
