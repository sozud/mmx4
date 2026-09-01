#include "common.h"

// engine_state_3_update_funcs state 0 (load video)
void func_8002E420(struct EngineObj* arg0)
{
    s32 completed;
    u32 i;

    i = 0;
    arg0->stage = 0xD;
    arg0->substage = 0;
    arg0->checkpoint = 0;
    D_80141BE0 = 0;
    i = 0;
    do {
        arg0->character_state.bytes[i] = 0;
        i++;
    } while (i < 0x10);
    arg0->unk1F = 0;
    arg0->enable_boss = 0;
    arg0->unk8 = 0;
    arg0->unkA = 0;
    func_80013014();
    reset_objects();
    func_8002AB20();
    func_80028BF0();
    func_8002771C();
    func_80023CE0();
    D_8013B810 = 0;
    D_8013B814 = 0;
    arg0->unkE = 0;

    switch (arg0->unk5F) {
    case 0:
        arg0->unk1 = 8;
        arg0->unkE = arg0->cur_character;
        break;
    case 1:
    case 2:
        arg0->unkE = 2;
        arg0->unk1 = 8;
        break;
    case 3:
        completed = 0;
        for (i = 0; i < 8; i++)
            if (((u8)arg0->palette_flags >> i) & 1)
                completed++;
        if (completed == 4) {
            if (arg0->cur_character != 0) {
                i = 7;
            } else {
                i = 2;
            }
            arg0->unkE = i;
        }
        arg0->unk1 = 1;
        break;
    case 5:
        if (arg0->cur_character != 0) {
            i = 8;
        } else {
            i = 3;
        }
        arg0->unkE = i;
        arg0->unk1 = 1;
        break;
    case 7:
        if (arg0->cur_character != 0) {
            i = 9;
        } else {
            i = 4;
        }
        arg0->unkE = i;
        arg0->unk1 = 1;
        break;
    case 8:
        if (arg0->cur_character != CHARACTER_X)
            arg0->unk5F = 9;
        arg0->unk1 = 1;
        break;
    case 9:
    case 10:
    default:
        arg0->unk1 = 1;
        break;
    }
    arg0->unk2 = 0;
    arg0->unk3 = 0;
    D_80171EA8 = 0;
}

#ifdef MMX4_PC
void func_8002E5E0(void)
{
    static const u8 palette_rows[8] = { 0, 7, 5, 3, 4, 1, 2, 6 };
    u8 enabled = engine_obj.palette_flags;
    u16* palette = SP_TABLE_28;
    u32 row, color;

    for (row = 0; row < 8; row++) {
        u16* entry = palette + palette_rows[row] * 16;
        if (!((enabled >> row) & 1))
            continue;
        for (color = 0; color < 16; color++) {
            u16 value = entry[color];
            u16 gray = ((value & 0x1f) + ((value >> 5) & 0x1f) + ((value >> 10) & 0x1f)) / 3;
            entry[color] = gray | (gray << 5) | (gray << 10);
        }
    }
}
#else
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E5E0);
#endif

// engine_state_3_update_funcs state 1 (load briefing room)
void func_8002E698(struct EngineObj* arg0)
{
    s8 var_a0;
    s8 var_a1;
    struct MiscObj* temp_v0;
    struct MiscObj* temp_v0_2;

    func_800129A4(8);
    var_a0 = 8;
    if ((u8)arg0->unk5F >= 5) {
        var_a0 = 0x16;
        var_a1 = 0x75;
    } else {
        var_a1 = 0x72;
    }
    func_8001663C(var_a0, var_a1);
    func_8002E5E0();
    temp_v0 = find_free_misc_obj();
    if (temp_v0 != 0) {
        temp_v0->base.active = 0x41;
        temp_v0->base.id = 0xA;
        temp_v0->base.unk2 = 0;
    }
    if (arg0->cur_character == 0) {
        if ((u8)arg0->unk5F < 9) {
            if (arg0->unkE != 0xA) {
                temp_v0_2 = find_free_misc_obj();
                if (temp_v0_2 != 0) {
                    temp_v0_2->base.active = 0x41;
                    temp_v0_2->base.id = 0xA;
                    temp_v0_2->base.unk2 = 1;
                }
            }
        }
    } else {
        if ((u8)arg0->unk5F < 7) {
            if (arg0->unkE != 5) {
                temp_v0_2 = find_free_misc_obj();
                if (temp_v0_2 != 0) {
                    temp_v0_2->base.active = 0x41;
                    temp_v0_2->base.id = 0xA;
                    temp_v0_2->base.unk2 = 1;
                }
            }
        }
    }
    if (arg0->unkE != 0) {
        arg0->unk1 = 9;
    } else {
        arg0->unk1++;
    }
    arg0->unk2 = 0;
}

// engine_state_3_update_funcs state 2
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E7BC);

// engine_state_3_update_funcs state 3
void func_8002E8D4(struct EngineObj* arg0)
{
    struct MiscObj* obj;

    if (arg0->unk3C->state == 2) {
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0xF;
            obj->base.unk2 = 0;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0xF;
            obj->base.unk2 = 1;
        }
        obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->base.active = 0x41;
            obj->base.id = 0xC;
            obj->base.unk2 = 9;
        }
        arg0->unk1++;
    }
}

// engine_state_3_update_funcs state 4 (mission selection)
#ifdef MMX4_PC
void func_8002E994(struct EngineObj* arg0)
{
    u16 direction = D_80166C08 & 0xF000;
    s8 selection = arg0->unk3;
    s8 next = selection;
    int moved = 0;

    if (direction == PADLup || direction == PADLright || direction == PADLdown || direction == PADLleft) {
        if ((D_80166C08 ^ controller_state) & direction) {
            if (arg0->unk8 != 0) {
                arg0->unk8--;
            } else {
                s16 repeats = arg0->unkA++;
                arg0->unk8 = repeats < 3 ? 0x1E : 0xA;
                if (direction == PADLup) {
                    if ((u8)arg0->unk5F >= 5) {
                        if (selection == 8)
                            next = 0;
                        else if (selection >= 4)
                            next = 8;
                    } else if (selection >= 4) {
                        next = selection - 4;
                    }
                } else if (direction == PADLdown) {
                    if ((u8)arg0->unk5F >= 5) {
                        if (selection == 8)
                            next = 4;
                        else if (selection < 4)
                            next = 8;
                    } else if (selection < 4) {
                        next = selection + 4;
                    }
                } else if (direction == PADLright) {
                    if (selection != 8 && (selection & 3) != 3)
                        next = selection + 1;
                } else {
                    if (selection != 8 && (selection & 3) != 0)
                        next = selection - 1;
                }
                moved = next != selection;
            }
        }
    } else {
        arg0->unk8 = 0;
        arg0->unkA = 0;
    }

    if (moved) {
        arg0->unk3 = next;
        func_8001540C(5, 0, 0);
    }

    if (controller_state & (PADstart | PADRdown)) {
        if (arg0->unk3 == 8) {
            if ((u8)arg0->unk5F < 7) {
                arg0->stage = 0xA;
                arg0->unk40 = arg0->cur_character == 0 ? 0x31 : 0x11;
            } else {
                arg0->stage = (u8)arg0->unk5F < 0xA ? 0xB : 0xC;
                arg0->unk40 = 0x11;
            }
            D_8013B814 = 0;
        } else {
            arg0->unk40 = arg0->cur_character == 0 ? 0x31 : 0x11;
            arg0->stage = D_800F474C.stage_order[(u8)arg0->unk3];
            arg0->substage = D_8013B814;
        }
        func_8001540C(5, 1, 0);
        arg0->unk2 = 0;
        arg0->unk1++;
    }
}
#else
INCLUDE_ASM("asm/us/main/nonmatchings/1A5BC", func_8002E994);
#endif

// engine_state_3_update_funcs state 5
void func_8002ED80(struct EngineObj* arg0)
{
    arg0->unk40 = 0;
    arg0->unk2 = 0;
    arg0->unk1++;
}

// engine_state_3_update_funcs state 6
void func_8002ED98(struct EngineObj* arg0)
{
    func_800129F0(8);
    arg0->unk2 = 0;
    arg0->unk1++;
}

// engine_state_3_update_funcs state 7
void func_8002EDD4(struct EngineObj* arg0)
{
    if (*D_80141BDC == 0) {
        func_8001D134();
        reset_objects();
        if (arg0->cur_character == 0) {
            if ((arg0->stage == 0xB) && (arg0->unk5F == 8)) {
                arg0->unkE = 3;
                arg0->unk1 = 8;
                goto block_17;
            }
        }
        if (arg0->cur_character != 0) {
            if ((arg0->unkE == 9) && (arg0->unk5F < 4)) {
                arg0->unkE = 4;
                arg0->unk1 = 8;
            } else if (arg0->cur_character != 0) {
                if (arg0->stage == 9) {
                    arg0->state = 9;
                    arg0->unk1 = 0;
                } else {
                    goto block_12;
                }
            } else {
                goto block_12;
            }
        } else {
        block_12:
            if ((arg0->stage > 8) || (arg0->stage == 0) || ((((u8)arg0->palette_flags >> (arg0->stage - 1)) & 1) != 0)) {
                arg0->unk1 = 0;
                arg0->state = (u8)arg0->state + 1;
            } else {
                arg0->unk1 = 0xB;
            }
        }
    block_17:
        arg0->unk2 = 0;
        arg0->unk3 = 0;
    }
}

// engine_state_3_update_funcs state 8 (play video)
#ifndef MMX4_PC
extern RECT D_800F4768;
extern RECT D_800F4770;
#endif

void func_8002EF14(struct EngineObj* arg0)
{
    s8 next;

#ifdef MMX4_PC
    MoveImage((RECT*)&D_800F474C.route_a_positions, 576, 0);
#else
    MoveImage(&D_800F4768, 576, 0);
#endif
    DrawSync(0);
    func_80018000(D_800F474C.route_b[arg0->unkE]);
#ifdef MMX4_PC
    MoveImage((RECT*)&D_800F474C.route_b_positions, 320, 176);
#else
    MoveImage(&D_800F4770, 320, 176);
#endif
    DrawSync(0);
    switch (arg0->unkE) {
    case 0:
    case 1:
        next = 10;
        if (arg0->unkE != 0) {
            next = 5;
        }
        goto load_archive;
    case 2:
        next = 1;
        if (arg0->cur_character != 0) {
            next = 6;
        }
    load_archive:
        arg0->unkE = next;
        arg0->unk1 = 1;
        func_80013014();
        arg0->unk2 = 0;
        break;
    case 3:
        arg0->unk5F = 9;
        arg0->unk1 = 7;
        arg0->unkE = 0;
        arg0->stage = 0xB;
        arg0->substage = 0;
        func_800129F0(8);
        arg0->unk2 = 0;
        return;
    case 4:
        arg0->stage = 9;
        arg0->unk1 = 7;
        arg0->unkE = 0;
        arg0->unk5F = 4;
        /* fallthrough */
    default:
        arg0->unk2 = 0;
        return;
    }
}

void func_8002F048(void)
{
    struct MiscObj* misc;
    struct EffectObj* effect;

    switch (*D_8013B80C) {
    case 0x0:
        D_8013B80C++;
        return;
    case 0x40:
        D_8013B80C++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->unk1 = 3;
            effect->unk2 = 0;
        }
        misc = find_free_misc_obj();
        D_8013B808 = misc;
        if (misc != NULL) {
            misc->base.active = 0x41;
            D_8013B808->base.id = 0xD;
            D_8013B808->base.unk2 = 1;
        }
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->base.active = 0x41;
            misc->base.id = 0xC;
            misc->base.unk2 = 8;
            misc->ext.ready_text.unk50 = D_8013B808;
            return;
        }
    case 0xFF:
        return;
    default:
        if (*D_8013B80C & 0x40) {
            ZeroObjectState(D_8013B808);
        }
        engine_obj.unk40 = *D_8013B80C & 0x3F;
        D_8013B80C++;
        break;
    }
}

// briefing_room_state_9_update_funcs state 0
void func_8002F1B4(struct EngineObj* arg0)
{
    // if the player presses a button, skip to the bottom
    if (controller_state & (PADRdown | PADstart)) {
        background_objects[0].y_pos.i.hi = 272;
        background_objects[0].unk4C = 1;
    }
    // scroll down
    if (background_objects[0].y_pos.i.hi < 272) {
        background_objects[0].y_pos.i.hi++;
        return;
    }
    arg0->unk2++;
    D_8013B80C = D_800F4834[arg0->unkE - 1];
    func_8002217C(D_800F474C.briefing_sound_ids[arg0->unkE], 0xFF, 0);
}

// briefing_room_state_9_update_funcs state 1
void func_8002F264(struct EngineObj* arg0)
{
    if (abc_object.unkC != 0x80) {
        arg0->unk2++;
        func_8002F048();
    }
}

// briefing_room_state_9_update_funcs state 2
void func_8002F2A0(struct EngineObj* arg0)
{
    s8 temp_v0;
    u8 var_s0;
    struct BaseObj* obj;

    if (abc_object.unkC == 0xFF) {
        arg0->unk2++;
        func_8002F048();
        return;
    } else if (abc_object.unkC == 0) {
        temp_v0 = arg0->unkE - 2;
        switch (temp_v0) {
        case 1:
        case 6:
            arg0->unk5F = 6;
            break;
        case 2:
        case 7:
            arg0->unk5F = 8;
            break;
        case 3:
        case 8:
            arg0->unk1 = 7;
            arg0->unk2 = 0;
            arg0->stage = 0;
            arg0->substage = 0;
            arg0->unk5F = 1;
            func_800129F0(8);
            return;
        case 5:
            arg0->unk1 = 7;
            arg0->unk2 = 0;
            arg0->unkE = 9;
            func_800129F0(8);
            return;
        case 0:
            arg0->unk1 = 7;
            arg0->unk2 = 0;
            arg0->stage = 9;
            arg0->substage = 0;
            func_800129F0(8);
            return;
        }

        obj = (struct BaseObj*)find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0xD;
            obj->unk2 = 0;
        }
        if (arg0->unk5F == 2) {
            arg0->unk1 = 0xA;
        } else {
            arg0->unk1 = 3;
            for (var_s0 = 0; var_s0 < 8; var_s0++) {
                obj = (struct BaseObj*)find_free_quad_obj();
                if (obj != NULL) {
                    obj->active = -0x7F;
                    obj->id = 1;
                    obj->unk2 = var_s0;
                }
            }
            arg0->unk3C = obj;
            if (arg0->unk5F >= 5) {
                arg0->unk3 = 8;
            }
        }
        arg0->unk2 = 0;
        return;
    }
}

// briefing_room_state_9_update_funcs state 3
void func_8002F47C(struct EngineObj* arg0)
{
    if ((abc_object.unkC == 1) || (abc_object.unkC == 0x80)) {
        arg0->unk2--;
        func_8002F048();
    }
}

// engine_state_3_update_funcs state 9 (briefing room)
void func_8002F4C4(struct EngineObj* arg0)
{
    arg0->unk40 = 0;
    briefing_room_state_9_update_funcs[arg0->unk2](arg0);
    func_80022730(&abc_object);
}
