#include "common.h"

// megaman never appears in stage if nopped out
void MegamanRelatedUpdate(struct MiscObj* arg0)
{
    g_MegamanRelatedUpdateFuncs[arg0->base.state](arg0);
}

// g_MegamanRelatedUpdateFuncs state 0
INCLUDE_ASM("asm/us/main/nonmatchings/ready_text", func_800CB048);

// g_MegamanRelatedUpdateFuncs state 1
void func_800CB1F0(struct MiscObj* arg0)
{
    D_8010E6FC[arg0->base.unk2](arg0); // the animation before ready appears but "READY" doesn't if nopped out
}

// func_800CB22C state 0, 1
// animation leading up to "READY" shows up but "READY" never apprears
// if nopped out
// asm(".rept 18 ; nop ; .endr");
void func_800CB22C(struct MiscObj* arg0)
{
    ReadyTextUpdateFuncs[arg0->base.unk5]();
    is_on_screen(arg0);
}

extern u8 D_8010E6B0[];

// ReadyText State 0
void func_800CB27C(struct MiscObj* arg0)
{
    if (arg0->ext.ready_text.unk50->unk16 != 0) {
        func_800CB5B4(arg0, NULL);
        arg0->base.unk5 = 1;
        arg0->ext.ready_text.unk54 = 8;
        if (arg0->base.unk2 != 0) {
            arg0->unk42 = 0x7840;
            arg0->x_vel.val = FIXED(.25);
            arg0->y_vel.val = FIXED(-.5); // set y velocity of shadow behind "READY"
            return;
        }
        arg0->x_vel.val = FIXED(-.25);
        arg0->y_vel.val = FIXED(.5); // set y velocity of blue "READY"
        func_8001540C(0, 0xA, 0);
        return;
    }
    if ((arg0->base.unk2 == 0) && (arg0->ext.ready_text.palette_cycle_done == 0)) {
        if (arg0->ext.ready_text.unk54 != 0) {
            arg0->ext.ready_text.unk54--;
            return;
        }
        // cycle palette when "READY" first appears
        func_800CB5B4(arg0, D_8010E6B0[arg0->ext.ready_text.palette_pos]);
        arg0->ext.ready_text.palette_pos++;
        if (arg0->ext.ready_text.palette_pos >= 14) {
            arg0->ext.ready_text.palette_pos = 0;
            arg0->ext.ready_text.palette_cycle_done = 1;
        }
    }
}

extern u16 D_8013B940;

// ReadyText State 1
void func_800CB394(struct MiscObj* arg0)
{
    u16* pal_src;
    u16* pal_dst;
    u32 pal_pos;

    if (arg0->ext.ready_text.stay_up_timer != 0) {
        arg0->ext.ready_text.stay_up_timer--;
        return;
    }
    arg0->ext.ready_text.unk54--;
    if (arg0->ext.ready_text.unk54 == 0) {
        if (arg0->base.unk6 == 0) {
            if (arg0->base.unk2 != 0) {
                arg0->x_vel.val = FIXED(-.25);
                arg0->y_vel.val = FIXED(.5);
            } else {
                arg0->x_vel.val = FIXED(.25);
                arg0->y_vel.val = FIXED(-.50);
            }
            arg0->base.unk6 = 1;
            arg0->ext.ready_text.unk54 = 8;
            arg0->ext.ready_text.stay_up_timer = 30; // how long the "READY" text should be in the "up" position
            return;
        }
        arg0->base.unk5 = 2;
        arg0->base.unk6 = 0;
        arg0->unk42 = 0x7801;
        if (arg0->base.unk2 != 0) {
            pal_src = &D_8013B940;
            pal_pos = 0;
            arg0->x_vel.val = FIXED(-16);
            pal_dst = *(s32*)0x1F800028 + 0x200;
            do {
                *pal_dst++ = *pal_src++;
                pal_pos += 1;
            } while (pal_pos < 16);
            need_palette_load |= 1;
        } else {
            arg0->x_vel.val = FIXED(16);
        }
        arg0->base.x_pos.i.hi = 160;
        arg0->base.y_pos.i.hi = 120;
        arg0->y_vel.val = 0;
        engine_obj.unk1E = 1;
        return;
    }
    func_8002B694();
}

// ReadyText State 2
// "READY" never disappears if nopped out
// asm(".rept 26 ; nop ; .endr");
void func_800CB4E4(struct MiscObj* arg0)
{
    if (arg0->base.on_screen != 0) {
        func_8002B694(arg0);
        return;
    }
    arg0->base.state = 2;
    arg0->base.unk5 = 0;
    if ((engine_obj.stage == 5) && (engine_obj.checkpoint == 0)) {
        engine_obj.unk1C = 0;
    }
}

// D_8010E6FC state 2
void func_800CB554(struct MiscObj* arg0)
{
    arg0->base.on_screen = 0;
    if (D_80141BD8.unk0 & 0x10) {
        is_on_screen(arg0);
    }
}

// D_8010E6FC state 3, 4
void func_800CB590(struct MiscObj* arg0)
{
    arg0->base.on_screen = 1;
    is_on_screen(arg0);
}

// "READY" has wrong palette if nopped out
// asm(".rept 22 ; nop ; .endr");
void func_800CB5B4(s32 arg0, s32 arg1)
{
    u16* var_a0;
    u16* var_v1;
    u32 var_a2;

    var_a2 = 0;
    var_a0 = *(s32*)0x1F800024 + ((arg1 + 0x39) << 5);
    var_v1 = *(s32*)0x1F800028 + 0x20;
    do {
        *var_v1++ = *var_a0++;
        var_a2 += 1;
    } while (var_a2 < 0x10);
    need_palette_load |= 1;
}

// g_MegamanRelatedUpdateFuncs state 2
void func_800CB614(struct MiscObj* arg0)
{
    ZeroObjectState(arg0);
}
