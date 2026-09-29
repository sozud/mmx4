// MiscObj, misc_object_update_funcs[55]
// 800D3084..800D3388
#include "common.h"

// sigma_final_fx_init
INCLUDE_ASM("main/nonmatchings/misc/misc_55_sigma_final_fx", func_800D3084);

void sigma_final_fx_charge(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->state = 2;
    }
}

void sigma_final_fx_gust(struct MiscObj* self)
{
    move_with_gravity((struct AnimatedObj*)self);
    animate_object(self);
    is_on_screen(self);
    if (func_8002B160(self) != 0) {
        self->state = 2;
    }
}

void sigma_final_fx_follow(struct MiscObj* self)
{
    self->x_pos.u.hi = self->ext.misc_55.owner->x_pos.u.hi;
    self->y_pos.u.hi = self->ext.misc_55.owner->y_pos.u.hi;
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (self->ext.misc_55.owner->state == 2) {
        self->state = 2;
        self->unk5 = 0;
    }
    if (func_8002B160(BASE_OBJECT(self)) != 0) {
        self->state = 2;
        self->unk5 = 0;
    }
}

void sigma_final_fx_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void sigma_final_fx_update(struct MiscObj* self)
{
    if (self->ext.misc_55.owner->ext.main_74.death_kind != 0) {
        self->state = 2;
        self->unk5 = 0;
    }
    sigma_final_fx_state_funcs[self->state](self);
}

void (*sigma_final_fx_state_funcs[5])(struct MiscObj*) = {
    func_800D3084,
    sigma_final_fx_charge,
    sigma_final_fx_despawn,
    sigma_final_fx_gust,
    sigma_final_fx_follow,
};
