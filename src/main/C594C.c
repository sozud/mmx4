#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D514C);

void func_800D5210(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D5230(struct QuadObj* arg0)
{
    D_8010F898[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D526C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D52F4);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D54A0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D54E0);

void func_800D5500(struct QuadObj* arg0)
{
    D_8010F9A4[arg0->state](arg0);
}

void func_800D553C(struct QuadObj* arg0)
{
    D_8010FAD4[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5578);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D55E4);

void func_800D56A8(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D56C8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D57A8);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5934);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5AB0);

void func_800D5BF8(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D5C18(struct QuadObj* arg0)
{
    D_8010FAE0[arg0->state](arg0);
}

// QuadObj #7
// megaman never appears in intro stage if nopped out
void func_800D5C54(struct QuadObj* arg0)
{
    D_8010FC84[arg0->state](arg0);
}

// D_8010FC84 state 0
void func_800D5C90(struct QuadObj* arg0)
{
    arg0->active |= 0x92;
    if (arg0->unk2 == 0) {
        arg0->unk36 = 0x10;
    } else {
        arg0->unk36 = 0x13;
    }
    arg0->unk34 = 5;
    arg0->state = 1;
    arg0->bg_offset = -1;
    arg0->x_pos.val = 0;
    arg0->y_pos.val = 0;
    arg0->unk14.val = 0;
    arg0->unk18.val = 0;
    arg0->unk1C.val = 0;
    arg0->unk20.val = 0;
    arg0->unk24.val = 0;
    arg0->unk28.val = 0;
    arg0->unk2C.val = 0;
    arg0->unk30.val = 0;
}

// D_8010FC84 state 1
// "READY" never appears if noppped out
//  asm(".rept 20 ; nop ; .endr");
void func_800D5CF8(struct QuadObj* arg0)
{
    D_8010FC90[arg0->unk2](arg0);
    arg0->on_screen = 1;
    func_8002B458(arg0);
}

extern u16 D_8010FAEC;

// D_8010FC90 state 0
void func_800D5D50(struct QuadObj* arg0)
{
    u16* verts;
    struct BaseObj* temp_s1;
    struct MiscObj* misc_obj;
    switch (arg0->unk5) {
    case 0:
        arg0->unk5 = 1;
        // set position of blue line that goes left to right before
        // ready text appears
        arg0->x_pos.i.hi = -320;
        arg0->y_pos.i.hi = 112;
        verts = &D_8010FAEC;
        arg0->unk14.i.hi = *verts++;
        arg0->unk18.i.hi = *verts++;
        arg0->unk1C.i.hi = *verts++;
        arg0->unk20.i.hi = *verts++;
        arg0->unk24.i.hi = *verts++;
        arg0->unk28.i.hi = *verts++;
        arg0->unk2C.i.hi = *verts++;
        arg0->unk30.i.hi = *verts;
        arg0->unk38.val = 0x200000;
        arg0->unk3C = 0;
        arg0->unk40.val = 0;
        arg0->unk44 = 0;
        func_800D6494(arg0);
        return;
    case 1:
        temp_s1 = arg0->unk58;
        // spawn "READY" text and shadow when blue line reaches center of screen
        if ((arg0->x_pos.i.hi >= 0 && arg0->x_pos.i.hi < 3) && (temp_s1->unk15 == 0)) {
            misc_obj = find_free_misc_obj();
            if (misc_obj != NULL) {
                misc_obj->base.active = 1;
                misc_obj->base.id = 0x13;
                misc_obj->base.unk2 = 0;
                temp_s1->unk15 = 0;
                misc_obj->ext.ready_text.unk50 = (void*)arg0->unk58;
            }
            misc_obj = find_free_misc_obj();
            if (misc_obj != NULL) {
                misc_obj->base.active = 1;
                misc_obj->base.id = 0x12;
                misc_obj->base.unk2 = 1;
                temp_s1->unk15 = 0;
                misc_obj->ext.ready_text.unk50 = (void*)arg0->unk58;
            }
        }
        if (arg0->x_pos.i.hi >= 320) {
            arg0->unk5 = 2;
            return;
        }
        func_800D6494(arg0);
        return;
    case 2:
        temp_s1 = arg0->unk58;
        temp_s1->bg_offset = 0;
        arg0->state = 2;
        arg0->unk5 = 0;
        return;
    }
}

// D_8010FC90 state 1
INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D5F1C);

// D_8010FC90 state 2
INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6260);

void func_800D6494(struct Unk22* arg0)
{
    arg0->unk8 += arg0->unk38;
    arg0->unkC += arg0->unk3C;
    arg0->unk38 += arg0->unk40;
    arg0->unk3C += arg0->unk44;
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D64D8);

// D_8010FC84 state 2
void func_800D666C(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D668C(void)
{
}

void func_800D6694(struct QuadObj* arg0)
{
    arg0->unk34 = 3;
    *(s32*)&arg0->unk38 = FIXED(4);
    arg0->unk36 = 0;
    arg0->bg_offset = 0;
    arg0->unk14.val = 0;
    arg0->unk18.val = 0;
    arg0->unk1C.val = 0;
    arg0->unk20.val = 0;
    arg0->unk24.val = 0;
    arg0->unk28.val = 0;
    arg0->unk2C.val = 0;
    arg0->unk30.val = 0;
    arg0->active |= 0x82;
    arg0->state++;
    quad_is_on_screen(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6700);

void func_800D6780(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

// QuadObj #8
void func_800D67A0(struct QuadObj* arg0)
{
    D_8010FCAC[arg0->state](arg0);
}

void func_800D67DC(struct QuadObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    struct Unk* temp_a2 = arg0->unk5C;
    s32 var_a3 = 0;
    if (g_Player.unkC3 != 0) {
        var_a3 = 1;
    }
    if (g_Player.unkC4 != 0) {
        var_a3 = 1;
    }
    if (g_Player.unk93 != 6) {
        var_a3 = 1;
    }
    if (g_Player.unk5C == 0) {
        var_a3 = 1;
    }
    if (g_Player.unkBF != 0) {
        var_a3 = 1;
    }
    if (arg0->unk5C->base.active == 0) {
        var_a3 = 1;
    }
    if (arg0->unk5C->unk5C == 0) {
        var_a3 = 1;
    }
    if (var_a3 != 0) {
        ZeroObjectState(arg0);
        return;
    }
    if (arg0->state == 0) {
        func_800D68D0(arg0, ptr, temp_a2);
        return;
    }
    func_800D6944(arg0, ptr);
}

void func_800D68D0(struct QuadObj* arg0, struct PlayerObj* arg1, struct Unk* arg2)
{
    arg0->active = -0x7D;
    arg0->on_screen = 1;
    arg0->bg_offset = arg1->base.bg_offset;
    arg0->unk36 = 1;
    *(s8*)&arg0->unk38 = 0x3C;
    arg0->unk34 = arg0->unk2 + 0xD;
    func_800D69A8(arg0, arg1, arg2);
    arg0->state++;
}

void func_800D6944(struct QuadObj* arg0, struct PlayerObj* arg1)
{
    if (*(u8*)&arg0->unk38 == 0) {
        ZeroObjectState(arg0);
        return;
    }
    if (*(u8*)&arg0->unk38 & 2) {
        arg0->on_screen ^= 1;
    }
    *(u8*)&arg0->unk38 -= 1;
    func_800D69A8(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D69A8);

void func_800D6AD8(struct QuadObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    void* temp_a2 = arg0->unk5C;
    s32 var_a1 = 0;
    if (g_Player.unkC3 != 0) {
        var_a1 = 1;
    }
    if (g_Player.unkC4 != 0) {
        var_a1 = 1;
    }
    if (g_Player.unk93 != 6) {
        var_a1 = 1;
    }
    if (g_Player.unk5C == 0) {
        var_a1 = 1;
    }
    if (g_Player.unkBF != 0) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        ZeroObjectState(arg0);
        return;
    }
    D_8010FCB8[arg0->state](arg0, ptr, temp_a2);
}

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6B9C);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6C48);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6CA0);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6D48);

INCLUDE_ASM("asm/us/main/nonmatchings/C594C", func_800D6DC4);
