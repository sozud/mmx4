#include "common.h"

extern s32 D_8010EC00[];
extern s32* D_8010E81C[];

// TitleLogoUpdate state 0
void func_800CD78C(struct MiscObj* arg0)
{
    arg0->unk3C = *(s32**)0x1F80003C;
    arg0->unk40 = 0x600;
    arg0->unk30 = &D_8010E81C;
    arg0->base.bg_offset = -1;
    arg0->base.unk15 = 0;

    if (arg0->base.unk2 < 0x20) {
        arg0->unk42 = 0x7804;
        arg0->unk47 = 0x1C;
        if (!(arg0->base.unk2 & 0x10)) {
            arg0->base.y_pos.val = FIXED(240);
            arg0->x_vel.val = FIXED(8);
            arg0->y_vel.val = FIXED(6);
            arg0->base.x_pos.val = 0;
            arg0->ext.title_logo.palette_shift_speed = D_8010EC00[arg0->base.unk2];
            arg0->base.unk16 = 0;
            arg0->base.state++;
        } else {
            arg0->base.unk16 = 1;
            arg0->base.state = 4;
            arg0->ext.title_logo.palette_shift_speed = 6;
        }
        return;
    }
    arg0->unk42 = 0x7840;
    if (arg0->base.unk2 == 0x20) {
        func_80015D60(arg0, 0);
        arg0->base.x_pos.i.hi = 144; // set x pos of "MEGAMAN" while it's fading from white
        arg0->base.y_pos.i.hi = 72;
        arg0->base.state = 5;
    } else if (arg0->base.unk2 == 0x21) {
        func_80015D60(arg0, 1);
        arg0->base.x_pos.i.hi = 208; // set x pos of "sparkle" effect
        arg0->base.y_pos.i.hi = 72;
        arg0->base.state = 7;
    } else {
        arg0->unk42 = 0x7804;
        arg0->base.x_pos.i.hi = 216;
        arg0->base.y_pos.i.hi = 72;
        arg0->base.state = 3;
        arg0->base.unk16 = 0;
        arg0->unk47 = 0x1C;
        arg0->base.unk2 = 0;
    }
    is_on_screen(arg0);
}

// TitleLogoUpdate state 1
void func_800CD90C(struct MiscObj* arg0)
{
    if (arg0->ext.title_logo.palette_shift_speed != 0) {
        arg0->ext.title_logo.palette_shift_speed--;
    } else {
        arg0->ext.title_logo.palette_shift_value = func_8002B7B0(arg0, FIXED(216), FIXED(72));
        arg0->ext.title_logo.palette_shift_speed = 3;
        arg0->ext.title_logo.unk50 = NULL;
        arg0->base.state++;
    }
}

// TitleLogoUpdate state 2
void func_800CD974(struct MiscObj* arg0)
{
    struct MiscObj* obj;
    u8 temp_v0 = func_8002B7B0(arg0, FIXED(216), FIXED(72));
    if ((arg0->ext.title_logo.palette_shift_value ^ temp_v0) & 0x10) {
        arg0->base.x_pos.i.hi = 0xD8;
        arg0->base.y_pos.i.hi = 0x48;
        is_on_screen(arg0);
        arg0->base.unk16 = 2;
        arg0->base.state++;
    } else {
        if (arg0->ext.title_logo.palette_shift_speed == 0) {
            obj = func_8002AE90(arg0->ext.title_logo.unk50, 0);
            if (obj != NULL) {
                obj->base.active = 1;
                obj->base.id = 0x1D;
                obj->base.unk2 = 0x10;
                obj->base.x_pos.val = arg0->base.x_pos.val;
                obj->base.y_pos.val = arg0->base.y_pos.val;
                arg0->ext.title_logo.unk50 = obj;
            }
            arg0->ext.title_logo.palette_shift_speed = 3;
        } else {
            arg0->ext.title_logo.palette_shift_speed--;
        }
        func_8002B93C(arg0, temp_v0);
        arg0->x_vel.val *= 10;
        arg0->y_vel.val *= 8;
        func_8002B718(arg0);
        is_on_screen(arg0);
    }
}

// TitleLogoUpdate state 3
void func_800CDA90(struct MiscObj* arg0)
{
    if (arg0->base.unk2 == 0) {
        is_on_screen(arg0);
    } else {
        ZeroObjectState(arg0);
    }
}

// TitleLogoUpdate state 4
void func_800CDAD0(struct MiscObj* arg0)
{
    if (arg0->ext.title_logo.palette_shift_speed != 0) {
        arg0->ext.title_logo.palette_shift_speed--;
        is_on_screen(arg0);
    } else {
        ZeroObjectState(arg0);
    }
}

// TitleLogoUpdate state 5
void func_800CDB10(struct MiscObj* arg0)
{
    func_80015DC8();
    // transition "MEGAMAN" to white before full logo appears
    if (arg0->unk46 == 0) {
        arg0->ext.title_logo.palette2 = (s32)(*(s32*)SP_PALETTE_ADDR + 0x200);
        arg0->ext.title_logo.palette1 = (s32) * (s32*)0x1F800030;
        // interval to shift on
        arg0->ext.title_logo.palette_shift_speed = 2;
        // how much to shift each step
        arg0->ext.title_logo.palette_shift_value = 0xF;
        arg0->base.state++;
    }
    is_on_screen(arg0);
}

// TitleLogoUpdate state 6
void func_800CDB84(struct MiscObj* arg0)
{
    s32* src;
    s32* dst;
    u32 i;

    if (--arg0->ext.title_logo.palette_shift_speed == 0) {
        arg0->ext.title_logo.palette_shift_speed = 2;
        if (--arg0->ext.title_logo.palette_shift_value) {
            src = arg0->ext.title_logo.palette1;
            dst = arg0->ext.title_logo.palette2;
            for (i = 0; i < 16; i++) {
                *dst++ = *src++;
            }
            need_palette_load |= 1;
            arg0->ext.title_logo.palette1 += 0x40;
        } else {
            arg0->base.id = 0x13;
            arg0->base.unk2 = 0;
            arg0->base.state = 0;
        }
    }
    is_on_screen(arg0);
}

// TitleLogoUpdate state 7
void func_800CDC34(struct MiscObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->unk46 == 0) {
        ZeroObjectState(arg0);
    } else {
        is_on_screen(arg0);
    }
}

// part of the title logo animation
void TitleLogoUpdate(struct MiscObj* arg0)
{
    arg0->base.on_screen = 0;
    g_TitleLogoUpdateFuncs[arg0->base.state](arg0);
}
