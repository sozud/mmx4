#include "common.h"

void character_select_state_0(struct EngineObj* arg0)
{
    u8 var_v1;

    for (var_v1 = 0; var_v1 < 0x10; var_v1++) {
        arg0->unk26[var_v1] = 0;
    }
    func_8001D134();
    arg0->stage = 14;
    arg0->substage = 1;
    func_80013014();
    func_800160AC();
    reset_objects();
    func_8002AB20();
    func_80028BF0();
    func_8002771C();
    func_80023CE0();
    background_objects[0].unk3 = 0;
    background_objects[1].unk3 = 0;
    background_objects[2].unk3 = 1;
    need_palette_load |= 1;
    func_8001663C(0x1C, 0x70);
    arg0->unk37 = 0;
    func_800129A4(8);
    arg0->cur_character = CHARACTER_X;
    arg0->unk26[3] = 0; // already cleared above?
    arg0->unk2 = 0;
    arg0->unkA = 3;
    arg0->unk1++;
}

void character_select_state_1(struct EngineObj* arg0)
{
    s8 var_s0;
    struct MiscObj* misc;

    if (D_80141BDC[0] == 0) {
        if (arg0->unk2 == 0) {
            arg0->unk2++;
            var_s0 = 0;
            // spawn X, Zero character portraits
            do {
                misc = find_free_misc_obj();
                if (misc != NULL) {
                    misc->base.active = 0x41;
                    misc->base.id = 0x1C;
                    misc->base.unk2 = var_s0; // SelectACharacterUpdate 0, 1
                }
                var_s0 += 1;
            } while (var_s0 < 2U);
        }
        if (arg0->unk26[2] != 0) {
            arg0->unk2 = 0;
            arg0->unk1 = (u8)(arg0->unk1 + 1);
            D_8013E188[0] = -1;
            D_8013E188[1] = -1;
            D_8013E188[2] = -1;
            D_8013E188[3] = -1;
            arg0->unk4 = 2;
        }
    }
}

void character_select_state_2_substate_0(struct EngineObj* arg0)
{
    if (arg0->unk4 != 0) {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
        arg0->unk4--;
    } else {
        arg0->unk2++;
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        D_8013E188[0] = 0;
        D_8013E188[1] = 0;
        D_8013E188[2] = 0;
        D_8013E188[3] = 0;
        need_palette_load |= 1;
    }
}

// state 2 substate 1
void character_select_spawn_objects(struct EngineObj* arg0)
{
    u8 var_s0;
    struct MiscObj* obj;

    var_s0 = 0;
    // spawn SelectACharacterUpdate
    do {
        // spawn upper/lower "PLAYER SELECT" text
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0x1C;
            obj->base.unk2 = var_s0 + 2; // subtype 2,3
        }
        // spawn X, Zero
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0x1C;
            obj->base.unk2 = var_s0 + 7; // subtype 7,8
        }
        // Not sure
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0x1C;
            obj->base.unk2 = var_s0 + 4; // subtype 4,5
        }
        var_s0 += 1;
    } while (var_s0 < 2);
    // spawn green selector
    obj = find_free_misc_obj();
    if (obj != NULL) {
        obj->base.active = 0x41;
        obj->base.id = 0x1C;
        obj->base.unk2 = 6;
    }
    arg0->unk2 = 0;
    arg0->unk1++;
}

void character_select_state_2(struct EngineObj* arg0)
{
    character_select_state_2_update_funcs[arg0->unk2](arg0);
}

extern void (*character_select_state_3_update_funcs[])();

void character_select_state_3(struct EngineObj* arg0)
{
    u16* ptr = &controller_state;
    s8 temp_v1;

    // select X
    if (*ptr & (PADLdown | PADLleft)) {
        arg0->cur_character = CHARACTER_X;
    }
    // select Zero
    if (*ptr & (PADLup | PADLright)) {
        arg0->cur_character = CHARACTER_ZERO;
    }
    temp_v1 = arg0->unk26[3];
    if (temp_v1 == arg0->cur_character) {
        character_select_state_3_update_funcs[temp_v1]();
    } else {
        engine_obj.unk26[4] = 0;
        arg0->unk37 = 0;
    }
    if (controller_state & (PADRdown | PADstart)) {
        arg0->unk26[0] = 1;
        arg0->unk1++;
        func_8001540C(5, 1, 0);
    }
    arg0->unk26[3] = arg0->cur_character;
}

void character_select_state_4(struct EngineObj* arg0)
{
    if (arg0->unk2 == 0) {
        if ((arg0->unk26[1] >> arg0->cur_character) & 1) {
            arg0->unk2++;
            arg0->unk26[1] |= 0x80;
        }
    } else if (!(arg0->unk26[1] & 0x7F)) {
        arg0->unk2 = 0;
        arg0->unk4 = 20; // how long to wait on green background before fading out
        arg0->unk1++;
    }
}

void character_select_state_5(struct EngineObj* arg0)
{
    if (arg0->unk4 == 0) {
        arg0->unk1++;
        func_800129F0(8);
        return;
    }
    arg0->unk4--;
}

void character_select_state_6(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_8001D134();
        background_objects[0].unk3 = 0;
        background_objects[1].unk3 = 0;
        background_objects[2].unk3 = 0;
        reset_objects();
        func_80012EB8();
        arg0->state = 3;
        arg0->unk1 = 0;
        arg0->stage = 0;
        arg0->substage = 0;
    }
}

void engine_state_1(struct EngineObj* arg0)
{
    D_800F44A8[arg0->unk1](arg0);
    func_8002B460();
    update_misc_objects();
    func_8002A484();
    func_80023D68();
}

// character_select_state_3_update_funcs state 0
INCLUDE_ASM("asm/us/main/nonmatchings/character_select", func_80029A48);

// character_select_state_3_update_funcs state 1
INCLUDE_ASM("asm/us/main/nonmatchings/character_select", func_80029BD8);
