// ShotObj, shot_object_update_funcs[57]
// 800AE450..800AE6B4
#include "common.h"

u16 sigma_beam_hitbox_offsets[6][2] = {
    { 0x4AE, 0x29C },
    { 0x49F, 0x279 },
    { 0x49D, 0x259 },
    { 0x49B, 0x231 },
    { 0x49D, 0x259 },
    { 0x49D, 0x259 },
};

s16 sigma_beam_hitbox_box_data[30][2] = {
    { -7040, 16672 },
    { -5984, 14112 },
    { -4672, 11296 },
    { -3104, 8224 },
    { -768, 5408 },
    { -1504, 3104 },
    { -704, 1568 },
    { 7040, 14368 },
    { 6048, 11808 },
    { 5312, 8736 },
    { 4320, 6176 },
    { 3072, 3872 },
    { 1824, 3088 },
    { 1328, 1808 },
    { 576, 1056 },
    { 13440, 14368 },
    { 11936, 10528 },
    { 10432, 7712 },
    { 8160, 5152 },
    { 5888, 3360 },
    { 3616, 1056 },
    { 576, 1056 },
    { 16604, 4172 },
    { 12533, 4157 },
    { 8217, 4132 },
    { 4156, 4108 },
    { 592, 4104 },
    { 23442, 12512 },
    { 23392, 12477 },
    { -22144, -5832 },
};

u8 sigma_beam_hitbox_ranges[6][2] = {
    { 22, 4 },
    { 15, 6 },
    { 7, 7 },
    { 0, 6 },
    { 29, 1 },
    { 27, 2 },
};

s16* sigma_beam_hitbox_boxes[30] = {
    sigma_beam_hitbox_box_data[0],
    sigma_beam_hitbox_box_data[1],
    sigma_beam_hitbox_box_data[2],
    sigma_beam_hitbox_box_data[3],
    sigma_beam_hitbox_box_data[4],
    sigma_beam_hitbox_box_data[5],
    sigma_beam_hitbox_box_data[6],
    sigma_beam_hitbox_box_data[7],
    sigma_beam_hitbox_box_data[8],
    sigma_beam_hitbox_box_data[9],
    sigma_beam_hitbox_box_data[10],
    sigma_beam_hitbox_box_data[11],
    sigma_beam_hitbox_box_data[12],
    sigma_beam_hitbox_box_data[13],
    sigma_beam_hitbox_box_data[14],
    sigma_beam_hitbox_box_data[15],
    sigma_beam_hitbox_box_data[16],
    sigma_beam_hitbox_box_data[17],
    sigma_beam_hitbox_box_data[18],
    sigma_beam_hitbox_box_data[19],
    sigma_beam_hitbox_box_data[20],
    sigma_beam_hitbox_box_data[21],
    sigma_beam_hitbox_box_data[22],
    sigma_beam_hitbox_box_data[23],
    sigma_beam_hitbox_box_data[24],
    sigma_beam_hitbox_box_data[25],
    sigma_beam_hitbox_box_data[26],
    sigma_beam_hitbox_box_data[27],
    sigma_beam_hitbox_box_data[28],
    sigma_beam_hitbox_box_data[29],
};

// sigma_beam_hitbox_init
INCLUDE_ASM("main/nonmatchings/shots/shot_57", func_800AE450);

void sigma_beam_hitbox_pulse(struct ShotObj* self)
{
    u32 i;
    u32 start;

    if (self->unk7C->unk95 != 0) {
        start = self->unk8C.bytes[0];
        for (i = 0; i < self->unk8C.bytes[1] + 1; i++) {
            self->unk50.frames = sigma_beam_hitbox_boxes[start++];
            func_8002D9BC(self);
        }
        self->state = 2;
    }
}

void sigma_beam_hitbox_active(struct ShotObj* self)
{
    u32 i;
    u32 start;

    if (self->unk7C->unk95 != 0) {
        start = self->unk8C.bytes[0];
        for (i = 0; i < self->unk8C.bytes[1] + 1; i++) {
            self->unk50.frames = sigma_beam_hitbox_boxes[start++];
            func_8002D9BC(self);
        }
        return;
    }
    self->state = 3;
}

void sigma_beam_hitbox_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void sigma_beam_hitbox_update(struct ShotObj* self)
{
    if (self->unk7C->unk94 != 0) {
        self->state = 3;
    }
    sigma_beam_hitbox_state_funcs[self->state](self);
}

void (*sigma_beam_hitbox_state_funcs[])(struct ShotObj*) = {
    func_800AE450,
    sigma_beam_hitbox_pulse,
    sigma_beam_hitbox_active,
    sigma_beam_hitbox_despawn,
};
