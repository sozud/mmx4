// WeaponObj, weapon_object_update_funcs[57]
// 80098838..80098990
#include "common.h"

void ride_chaser_ram_update(struct WeaponObj* arg0)
{
    ride_chaser_ram_state_funcs[arg0->state](arg0);
}

void ride_chaser_ram_init(struct WeaponObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = 0;
    arg0->unk50 = ride_chaser_ram_hit_box;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    set_animation(arg0, 0xC);
}

void ride_chaser_ram_main(struct WeaponObj* arg0)
{
    s8 temp_v1;
    struct PlayerObj* temp_a0;
    struct WeaponObj* self = arg0;
    temp_a0 = self->owner;
    if (temp_a0->state < 2) {
        temp_v1 = temp_a0->unk5;
        if ((temp_v1 == 5) || (temp_v1 == 0)) {
            self->on_screen = 0;
            if (temp_a0->animation_step.fields.frame_index == 3) {
                self->x_pos.val = temp_a0->x_pos.val;
                self->y_pos.val = temp_a0->y_pos.val;
                animate_object(ANIMATED_OBJECT(self));
                update_on_screen(BASE_OBJECT(self), 0x10, 0x10);
            }
            return;
        }
    }

    self->state = 2;
    self->on_screen = 0;
}

void ride_chaser_ram_despawn(struct WeaponObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

extern u8 ride_chaser_shot_angles[8];

extern u8 ride_chaser_shot_animations[8];

u8 ride_chaser_ram_hit_box[4] = { 0xCF, 0xEE, 0x3C, 0x37 };

void (*ride_chaser_ram_state_funcs[])(struct WeaponObj*) = {
    ride_chaser_ram_init,
    ride_chaser_ram_main,
    ride_chaser_ram_despawn,
};
