// MiscObj, misc_object_update_funcs[51]
// 800D1DC4..800D2190
#include "common.h"

void capsule_part_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    capsule_part_state_funcs[self->state](self);
}

void capsule_part_init(struct MiscObj* self)
{
    struct MainObj* source;
    const u8* const* animation_table;

    source = self->ext.misc_51.source;
    self->bg_offset = g_Player.bg_offset;
    self->unk15 = source->unk15;
    self->unk40 = source->unk40;
    self->unk42 = source->unk42;
    self->unk3C = (void*)source->sprite_frames;
    self->animation_table = (u32**)source->animation_table;
    self->unk6 = 0;
    self->state++;
    self->unk5 = self->unk2 >> 4;
    self->unk2 &= 0xF;
    capsule_part_main(self);
}

void capsule_part_main(struct MiscObj* self)
{
    struct MainObj* source;

    source = self->ext.misc_51.source;
    capsule_part_type_funcs[self->unk5](self);
    if (source->active != 0x41) {
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void capsule_part_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void capsule_part_base(struct MiscObj* self)
{
    capsule_part_base_funcs[self->unk6](self);
    is_on_screen(BASE_OBJECT(self));
}

void capsule_part_base_open(struct MiscObj* self)
{
    self->unk16 = 2;
    set_animation(self, 2);
    self->unk6++;
}

void capsule_part_base_opening(struct MiscObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 5);
        self->unk6++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void capsule_part_base_animate(struct MiscObj* self)
{
    animate_object(self);
}

void capsule_part_glass(struct MiscObj* self)
{
    if (self->unk6 == 0) {
        self->unk16 = 6;
        set_animation(self, 3);
        self->unk6++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
    is_on_screen(BASE_OBJECT(self));
}

// capsule_part_beam
void func_800D2094(struct MiscObj* self)
{
    if (self->unk6 == 0) {
        self->unk16 = 1;
        set_animation(self, 7);
        self->ext.misc_51.unk54 = 0x78;
        self->unk6++;
    } else if (--self->ext.misc_51.unk54 != 0) {
        animate_object(ANIMATED_OBJECT(self));
    } else {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
    is_on_screen(BASE_OBJECT(self));
}

void capsule_part_light(struct MiscObj* self)
{
    if (self->unk6 == 0) {
        self->unk16 = 1;
        set_animation(self, 9);
        self->unk6++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
    is_on_screen(BASE_OBJECT(self));
}

void (*capsule_part_state_funcs[3])(struct MiscObj*) = {
    capsule_part_init,
    capsule_part_main,
    capsule_part_despawn,
};

void (*capsule_part_type_funcs[4])(struct MiscObj*) = {
    capsule_part_base,
    capsule_part_glass,
    func_800D2094,
    capsule_part_light,
};

void (*capsule_part_base_funcs[3])(struct MiscObj*) = {
    capsule_part_base_open,
    capsule_part_base_opening,
    capsule_part_base_animate,
};
