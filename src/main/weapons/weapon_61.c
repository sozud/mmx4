// WeaponObj, weapon_object_update_funcs[61, 62]
// 800992FC..800994A0
#include "common.h"

void ride_armor_punch_update(struct WeaponObj* arg0)
{
    ride_armor_punch_state_funcs[arg0->state](arg0);
}

void ride_armor_punch_init(struct WeaponObj* arg0)
{
    arg0->state = 1;
    arg0->unk64 = 1;
    arg0->unk5C = 1;
    arg0->unk60 = 3;
    arg0->on_screen = 0;
    arg0->bg_offset = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = 0;
    arg0->unk50 = 0;
    arg0->unk88.half = 6;
    ride_armor_punch_main(arg0);
}

void ride_armor_punch_main(struct WeaponObj* self)
{
    s8 index;
    s8 event;
    u16 timer;
    struct PlayerObj* owner;

    owner = self->owner;
    self->x_pos.i.hi = (s16)(u16)owner->x_pos.i.hi;
    self->y_pos.i.hi = (s16)(u16)owner->y_pos.i.hi;
    self->animation_step.fields.event = (s8)((u8)owner->animation_step.fields.event >> 4);
    if (self->unk2 != 0) {
        timer = self->unk88.half - 1;
        self->unk88.half = timer;
        if ((timer << 16) == 0) {
            self->unk88.half = 6;
            self->unk64 = (u8)self->unk64 + 1;
        }
    }
    index = self->unk2;
    if ((ride_armor_punch_animations[index] == owner->unk17) && (ride_armor_punch_steps[index] == owner->unk5) && (owner->state == 1)) {
        event = self->animation_step.fields.event;
        if (event == 0) {
            self->unk50 = NULL;
            return;
        }
        self->unk50 = &ride_armor_punch_hit_boxes[event];
        return;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void ride_armor_punch_despawn(struct WeaponObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 ride_armor_punch_hit_boxes[7][4] = {
    { 0xFC, 0xFD, 6, 5 },
    { 0xC0, 0xF9, 0x38, 0x1A },
    { 0xB9, 0xCD, 0x31, 0x40 },
    { 0xB1, 0xBF, 0x4A, 0x60 },
    { 0xB9, 0xD4, 0x3E, 0x3F },
    { 0xB1, 0xBF, 0x4A, 0x60 },
    { 0x96, 0xF1, 0x72, 0x29 },
};

u8 ride_armor_punch_animations[8] = { 8, 9, 0x0A, 0x0B, 0x0F, 0, 0, 0 };

u8 ride_armor_punch_steps[8] = { 3, 9, 3, 6, 0x0D, 0, 0, 0 };

void (*ride_armor_punch_state_funcs[])(struct WeaponObj*) = {
    ride_armor_punch_init,
    ride_armor_punch_main,
    ride_armor_punch_despawn,
};
