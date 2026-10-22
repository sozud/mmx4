// 8001FAFC..800204A4
#include "common.h"
#include "main/102FC.h"
#include "main/10CA4.h"
#include "main/11184.h"
#include "main/13A8C.h"
#include "main/1FD10.h"
#include "main/2824.h"
#include "main/character_select.h"
#include "main/engine.h"
#include "main/engine_dispatch_data.h"
#include "main/objects.h"
#include "main/144A4.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/object_update.h"
#include "main/pause_menu.h"
#include "main/195B4.h"
#include "main/323C.h"
#include "main/background.h"
#include "main/player_common.h"
#include "main/stage_objects.h"
#ifdef MMX4_SATURN
#include "saturn/menu.h"
#endif

extern RECT D_800F2428;
extern RECT D_800F2430;

// D_800F241C
extern void (*D_800F241C[])(struct EngineObj*);

void func_80012F44(void);
s32 func_8001FD7C(struct EngineObj* arg0);
void func_80021158(void);
void func_8002FCAC(void);

void func_80016F0C();

void func_8001F118(void);

struct MiscObj* func_8001F150(struct EngineObj* arg0, u8 arg1);

void func_8001F398(struct EngineObj* arg0);

void func_8001F3D4(struct MainObj* obj);

void func_8001F5D8(struct EngineObj* arg0);

void func_8001F798(struct EngineObj* arg0);

void func_8001F850(struct EngineObj* arg0);

void func_8001F8DC(void);

s32 func_8001F8FC(struct GameInfo* arg0);

void func_8001F93C(struct EngineObj* arg0);

void func_8001F968(struct EngineObj* arg0);

void func_8001F9A0(struct EngineObj* arg0);

void func_8001F9DC(struct EngineObj* arg0);

void func_8001FAC0(struct EngineObj* arg0);

extern void (*D_800F23DC[3])(struct EngineObj*);

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

void func_8001FAFC(struct EngineObj* arg0)
{
#ifdef MMX4_SATURN
    saturn_sprite_reset_queues();
#else
    func_8002B460();
#endif
    D_800F23DC[arg0->unk1](arg0);
    func_8001F118();
}

void func_8001FB50(void)
{
    while (1) {
        s8 state = engine_obj.state;
        engine_update_funcs[state](&engine_obj);
        func_800127C8(1);
    }
}

void engine_state_0(struct EngineObj* arg0)
{
    arg0->player_lives = 2;
    arg0->max_hp = 0x20;
    arg0->state = 1;
}

void engine_state_2(struct EngineObj* arg0)
{
    arg0->state = 3;
}

void engine_state_4(struct EngineObj* arg0)
{
#ifdef MMX4_SATURN_STAGE_BOOT
    extern void saturn_stage_boot_apply(struct EngineObj*);
    saturn_stage_boot_apply(arg0);
#endif
    func_80013014();
    arg0->checkpoint = 0;
    arg0->unk1E = 0;
    D_80171EA8 = 0;
#ifdef MMX4_SATURN_STAGE_BOOT
    {
        extern void saturn_stage_boot_checkpoint(struct EngineObj*);
        saturn_stage_boot_checkpoint(arg0);
    }
#endif
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
    player_spawn();
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
    arg0->gameplay_locked = 1;
    arg0->unkF = 0;

    func_80023CE0();
    func_8001FDBC();
    if (arg0->unk42 != 0) {
        arg0->unk42 = 0;
    } else {
        func_8001FEC0();
    }
#ifdef MMX4_SATURN
    if (arg0->cur_character == CHARACTER_X && arg0->stage == 9) {
        for (var_v1 = 0; var_v1 < 0x20; var_v1++) {
            ((u16*)((u8*)SP_PALETTE + 0xA00))[var_v1] = 0;
        }
        need_palette_load |= 1;
        saturn_display_mode = 11;
    }
#endif
    func_800129A4(8);
    arg0->state++;
}

s32 func_8001FD7C(struct EngineObj* arg0)
{
    if (arg0->stage != 0xC) {
        return 0;
    }
    if (arg0->substage != 0) {
        return 0;
    }
    if (arg0->checkpoint < 2) {
        return 0;
    }
    return arg0->checkpoint <= 9;
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
    if (engine_obj.stage == 0xC && engine_obj.substage == 1 && engine_obj.character_state.bytes[8] == 0 && engine_obj.cur_character != 0) {
        return;
    }
    if (engine_obj.stage == 0xC && engine_obj.checkpoint > 1 && engine_obj.checkpoint < 10) {
        return;
    }
    if (engine_obj.stage == 9) {
        return;
    }
#ifdef MMX4_SATURN
    func_800127C8(8);
    saturn_music_start(engine_obj.stage, 0);
#else
    func_800164D8();
#endif
}

// in a stage
void engine_state_6(struct EngineObj* arg0)
{
    D_800F241C[arg0->unk1](arg0);
}

// D_800F241C state 0
#ifdef MMX4_SATURN
void func_8001FF8C(struct EngineObj* arg0)
{
    if (!arg0->gameplay_locked && !main_bss_state.transition.active && ((saturn_pad_pressed & SATURN_PAD_START) || saturn_pause_request != 0) && !arg0->unk10 && !arg0->unkF) {
        arg0->unk1 = 2;
        func_80023D68();
        saturn_pause_latch = saturn_pause_request;
        return;
    }
    if (g_Player.state == 3) {
        arg0->unk1++;
        func_800129F0(8);
    }
    saturn_sprite_reset_queues();
    get_random();
    func_80021158();
    func_80023D68();
}
#else
void func_8001FF8C(struct EngineObj* arg0)
{
    if (!arg0->gameplay_locked && !main_bss_state.transition.active &&
#ifdef VERSION_EU
        ((controller_input.pressed & PADstart) || D_80166D68 != 0) &&
#else
        ((controller_input.pressed & PADstart)
#ifndef VERSION_JP
            || pad_port1_packet[0] == 0xFF
#endif
            )
        &&
#endif
        !arg0->unk10 && !arg0->unkF) {
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
#endif

// D_800F241C state 1
void func_80020060(struct EngineObj* arg0)
{
    if (main_bss_state.transition.active != 0) {
#ifdef MMX4_SATURN
        saturn_sprite_reset_queues();
#endif
        func_80021158();
        func_80023D68();
    } else {
        func_800200D4(arg0);
#ifdef MMX4_SATURN
        saturn_music_request(3, 0, 0, 0);
        if (arg0->unk42 == 0) {
            saturn_sound_stop_all();
        }
        saturn_stage_commit_video();
#else
        stop_sound(0xFF, 0);
        if (arg0->unk42 == 0) {
            func_80016F0C();
        }
#endif
    }
}

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800200D4(struct EngineObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800200D4(struct EngineObj* arg0)
{
    s32 i;

    if (arg0->unkF > 0) {
        arg0->unk1E = 0;
        if (arg0->stage > 0 && arg0->stage < 9) {
            if (arg0->substage != 0) {
                arg0->state
                    = (((u8)arg0->palette_flags >> (arg0->stage - 1)) & 1)
                    ? 9
                    : 7;
            } else {
                arg0->substage++;
                arg0->state = 4;
            }
        } else if (arg0->substage == 0
            && (arg0->stage >= 0xB || arg0->stage == 0)) {
            if (arg0->stage != 0) {
                arg0->state = 0xA;
            } else {
                arg0->substage = 1;
                arg0->state = 4;
            }
        } else if (arg0->stage == 0xC && arg0->substage == 1) {
            arg0->state = 0xB;
        } else {
            arg0->state = 9;
            switch (arg0->stage) {
            case 0:
                arg0->unk5F = 2;
                break;
            case 9:
                arg0->unk5F = 4;
                break;
            case 0xA:
                arg0->unk5F = 7;
                break;
            case 0xB:
                arg0->unk5F = 0xA;
                break;
            }
        }
    } else if (arg0->unkF < 0) {
        arg0->unk1E = -1;
        func_8002B560(2, 0xE);
        arg0->checkpoint_hp = g_Player.hp;
        for (i = 0; i < 0x10; i++) {
            arg0->player_initial_data[i] = g_Player.weapon_energy[i];
        }
        arg0->unk60 = g_Player.weapon;
        if (arg0->stage != 0xC
            || (arg0->stage == 0xC && arg0->substage == 0 && arg0->checkpoint == 0xA)) {
            arg0->unk42 = 1;
        }
        arg0->state = 5;
    } else {
        arg0->player_lives--;
        if (arg0->player_lives < 0) {
            arg0->state = 8;
            if (arg0->stage == 0xC && arg0->substage == 0) {
                for (i = 0; i < 0x10; i++) {
                    arg0->character_state.bytes[i] = 0;
                }
            }
        } else {
            arg0->unk1E = 0;
            if (func_8001FD7C(arg0) != 0) {
                arg0->checkpoint = 1;
            }
            if (arg0->stage == 0xC && arg0->substage == 1 && D_80171EA8 != 0) {
                arg0->state = 4;
            } else {
                arg0->state = 5;
            }
        }
    }

    arg0->unk1 = 0;
    arg0->unkF = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/102FC", func_800200D4);
#endif
// D_800F241C state 2
void func_80020368(struct EngineObj* arg0)
{
    player_read_input();
    func_8002FCAC();
}

#ifdef MMX4_SATURN
void func_80020390(struct EngineObj* arg0)
{
    s32 i;

    for (i = 0; i < 6; i++) {
        saturn_warm_buffer[0x8A + i] = 0;
    }
    saturn_video_start();
    if (arg0->stage == 0xB && arg0->cur_character != CHARACTER_X) {
        saturn_movie_play("Z3.CPK", 1);
    }
    if (arg0->stage == 0xC && arg0->cur_character != CHARACTER_X) {
        saturn_movie_play("Z4.CPK", 1);
    }
    saturn_video_start();
    func_800129F0(8);
    arg0->unk1++;
}

void func_8002044C(struct EngineObj* arg0)
{
    if (main_bss_state.transition.active == 0) {
        saturn_archive_load_blocking("ASCII.ARC");
        if (arg0->cur_character != 0) {
            saturn_archive_load_blocking("PL01.ARC");
        } else if (arg0->unk37 != 0) {
            saturn_archive_load_blocking("PL02.ARC");
        } else {
            saturn_archive_load_blocking("PL00.ARC");
        }
        arg0->substage = 1;
        arg0->state = 4;
        arg0->unk1 = 0;
    }
}
#else
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
#endif

void func_80020464(struct EngineObj* arg0)
{
    if (arg0->unk1 == 0) {
        func_80020390(arg0);
    } else {
        func_8002044C(arg0);
    }
}
