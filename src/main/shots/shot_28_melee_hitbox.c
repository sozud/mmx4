// ShotObj, shot_object_update_funcs[28]
// 8009F46C..8009F638
#include "common.h"

u8 melee_hitbox_box[4] = { 0xDB, 0xF2, 0x1E, 0x37 };

void melee_hitbox_update(struct ShotObj* self)
{
    struct BaseObj* unk7C = self->unk7C;
    self->x_pos.val = unk7C->x_pos.val;
    self->y_pos.val = unk7C->y_pos.val;
    melee_hitbox_state_funcs[self->state](self);
}

void melee_hitbox_init(struct ShotObj* self)
{
    struct WeaponObj* owner = self->unk7C;

    self->unk40 = owner->unk40;
    self->unk42 = owner->unk42 & 0x7FFF;
    self->animation_table = owner->animation_table;
    self->unk3C = owner->unk3C;
    self->unk15 = owner->unk15;
    self->bg_offset = owner->bg_offset;
    self->x_pos.val = owner->x_pos.val;
    self->y_pos.val = owner->y_pos.val;
    self->unk50.data = melee_hitbox_box;
    self->unk54 = NULL;
    self->unk5C = 1;
    self->unk16 = 4;
    self->unk60 = 6;
    self->unk68 = NULL;
    self->unk58.data = NULL;
    set_animation(self, 0xB);
    self->unk5 = 2;
    self->state++;
}

void melee_hitbox_active(struct ShotObj* self)
{
    struct WeaponObj* temp_v1;

    temp_v1 = self->unk7C;
    if (temp_v1->state > 1) {
        self->state++;
        return;
    }
    if (temp_v1->animation_step.fields.frame_index == 3) {
        animate_object(ANIMATED_OBJECT(self));
        func_8002D9BC(self);
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    }
}

void melee_hitbox_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*melee_hitbox_state_funcs[])(struct ShotObj*) = {
    melee_hitbox_init,
    melee_hitbox_active,
    melee_hitbox_despawn,
};
