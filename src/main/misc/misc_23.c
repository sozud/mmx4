// MiscObj, misc_object_update_funcs[23]
// 800CBD40..800CBECC
#include "common.h"

void func_800CBD40(struct MiscObj* arg0)
{
    if (arg0->base.state == 0) {
        func_800CBD80(arg0);
    } else {
        func_800CBE34(arg0);
    }
}

void func_800CBD80(struct MiscObj* arg0)
{
    arg0->base.on_screen = 1;
    arg0->unk38 = 0;
    arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[2];
    arg0->animation_table = &D_8010A4C0;
    arg0->unk40 = 0;
    if (arg0->ext.unk.unk54 != 2) {
        arg0->unk42 = 0x7805;
    } else {
        arg0->unk42 = 0x7806;
    }
    if (arg0->base.unk7 == 0) {
        arg0->base.unk16 = 1;
    }
    func_80015D60(arg0, arg0->ext.unk.unk54);
    arg0->base.state++;
    arg0->base.unk7 = get_random() & 1;
    is_on_screen(arg0);
}

void func_800CBE34(struct MiscObj* arg0)
{
    func_8002B718(arg0);
    func_80015DC8(arg0);
    if (arg0->unk46 == 0) {
        arg0->x_vel.val = 0;
        arg0->y_vel.val = 0;
        arg0->ext.unk.unk54 = 0;
        ZeroObjectState(arg0);
    } else {
        arg0->base.on_screen = 0;
        if (((arg0->ext.unk.unk54 & 3) && !(arg0->ext.unk.unk54 & 1)) || (D_80141BD8.unk0 & 1) == arg0->base.unk7) {
            is_on_screen(arg0);
        }
    }
}

u32 D_8010A440[7] = {
    0x12010002,
    0x13010002,
    0x14010002,
    0x15010003,
    0x16010004,
    0x17010005,
    0x18000106,
};

u32 D_8010A45C[8] = {
    0x19010004,
    0x1A010004,
    0x1B010004,
    0x1C010005,
    0x1D010006,
    0x1E010007,
    0x1F010007,
    0x20000107,
};

u32 D_8010A47C[17] = {
    0x02010002,
    0x03010002,
    0x04010002,
    0x05010002,
    0x06010002,
    0x07010002,
    0x08010002,
    0x09010002,
    0x0A010002,
    0x0B010002,
    0x0C010002,
    0x0D010003,
    0x0E010003,
    0x0F010004,
    0x10010005,
    0x11010006,
    0x11000160,
};

const u32* D_8010A4C0[3] = {
    D_8010A440,
    D_8010A45C,
    D_8010A47C,
};
