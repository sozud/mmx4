// ShotObj, shot_object_update_funcs[40]
// 800A5348..800A56E4
#include "common.h"

void hatch_blast_update(struct ShotObj* self)
{
    hatch_blast_state_funcs[self->state](self);
}

void hatch_blast_init(struct ShotObj* self)
{
    self->state = 1;
    self->on_screen = 1;
    self->unk16 = 2;
    self->unk68 = &hatch_blast_terrain_box;
    self->unk5C = 3;
    self->unk5 = 0;
    self->unk6 = 0;
    self->unk7 = 0;
    self->unk8A = 0;
    self->unk84.value = 0;
    self->unk54 = NULL;
    self->unk50.data = NULL;
    self->unk58.data = NULL;
    self->unk60 = 6;
    self->unk61 = 0;
    self->y_pos.i.hi = (u16)self->y_pos.i.hi + 0x7E;
    set_animation(self, 2);
}

void hatch_blast_open(struct ShotObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 1;
        self->unk6 = 0;
        self->timer = 0xF0;
        self->unk50.data = hatch_blast_hit_box;
        set_animation(self, 4);
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
}

void hatch_blast_fire(struct ShotObj* self)
{
    struct ShotObj* shot = self;

    if (shot->timer == 0) {
        shot->unk5 = 2;
        shot->unk6 = 0;
        shot->unk50.data = 0;
        set_animation(shot, 3);
        return;
    }
    if ((engine_obj.stage == 7) && (shot->unk70 & 0xB) && (shot->unk7 == 0)) {
        shot->unk8A = 0x14;
        shot->unk7 = 1;
    }
    shot->timer = (u16)shot->timer - 1;
    animate_object(ANIMATED_OBJECT(shot));
}

void hatch_blast_close(struct ShotObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
        return;
    }
    animate_object(self);
}

void hatch_blast_main(struct ShotObj* self)
{
    s32 x_offset;

    if (self->unk7C->active != 0 && self->unk7C->id == 0x3F) {
        self->unk18.val = self->x_pos.val;
        self->unk1C.val = self->y_pos.val;
        hatch_blast_step_funcs[self->unk5](self);
        func_8002D9BC(self);
        func_8002C808(PLAYER_OBJECT(self));
        if (self->unk8A != 0) {
            if (!(D_80141BD8.unk0 & 3)) {
                func_800AF878(BASE_OBJECT(self), 1, 0x60, 0x60);
                func_800AF878(BASE_OBJECT(self), 1, 0x30, 0x30);
                x_offset = get_random() & 0x30;
                spawn_debris_offset(7, hatch_blast_debris, (struct MiscObj*)self, x_offset, get_random() & 0x30);
            }
            if (--self->unk8A == 0) {
                apply_tile_effect(0, hatch_blast_tile_x[self->unk2], 0x150);
                spawn_debris(0xE, hatch_blast_break_debris, self);
            }
        }
        update_on_screen(BASE_OBJECT(self), 0x80, 0x80);
        return;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void hatch_blast_despawn(struct ShotObj* self)
{
    self->unk7C->unk7 = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

u8 hatch_blast_hit_box[4] = { 0xCF, 0x82, 0x60, 0xFF };

struct Unk_unk68 hatch_blast_terrain_box = { 0, 8, 0x2E, 0x78 };

s16 hatch_blast_tile_x[4] = { 0x0AE0, 0x14E0, 0x1710, 0 };

u8 hatch_blast_debris[8] = { 6, 7, 8, 9, 0x0A, 0x0B, 0x0C, 0 };

u8 hatch_blast_break_debris[16] = { 6, 7, 8, 9, 0x0A, 0x0B, 0x0C, 6, 7, 8, 9, 0x0A, 0x0B, 0x0C, 0, 0 };

void (*hatch_blast_state_funcs[])(struct ShotObj*) = {
    hatch_blast_init,
    hatch_blast_main,
    hatch_blast_despawn,
};

void (*hatch_blast_step_funcs[3])(struct ShotObj*) = {
    hatch_blast_open,
    hatch_blast_fire,
    hatch_blast_close,
};
