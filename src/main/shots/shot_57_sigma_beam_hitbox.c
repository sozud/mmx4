// ShotObj, shot_object_update_funcs[57]
// 800AE450..800AE6B4
#include "common.h"
#include "main/shots/shot_57_sigma_beam_hitbox.h"
#include "main/1E1BC.h"
#include "main/objects.h"

// sigma_beam_hitbox_state_funcs
extern void (*sigma_beam_hitbox_state_funcs[])(struct ShotObj*);

void sigma_beam_hitbox_pulse(struct ShotObj*);
void sigma_beam_hitbox_active(struct ShotObj*);
void sigma_beam_hitbox_despawn(struct ShotObj*);

u16 sigma_beam_hitbox_offsets[6][2] = {
    { 0x4AE, 0x29C },
    { 0x49F, 0x279 },
    { 0x49D, 0x259 },
    { 0x49B, 0x231 },
    { 0x49D, 0x259 },
    { 0x49D, 0x259 },
};

u8 sigma_beam_hitbox_box_data[30][4] = {
    { 0x80, 0xE4, 0x20, 0x41 },
    { 0xA0, 0xE8, 0x20, 0x37 },
    { 0xC0, 0xED, 0x20, 0x2C },
    { 0xE0, 0xF3, 0x20, 0x20 },
    { 0x00, 0xFD, 0x20, 0x15 },
    { 0x20, 0xFA, 0x20, 0x0C },
    { 0x40, 0xFD, 0x20, 0x06 },
    { 0x80, 0x1B, 0x20, 0x38 },
    { 0xA0, 0x17, 0x20, 0x2E },
    { 0xC0, 0x14, 0x20, 0x22 },
    { 0xE0, 0x10, 0x20, 0x18 },
    { 0x00, 0x0C, 0x20, 0x0F },
    { 0x20, 0x07, 0x10, 0x0C },
    { 0x30, 0x05, 0x10, 0x07 },
    { 0x40, 0x02, 0x20, 0x04 },
    { 0x80, 0x34, 0x20, 0x38 },
    { 0xA0, 0x2E, 0x20, 0x29 },
    { 0xC0, 0x28, 0x20, 0x1E },
    { 0xE0, 0x1F, 0x20, 0x14 },
    { 0x00, 0x17, 0x20, 0x0D },
    { 0x20, 0x0E, 0x20, 0x04 },
    { 0x40, 0x02, 0x20, 0x04 },
    { 0xDC, 0x40, 0x4C, 0x10 },
    { 0xF5, 0x30, 0x3D, 0x10 },
    { 0x19, 0x20, 0x24, 0x10 },
    { 0x3C, 0x10, 0x0C, 0x10 },
    { 0x50, 0x02, 0x08, 0x10 },
    { 0x92, 0x5B, 0xE0, 0x30 },
    { 0x60, 0x5B, 0xBD, 0x30 },
    { 0x80, 0xA9, 0x38, 0xE9 },
};

u8 sigma_beam_hitbox_ranges[6][2] = {
    { 22, 4 },
    { 15, 6 },
    { 7, 7 },
    { 0, 6 },
    { 29, 1 },
    { 27, 2 },
};

u8* sigma_beam_hitbox_boxes[30] = {
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

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800AE450(struct ShotObj* self);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800AE450(struct ShotObj* self)
{
    self->unk15 = 0;
    self->unk58.data = NULL;
    self->unk54 = NULL;
    self->unk8C.bytes[0] = sigma_beam_hitbox_ranges[self->unk2][0];
    self->unk8C.bytes[1] = sigma_beam_hitbox_ranges[self->unk2][1];
    self->bg_offset = self->unk7C->bg_offset;
    self->x_pos.u.hi = sigma_beam_hitbox_offsets[self->unk2][0];
    self->y_pos.u.hi = sigma_beam_hitbox_offsets[self->unk2][1];
    self->unk5C = 1;
    self->unk60 = 9;
    self->state = 1;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_57_sigma_beam_hitbox", func_800AE450);
#endif

void sigma_beam_hitbox_pulse(struct ShotObj* self)
{
    u32 i;
    u32 start;

    if (self->unk7C->unk95 != 0) {
        start = self->unk8C.bytes[0];
        for (i = 0; i < self->unk8C.bytes[1] + 1; i++) {
            self->unk50.data = sigma_beam_hitbox_boxes[start++];
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
            self->unk50.data = sigma_beam_hitbox_boxes[start++];
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
