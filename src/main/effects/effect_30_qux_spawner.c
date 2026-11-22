// EffectObj, effect_object_update_funcs[30]
// 800BC2E0..800BC4D8
#include "common.h"
#include "main/effects/effect_30_qux_spawner.h"
#include "main/objects.h"
#include "main/CB184.h"
#include "main/visuals/visual_04_blast.h"

void qux_spawner_update(struct EffectObj* self)
{
    self->state = 1;
    self->unk5 = 0;
    qux_object.active = DEMO_ALT(0x41, 1);
    qux_object.id = 1;
#ifndef VERSION_DEMO
    qux_object.state = 0;
    qux_object.unk5 = 0;
    qux_object.unk6 = 0;
    qux_object.unk7 = 0;
#endif
    qux_object.unk2 = self->unk2;
    qux_object.backref = self->backref;
    qux_object.x_pos.val = self->x_pos.val;
    qux_object.y_pos.val = self->y_pos.val;
#ifdef VERSION_DEMO
    ZeroObjectState(OBJECT_HEADER(self));
#else
    despawn_object_permanently(OBJECT_HEADER(self));
#endif
}

void floor_trap_wait(struct EffectObj* self)
{
    s16 temp_a0;

    self->x_pos.val &= 0xFFF00000;
    self->y_pos.val &= 0xFFF00000;
    temp_a0 = self->x_pos.i.hi;
    if (qux_object.x_pos.i.hi >= temp_a0 + 0x18 && qux_object.x_pos.i.hi <= temp_a0 + 0x30 && self->y_pos.i.hi - qux_object.y_pos.i.hi == 0x1A) {
        self->unk5 = 3;
        self->state++;
    }
}

void floor_trap_explode(struct EffectObj* self)
{
    struct ShotObj* shot;
    struct ShotObj* temp_v0_3;

    self->unk5--;
    if (self->unk5 == 0) {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x20;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk2 = 0;
        }
        temp_v0_3 = find_free_shot_obj();
        if (temp_v0_3 != 0) {
            temp_v0_3->active = 0x41;
            temp_v0_3->id = 0x20;
            temp_v0_3->unk7C = WEAPON_OBJECT(self);
            temp_v0_3->unk2 = 1;
        }
        spawn_explosion_at(0, self->x_pos.i.hi + 0x10, self->y_pos.i.hi, 0);
        spawn_explosion_at(0, self->x_pos.i.hi + 0x28, self->y_pos.i.hi, 1);
        apply_tile_effect(0xA, self->x_pos.i.hi, self->y_pos.i.hi - 0x20);
        ZeroObjectState(OBJECT_HEADER(self));
    }
}
