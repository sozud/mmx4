#include "common.h"

void func_8002F510(struct EngineObj* arg0)
{
    arg0->unk3 = 0;
    arg0->unk2++;
}

void func_8002F524(struct EngineObj* arg0)
{
    struct QuadObj* temp_v0 = find_free_quad_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = -0x7F;
        temp_v0->id = 1;
        temp_v0->unk2 = arg0->unk3 + 0x10;
        arg0->unk3C = temp_v0;
        arg0->unk2++;
    }
}

void func_8002F584(struct EngineObj* arg0)
{
    if (arg0->unk3C->state == 2) {
        func_8002217C(arg0->unk3, 0xFF, 0);
        arg0->unk2++;
    }
}

void func_8002F5E8(struct EngineObj* arg0)
{
    struct BaseObj* obj;

    if (abc_object.unkC == 0) {
        if (++arg0->unk3 < 8) {
            arg0->unk2 = 1;
            return;
        }
        arg0->unk5F = 3;
        arg0->unk1 = 4;
        arg0->unk2 = 0;
        arg0->unk3 = 0;
        obj = (struct BaseObj*)find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0xF;
            obj->unk2 = 0;
        }
        obj = (struct BaseObj*)find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0xF;
            obj->unk2 = 1;
        }
    }
}

// engine_state_3_update_funcs state 10
void func_8002F698(struct EngineObj* arg0)
{
    D_800F486C[arg0->unk2](arg0);
    func_80022730(&abc_object);
}

void func_8002F6E4(struct EngineObj* arg0)
{
    D_8013B810 = arg0->stage;
    D_8013B814 = arg0->substage;
    arg0->stage = 0xD;
    arg0->substage = 1;
    arg0->unk40 = D_8013B810;
    func_80013014();
    reset_objects();
    func_8002AB20();
    func_80028BF0();
    func_8002771C();
    func_80023CE0();
    background_objects[1].unk4C = 1;
    background_objects[1].x_pos.val = FIXED((D_8013B810 - 1) << 9);
    background_objects[2].x_pos.val = FIXED((D_8013B810 - 1) << 9);
    arg0->unk2++;
}

void func_8002F7A8(struct EngineObj* arg0)
{
    struct BaseObj* obj = (struct BaseObj*)find_free_misc_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x32;
        obj->x_pos.i.hi = 0x100;
        obj->y_pos.i.hi = 0x70;
        obj->unk2 = D_8013B810;
    }
    background_objects[2].unk4C = 1;
    func_800129A4(8);
    arg0->unk2++;
}

void func_8002F828(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unk2++;
        arg0->unk4 = 0x10;
        func_8001663C(D_8013B810 + 0x4F, 0x7F);
    }
}

void func_8002F87C(struct EngineObj* arg0)
{
    if (D_80173C84 == 2) {
        background_objects[1].y_pos.val -= FIXED(8 + 1.0 / 16);
        background_objects[2].y_pos.val += FIXED(8 + 1.0 / 16);
        if (background_objects[1].y_pos.val < 0) {
            background_objects[1].y_pos.val = 0;
            background_objects[2].y_pos.val = FIXED(256);
            arg0->unk4 = 0x1E;
            arg0->unk2++;
        }
    }
}

void func_8002F8F8(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        arg0->unk4 = 0x96;
        arg0->unk2++;
    }
}

void func_8002F92C(struct EngineObj* arg0)
{
    struct BaseObj* obj;
    if (--arg0->unk4 != 0) {
        if (!(func_8002B780() & 1)) {
            obj = (struct BaseObj*)find_free_quad_obj();
            if (obj != NULL) {
                obj->active = 1;
                obj->id = 6;
                obj->x_pos.i.hi = 0x9C0;
                obj->y_pos.i.hi = 0x70;
            }
        }
    } else {
        obj = (struct BaseObj*)find_free_effect_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 2;
            obj->unk2 = 0xC;
        }
        arg0->unk2++;
    }
}

void func_8002F9EC(struct EngineObj* arg0)
{
    struct BaseObj* obj;
    u32 var_a0;

    if (g_FilterAmountR == 0x1F) {
        func_8002B560(2, 0xC);
        for (var_a0 = 0; var_a0 < 4; var_a0++) {
            D_8013E188[var_a0] = 0;
        }
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        need_palette_load |= 1;
        obj = (struct BaseObj*)find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x32;
            obj->unk2 = 0;
        }
        arg0->unk4 = 0x78;
        arg0->unk2++;
    }
}

void func_8002FAB0(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        arg0->unk4 = 0x12C;
        arg0->unk2++;
    }
}

void func_8002FAE4(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        func_800129F0(8);
        arg0->unk2++;
    }
    background_objects[0].x_pos.val += FIXED(-6);
}

void func_8002FB54(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_8001D134();
        arg0->stage = D_8013B810;
        arg0->substage = D_8013B814;
        arg0->unk1 = 0;
        arg0->unk2 = 0;
        arg0->unk3 = 0;
        arg0->state++;
    } else {
        background_objects[0].x_pos.val += FIXED(-6);
    }
}

// engine_state_3_update_funcs state 11
void func_8002FBDC(struct EngineObj* arg0)
{
    background_objects[0].unk14.val = background_objects[0].x_pos.val;
    background_objects[0].unk18.val = background_objects[0].y_pos.val;
    D_800F487C[arg0->unk2](arg0);
}

// videos / loading / briefing room
void engine_state_3(struct EngineObj* arg0)
{
    func_8002B460();
    engine_state_3_update_funcs[arg0->unk1](arg0);
    update_effect_objects();
    update_misc_objects();
    update_quad_objects();
    func_8002A484();
    func_80023D68();
}

void func_8002FCAC(void)
{
    struct BarObj* bar = &bar_object;
    D_800F48D4[bar_object.state](bar);
}

void func_8002FCEC(struct BarObj* arg0)
{
    D_800F48E0[arg0->unk5](arg0);
}

void func_8002FD28(struct BarObj* arg0)
{
    func_80015930(0xFF, 0);
    func_800129F0(8);
    func_80023D68();
    arg0->unk5 = 1;
}

INCLUDE_ASM("asm/us/main/nonmatchings/1FD10", func_8002FD70);

void func_800300AC(struct BarObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->state = 1;
        arg0->unk5 = 0;
        if (g_Player.base.unk2 || arg0->unk2) {
            if (arg0->unk14 >= 0xD) {
                arg0->unk5 = 2;
            } else {
                arg0->unk5 = 1;
            }
        }
    }
    func_80023D90();
}

void func_80030128(struct BarObj* arg0)
{
    if (controller_state & PADselect) {
        if (arg0->unk5 < 3) {
            arg0->unk28 = arg0->unk5;
            arg0->unk5 = 6;
            arg0->unk6 = 0;
        }
    }
    D_800F48F4[arg0->unk5](arg0);
    if (arg0->unk5 < 5) {
        func_80023D90();
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1FD10", func_800301BC);

INCLUDE_ASM("asm/us/main/nonmatchings/1FD10", func_800304E4);

INCLUDE_ASM("asm/us/main/nonmatchings/1FD10", func_80030728);

INCLUDE_ASM("asm/us/main/nonmatchings/1FD10", func_80030A2C);

INCLUDE_ASM("asm/us/main/nonmatchings/1FD10", func_80030C54);

INCLUDE_ASM("asm/us/main/nonmatchings/1FD10", func_80030DF8);

INCLUDE_ASM("asm/us/main/nonmatchings/1FD10", func_80030EC8);

void func_80030F9C(struct BarObj* arg0)
{
    D_800F4910[arg0->unk5](arg0);
}

void func_80030FD8(struct BarObj* arg0)
{
    func_800129F0(8);
    func_80023D90();
    arg0->unk5 = 1;
}

void func_80031014(struct BarObj* arg0)
{
    if (D_80141BDC[0] != 0) {
        func_80023D90();
    } else {
        func_800170E0();
        arg0->unk5 = 2;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1FD10", func_80031064);

void func_80031130(struct BarObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (arg0->unk30 == 0) {
            engine_obj.unk1 = 0;
            arg0->state = 0;
        } else {
            engine_obj.state = 9;
            engine_obj.unk1 = 0;
            engine_obj.unk2 = 0;
            engine_obj.unk10 = 0;
            engine_obj.unk11 = 0;
            engine_obj.unk12 = 0;
            engine_obj.unk13 = 0;
            engine_obj.unk14 = 0;
            engine_obj.unk15 = 0;
            engine_obj.unk16 = 0;
            engine_obj.unk17 = 0;
            arg0->state = 0;
        }
        arg0->unk5 = 0;
    }
    if (arg0->unk30 == 0) {
        func_80023D68();
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/1FD10", func_800311EC);
