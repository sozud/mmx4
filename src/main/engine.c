// EngineObj
// 8001F118..80021158
#include "common.h"

void func_80016F0C();

void func_8001F118(void)
{
    update_misc_objects();
    func_80021D20();
    func_8002A484();
    func_80023D68();
}

struct MiscObj* func_8001F150(struct EngineObj* arg0, u8 arg1)
{
    struct MiscObj* obj = find_free_misc_obj();

    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x2D;
        obj->unk2 = arg1;
    }
    return obj;
}

INCLUDE_ASM("main/nonmatchings/engine", func_8001F198);

INCLUDE_ASM("main/nonmatchings/engine", func_8001F2BC);

void func_8001F398(struct EngineObj* arg0)
{
    D_800F23B0[arg0->unk2](arg0);
}

void func_8001F3D4(struct MainObj* obj)
{
    s32 background_index;
    u32 i;

    *(s16*)&obj->state = 6;
    background_index = ((s8*)&obj->unk42)[1];
    obj->on_screen = 0;
    obj->unk2++;
    if (background_index == 0) {
        background_objects[0].x_pos.val = FIXED(512);
    } else {
        background_objects[background_index].x_pos.val = FIXED(256);
    }

    for (i = 0; i < 4; i++) {
        D_8013E188[i] = -1;
    }
    g_FilterModeR = 0;
    g_FilterModeG = 0;
    g_FilterModeB = 0;
    g_FilterAmountR = 0;
    g_FilterAmountG = 0;
    g_FilterAmountB = 0;
}

INCLUDE_ASM("main/nonmatchings/engine", func_8001F488);

void func_8001F5D8(struct EngineObj* arg0)
{
    if (!(arg0->unk4 & 1)) {
        g_FilterAmountR = 0x1F;
        g_FilterAmountG = 0x3E0;
        g_FilterAmountB = 0x7C00;
    } else {
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/engine", func_8001F634);

INCLUDE_ASM("main/nonmatchings/engine", func_8001F6E8);

void func_8001F798(struct EngineObj* arg0)
{
    u8 a1;

    if (--arg0->unk4 == 0) {
        g_FilterAmountR = 0;
        g_FilterAmountG = 0;
        g_FilterAmountB = 0;
        arg0->unk3 = 0;
        arg0->unk2++;

        if (arg0->cur_character != 0) {
            *(s16*)&arg0->unk6 = 0x46;
            a1 = 0;
        } else {
            *(s16*)&arg0->unk6 = 0x3C;
            a1 = 0;
        }

        arg0->unk4 = 0xF0;
        func_8001540C(5, a1, 0);
    } else {
        func_8001F5D8(arg0);
    }
    need_palette_load |= 1;
}

void func_8001F850(struct EngineObj* arg0)
{
    if (--arg0->unk4 == 0) {
        ((void (*)(s32, u8, u8))func_8002217C)(
            arg0->character_state.bytes[0] + 0x10, 0x80, 0);
        arg0->unk2++;
    } else if (arg0->unk4 == 0xF0 - *(s16*)&arg0->unk6) {
        func_8001540C(5, (u8)arg0->character_state.bytes[0], 0);
    }
}

void func_8001F8DC(void)
{
    func_80016FB4(3);
}

s32 func_8001F8FC(struct GameInfo* arg0)
{
    if (--arg0->unk6 == 0) {
        func_80016F0C();
        return 0;
    }
    return 1;
}

void func_8001F93C(struct EngineObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->unk4 = 0x3C;
        arg0->unk2 = (u8)arg0->unk2 + 1;
    }
}

void func_8001F968(struct EngineObj* arg0)
{
    func_800129F0(8);
    arg0->unk1 = 2;
    arg0->unk2 = 0;
}

void func_8001F9A0(struct EngineObj* arg0)
{
    D_800F23B8[arg0->unk2](arg0);
}

void func_8001F9DC(struct EngineObj* arg0)
{
    if (*D_80141BDC == 0) {
        func_8001D134();
        arg0->unk2++;
    }
}

INCLUDE_ASM("main/nonmatchings/engine", func_8001FA24);

void func_8001FAC0(struct EngineObj* arg0)
{
    D_800F23D4[arg0->unk2](arg0);
}

void func_8001FAFC(struct EngineObj* arg0)
{
    func_8002B460();
    D_800F23DC[arg0->unk1](arg0);
    func_8001F118();
}

void func_8001FB50(void)
{
    while (1) {
        engine_update_funcs[engine_obj.state](&engine_obj);
        func_800127C8(1);
    }
}

void engine_state_0(struct EngineObj* arg0)
{
    arg0->unk44 = 2;
    arg0->unk46 = 0x20;
    arg0->state = 1;
}

void engine_state_2(struct EngineObj* arg0)
{
    arg0->state = 3;
}

void engine_state_4(struct EngineObj* arg0)
{
    func_80013014();
    arg0->checkpoint = 0;
    arg0->unk1E = 0;
    D_80171EA8 = 0;
    arg0->state = 5;
}

void func_8001FC20(struct EngineObj* arg0)
{
    struct EngineObj* var_v0;
    u32 var_v1;

    if (func_8001FD7C(arg0) != 0 && D_80171EA8 != engine_obj.checkpoint) {
        func_80012F44();
    }

    for (var_v1 = 0; var_v1 < 8; var_v1++) {
        arg0->character_state.bytes[var_v1] = 0;
    }

    abc_object.unkC = 0;
    abc_object.unk10 = 0;

    reset_objects();
    func_8002AB20();
    func_800160AC();
    func_8002771C();
    func_80028BF0();
    func_80027850();
    func_80027D40();
    func_800281E8();
    func_80035240();
    func_80028DB4();
    func_80028F58();

    arg0->unk1F = 0;
    arg0->enable_boss = 0;
    arg0->unk10 = 0;
    arg0->unk11 = 0;
    arg0->unk12 = 0;
    arg0->unk13 = 0;
    arg0->unk14 = 0;
    arg0->unk15 = 0;
    arg0->unk16 = 0;
    arg0->unk17 = 0;
    arg0->unk18 = 0;
    arg0->unk19 = 0;
    arg0->unk1A = 0;
    arg0->unk1C = 1;
    arg0->unkF = 0;

    func_80023CE0();
    func_8001FDBC();
    if (arg0->unk42 != 0) {
        arg0->unk42 = 0;
    } else {
        func_8001FEC0();
    }
    func_800129A4(8);
    arg0->state++;
}

s32 func_8001FD7C(struct EngineObj* arg0)
{
    if (arg0->stage != 0xC) {
        return 0;
    } else if (arg0->substage != 0) {
        return 0;
    } else if (arg0->checkpoint >= 2) {
        return arg0->checkpoint < 0xA;
    }
    return 0;
}

void func_8001FDBC(void)
{
    struct EngineObj* ptr = &engine_obj;
    struct BaseObj* obj;

    if (engine_obj.stage == 5 && engine_obj.checkpoint == 0) {
        engine_obj.unk1E = 1;
        return;
    }
    if (ptr->stage == 0xC && ptr->substage != 0 && ptr->checkpoint == 0) {
        ptr->unk1E = -2;
        if (engine_obj.cur_character != CHARACTER_X) {
            obj = (struct BaseObj*)find_free_misc_obj();
            if (obj != NULL) {
                obj->active = 0x41;
                obj->id = 0x34;
                obj->unk2 = 1;
            }
        }
    } else if (ptr->unk1E == 0) {
        obj = (struct BaseObj*)find_free_effect_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 0x1B;
            return;
        }
        ptr->unk1E = 1;
    }
}

extern void func_800164D8(void);

void func_8001FEC0(void)
{
    if (((ENGINE_STAGE_ID != 0x10C) || (engine_obj.character_state.bytes[8] != 0) || (engine_obj.cur_character == 0)) && ((engine_obj.stage != 0xC) || ((u32)((u8)engine_obj.checkpoint - 2) >= 8U)) && (engine_obj.stage != 9)) {
        func_800164D8();
    }
}

// in a stage
void engine_state_6(struct EngineObj* arg0)
{
    D_800F241C[arg0->unk1](arg0);
}

// D_800F241C state 0
void func_8001FF8C(struct EngineObj* arg0)
{
    if (!arg0->unk1C && !D_80141BDC[0] && ((controller_state & PADstart)
#ifndef VERSION_JP
            || D_80166D68 == 0xFF
#endif
            )
        && !arg0->unk10 && !arg0->unkF) {
        arg0->unk1 = 2;
    } else {
        if (g_Player.state == 3) {
            arg0->unk1++;
            func_800129F0(8);
        }
        get_random(); // ???
        func_80021158();
    }
    func_80023D68();
}

// D_800F241C state 1
void func_80020060(struct EngineObj* arg0)
{
    if (D_80141BDC[0] != 0) {
        func_80021158();
        func_80023D68();
    } else {
        func_800200D4(arg0);
        func_80015930(0xFF, 0);
        if (arg0->unk42 == 0) {
            func_80016F0C();
        }
    }
}

INCLUDE_ASM("main/nonmatchings/engine", func_800200D4);

// D_800F241C state 2
void func_80020368(struct EngineObj* arg0)
{
    func_80035EF0();
    func_8002FCAC();
}

void func_80020390(struct EngineObj* arg0)
{
    MoveImage(&D_800F2428, 0x240, 0);
    DrawSync(0);
    if ((arg0->stage == 0xB) && (arg0->cur_character != CHARACTER_X)) {
        func_80018000(8);
    }
    if ((arg0->stage == 0xC) && (arg0->cur_character != CHARACTER_X)) {
        func_80018000(9);
    }
    MoveImage(&D_800F2430, 0x140, 0xB0);
    DrawSync(0);
    arg0->unk1++;
}

void func_8002044C(struct EngineObj* arg0)
{
    arg0->substage = 1;
    arg0->state = 4;
    arg0->unk1 = 0;
}

void func_80020464(struct EngineObj* arg0)
{
    if (arg0->unk1 == 0) {
        func_80020390(arg0);
    } else {
        func_8002044C(arg0);
    }
}

void func_800204A4(void)
{
}

void func_800204AC(struct EngineObj* arg0)
{
    func_800193D8(arg0);
}

void func_800204CC(s8* arg0, s32 arg1)
{
    if (controller_state & 0x1000) {
        func_8001540C(0, 0xC, 0);
        if (*arg0 == 0) {
            *arg0 = arg1;
        } else {
            *arg0 = *arg0 - 1;
        }
    }
    if (controller_state & 0x4000) {
        func_8001540C(0, 0xC, 0);
        if (*arg0 == arg1) {
            *arg0 = 0;
            return;
        }
        *arg0 = *arg0 + 1;
    }
}

void func_80020580(struct EngineObj* arg0)
{
    s8 next_state;

    func_8001D134();
    D_80141BDF[0] = 0;
    arg0->unk1F = 0;
    arg0->enable_boss = 0;
    func_8001E980(0);
    if (arg0->stage != 0) {
        func_8001C3E8();
    }
    arg0->unk4 = 0x78;
    func_800129A4(8);
    if (arg0->stage == 0) {
        arg0->unk8 = func_8001E850(D_800F231C, 1);
        next_state = arg0->unk1 + 5;
    } else {
        arg0->unk8 = func_8001E850(D_800F2328, 1);
        next_state = arg0->unk1 + 1;
    }
    arg0->unk1 = next_state;
}

void func_80020638(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_800204CC(D_80141BDC + 3, arg0->unk8);
        if (controller_state & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            if (D_80141BDC[3] != 2U) {
                func_800129F0(8);
            }
            arg0->unk1++;
        }
    }
}

void func_800206D0(struct EngineObj* arg0)
{
    s8 temp_v1;

    if (D_80141BDC[0] == 0) {
        switch (D_80141BDF[0]) {
        case 0:
            if (D_80171EA8 != 0) {
                func_800127C8(1);
                func_80013014();
                D_80171EA8 = 0;
            }
            if (engine_obj.unk5A & 0x8000) {
                arg0->unk44 = 4;
            } else {
                arg0->unk44 = 2;
            }
            arg0->checkpoint = 0;
            arg0->unk1E = 0;
            arg0->state = 5;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        case 1:
            if (engine_obj.unk5A & 0x8000) {
                arg0->unk44 = 4;
            } else {
                arg0->unk44 = 2;
            }
            arg0->state = 3;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        case 2:
            temp_v1 = arg0->state;
            arg0->state = 0xC;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            arg0->unk4 = temp_v1;
            break;
        default:
            func_8001DC30();
            func_800127FC();
            break;
        }
    }
}

void func_80020808(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_800204CC(D_80141BDC + 3, arg0->unk8);
        if (controller_state & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            func_800129F0(8);
            arg0->unk1++;
        }
    }
}

void func_8002088C(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        switch (D_80141BDF[0]) {
        case 0:
            if (D_80171EA8 != 0) {
                func_800127C8(1);
                func_80013014();
                D_80171EA8 = 0;
            }

            if (engine_obj.unk5A & 0x8000) {
                arg0->unk44 = 4;
            } else {
                arg0->unk44 = 2;
            }
            arg0->checkpoint = 0;
            arg0->unk1E = 0;
            arg0->state = 5;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        case 1:
            if (engine_obj.unk5A & 0x8000) {
                arg0->unk44 = 4;
            } else {
                arg0->unk44 = 2;
            }
            arg0->state = 3;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        case 2:
        default:
            func_8001DC30();
            func_800127FC();
            break;
        }
    }
}

void func_80020984(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_800204CC(D_80141BDC + 3, arg0->unk8);
        if (controller_state & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            func_800129F0(8);
            arg0->unk1++;
        }
    }
}

void func_80020A08(struct EngineObj* arg0)
{
    s8 var_v0;

    if (D_80141BDC[0] == 0) {
        if (D_80141BDF[0] == 0) {
            if (D_80171EA8 != 0) {
                func_800127C8(1);
                func_80013014();
                D_80171EA8 = 0;
            }

            if (engine_obj.unk5A & 0x8000) {
                arg0->unk44 = 4;
            } else {
                arg0->unk44 = 2;
            }
            arg0->checkpoint = 0;
            arg0->unk1E = 0;
            arg0->state = 5;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
        } else {
            func_8001DC30();
            func_800127FC();
        }
    }
}

void func_80020AC8(struct EngineObj* arg0)
{
    D_800F2438[arg0->unk1](arg0);
    update_misc_objects();
    func_80016124();
    init_objects();
}

void func_80020B1C(struct EngineObj* arg0)
{
    func_8001D134();
    D_80141BDF[0] = 0;
    arg0->unk1F = 0;
    arg0->enable_boss = 0;
    func_8001E980(0);
    func_8001C3E8();
    func_800129A4(8);
    arg0->unk8 = func_8001E850(&D_800F2300, 1);
    arg0->unk1++;
}

void func_80020B8C(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_800204CC(D_80141BDC + 3, arg0->unk8);
        if (controller_state & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            if ((u8)D_80141BDC[3] != 0) {
                func_800129F0(8);
            }
            arg0->unk1++;
        }
    }
}

void func_80020C24(struct EngineObj* arg0)
{
    s8 temp_v1;

    if (D_80141BDC[0] == 0) {
        switch (D_80141BDF[0]) {
        case 0:
            temp_v1 = arg0->state;
            arg0->state = 0xC;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            arg0->unk4 = temp_v1;
            return;
        case 1:
            arg0->state = 3;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            return;
        case 2:
        default:
            func_8001DC30();
            func_800127FC();
            break;
        }
    }
}

void func_80020CB8(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        func_800204CC(D_80141BDC + 3, arg0->unk8); // why not D_80141BDF?
        if (controller_state & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            func_800129F0(8);
            arg0->unk1++;
        }
    }
}

void func_80020D3C(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (D_80141BDF[0] == 0) {
            arg0->state = 3;
            arg0->unk1 = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
        } else {
            func_8001DC30();
            func_800127FC();
        }
    }
}

void func_80020D98(struct EngineObj* arg0)
{
    D_800F2454[arg0->unk1](arg0);
    update_misc_objects();
    func_80016124();
    init_objects();
}

void func_80020DEC(u8* arg0, s16 arg1)
{
    struct UnkObj* obj;

    while (arg0[0] != 0xFF) {
        obj = find_free_unk_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 1;
            obj->unk2 = arg0[0];
            obj->y_pos.i.hi = arg0[1];
            obj->unk7 = arg0[2];
        }
        arg0 += 3;
    }

    obj = find_free_unk_obj();
    if (obj != NULL) {
        obj->active = 1;
        obj->unk2 = -1;
        obj->id = 0;
        obj->link.data = D_800F2490;
        obj->x_pos.i.hi = arg1;
    }
}

void func_80020ED4(struct EngineObj* arg0)
{
    arg0->unk7 = 1;
    arg0->character_state.fields.menu_state = 0;
    func_80029DBC();
    D_80141BDF[0] = 0;
    func_80020DEC(&D_800F2468, 0x40);
    func_8001E980(0);
    func_800129A4(8);
}

void func_80020F24(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (arg0->character_state.fields.menu_state == 0) {
            func_800204CC(D_80141BDC + 3, 1);
            if (controller_state & PAD_CONFIRM) {
                func_8001540C(0, 0x22, 0);
                if ((u8)D_80141BDC[3] == 0) {
                    func_800129F0(8);
                    arg0->unk7 = 2;
                } else {
                    arg0->character_state.fields.menu_state = 1;
                    func_80029DBC();
#ifdef VERSION_JP
                    D_80141BDC[3] = 1;
#else
                    D_80141BDC[3] = 0;
#endif
                    func_80020DEC(&D_800F247C, 0x78);
                }
            }
        } else {
            func_800204CC(D_80141BDC + 3, 1);
            if (controller_state & PAD_CONFIRM) {
                func_8001540C(0, 0x22, 0);
                arg0->character_state.fields.menu_state = 0;
                if ((u8)D_80141BDC[3] ==
#ifdef VERSION_JP
                    0
#else
                    1
#endif
                ) {
                    arg0->unk7 = 0;
                    if (engine_obj.stage != 0 && engine_obj.unk5F >= 3) {
                        func_8001C3E8();
                    }
                    SetDispMask(0);
                    func_8001D134();
                    func_80015284();
                    reset_game_engine();
                    func_8001DC30();
                    func_800127FC();
                } else {
                    func_80029DBC();
                    D_80141BDC[3] = 0;
                    func_80020DEC(&D_800F2468, 0x40);
                    arg0->unk7 = 1;
                }
            }
        }
    }
}

void func_800210B8(struct EngineObj* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unk6++;
        func_80029DBC();
        arg0->unk7 = 0;
        arg0->character_state.fields.menu_state = 0;
    }
}

void func_80021104(struct EngineObj* arg0)
{
    D_800F2498[arg0->unk7](arg0);
    update_unk_objects();
    func_80016124();
    func_80025CDC();
}

void (*D_800F23B0[2])(struct EngineObj*) = {
    func_8001F198,
    func_8001F2BC,
};

void (*D_800F23B8[7])(struct EngineObj*) = {
    func_8001F488,
    func_8001F634,
    func_8001F6E8,
    func_8001F798,
    func_8001F850,
    func_8001F93C,
    func_8001F968,
};

void (*D_800F23D4[2])(struct EngineObj*) = {
    func_8001F9DC,
    func_8001FA24,
};

void (*D_800F23DC[3])(struct EngineObj*) = {
    func_8001F398,
    func_8001F9A0,
    func_8001FAC0,
};

void (*engine_update_funcs[13])(struct EngineObj*) = {
    engine_state_0,
    engine_state_1,
    engine_state_2,
    engine_state_3,
    engine_state_4,
    func_8001FC20,
    engine_state_6,
    func_8001FAFC,
    func_80020AC8,
    func_80020D98,
    func_80020464,
    func_80023A54,
    func_800204AC,
};

void (*D_800F241C[3])(struct EngineObj*) = {
    func_8001FF8C,
    func_80020060,
    func_80020368,
};

RECT D_800F2428 = { 0x140, 0xB0, 0x100, 0x50 };

RECT D_800F2430 = { 0x240, 0, 0x100, 0x50 };

void (*D_800F2438[7])(struct EngineObj*) = {
    func_80020580,
    func_80020638,
    func_800206D0,
    func_80020808,
    func_8002088C,
    func_80020984,
    func_80020A08,
};

void (*D_800F2454[5])(struct EngineObj*) = {
    func_80020B1C,
    func_80020B8C,
    func_80020C24,
    func_80020CB8,
    func_80020D3C,
};

u8 D_800F2468[20] = {
    0x59,
    0x10,
    0x80,
    0x2D,
    0x40,
    0x80,
    0x5B,
    0x70,
    0x00,
    0x5C,
    0x90,
    0x01,
    0x72,
    0xD0,
    0x80,
    0xFF,
    0x00,
    0x80,
    0x00,
    0x00,
};

u8 D_800F247C[20] = {
    0x59,
    0x10,
    0x80,
    0x5A,
    0x40,
    0x80,
    0x51,
    0x70,
    0x00,
    0x52,
    0x90,
    0x01,
    0x72,
    0xD0,
    0x80,
    0xFF,
    0x00,
    0x80,
    0x00,
    0x00,
};

u8 D_800F2490[8] = { 0x70, 0x00, 0x90, 0x01, 0xFF, 0, 0, 0 };

void (*D_800F2498[])(struct EngineObj*) = {
    func_80020ED4,
    func_80020F24,
    func_800210B8,
};
