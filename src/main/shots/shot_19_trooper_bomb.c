// ShotObj, shot_object_update_funcs[19]
// 8009CC64..8009CF38
#include "common.h"

u8 trooper_bomb_terrain_box[4] = { 0, 0, 4, 4 };
u8 trooper_bomb_debris[8] = { 3, 5, 4, 6, 4, 6, 3, 5 };
s8 trooper_bomb_offsets[4] = { 0, 0, 0, 0 };

void trooper_bomb_update(struct ShotObj* self)
{
    trooper_bomb_state_funcs[self->state](self);
    CollisionRelated(self);
}

// trooper_bomb_init
INCLUDE_ASM("main/nonmatchings/shots/shot_19_trooper_bomb", func_8009CCB4);

void trooper_bomb_fall(struct ShotObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->unk70 != 0) {
        self->unk84.value = 0x40;
        self->on_screen = 0;
        self->state++;
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
        if (!(main_bss_state.frame_counter & 7)) {
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
