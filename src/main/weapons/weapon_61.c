// WeaponObj, weapon_object_update_funcs[61, 62]
// 800992FC..800994A0
#include "common.h"

void func_800992FC(struct WeaponObj* arg0)
{
    D_80108C38[arg0->state](arg0);
}

void func_80099338(struct WeaponObj* arg0)
{
    arg0->state = 1;
    arg0->unk64 = 1;
    arg0->pad58[4] = 1;
    arg0->pad58[8] = 3;
    arg0->on_screen = 0;
    arg0->bg_offset = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = 0;
    arg0->unk50 = 0;
    arg0->unk88.half = 6;
    func_80099388(arg0);
}

void func_80099388(struct WeaponObj* self)
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
    if ((D_80108C28[index] == owner->unk17) && (D_80108C30[index] == owner->unk5) && (owner->state == 1)) {
        event = self->animation_step.fields.event;
        if (event == 0) {
            self->unk50 = NULL;
            return;
        }
        self->unk50 = &D_80108C0C[event];
        return;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void func_80099480(struct WeaponObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 D_80108C0C[7][4] = {
    { 0xFC, 0xFD, 6, 5 },
    { 0xC0, 0xF9, 0x38, 0x1A },
    { 0xB9, 0xCD, 0x31, 0x40 },
    { 0xB1, 0xBF, 0x4A, 0x60 },
    { 0xB9, 0xD4, 0x3E, 0x3F },
    { 0xB1, 0xBF, 0x4A, 0x60 },
    { 0x96, 0xF1, 0x72, 0x29 },
};

u8 D_80108C28[8] = { 8, 9, 0x0A, 0x0B, 0x0F, 0, 0, 0 };

u8 D_80108C30[8] = { 3, 9, 3, 6, 0x0D, 0, 0, 0 };

void (*D_80108C38[])(struct WeaponObj*) = {
    func_80099338,
    func_80099388,
    func_80099480,
};
