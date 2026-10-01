// GameInfo
// 8001D064..8001DC7C
#include "common.h"

#ifdef MMX4_PC
#include <psyz/audio.h>
#include <psyz/spu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
extern union TitleScratch D_80169498;
void func_80016F0C();
extern u8 D_80171EA9;
void func_800153D4(u8 arg0);

#ifdef MMX4_PC
static u8 direct_u8(const char* name)
{
    const char* value = getenv(name);
    return value == NULL ? 0 : (u8)strtoul(value, NULL, 0);
}

static void apply_direct_progress(u8 stage, u8 character, u8 loadout, u8 story)
{
    engine_obj.unk5F = story;
    if (loadout != 1 && loadout != 2)
        return;
    engine_obj.unk44 = 4;
    engine_obj.unk45 = 0x30;
    engine_obj.unk46 = 0x30;
    engine_obj.palette_flags = 0xFF;
    if (loadout == 2 && stage >= 1 && stage <= 8)
        engine_obj.palette_flags &= (u8) ~(1 << (stage - 1));
    engine_obj.unk5A = 0xF0FF;
    engine_obj.unk5C[0] = 0xA0;
    engine_obj.unk5C[1] = 0xA0;
    engine_obj.unk5C[2] = 0x20;
    if (character == CHARACTER_X) {
        engine_obj.unk47 = 0x0F;
        engine_obj.unk48 = 2;
    }
}
#endif

void func_8001D064(void)
{
    s32 var_v1;
    s8* var_a0;
    s8 fill;

    SetDispMask(0);
    func_8001D104();
    func_80012E38();
    func_8001512C();
#ifdef MMX4_PC
    {
        extern s32 mmx4_pc_sfx_group;
        extern u32 mmx4_pc_sfx_index;
        extern const char* mmx4_pc_sfx_raw;
        extern u32 mmx4_pc_sfx_frames;
        if (mmx4_pc_sfx_group >= 0) {
            FILE* output;
            s16* samples;
            s32 result;
            u32 frame;

            D_80173C80 = MAIN_ARCHIVE_ARENA;
            reset_game_engine();
            engine_obj.stage = 0xE;
            engine_obj.substage = 0;
            engine_obj.cur_character = CHARACTER_X;
            func_80013014();
            func_800160AC();
            engine_obj.substage = 1;
            func_80013014();
            func_800160AC();
            if (mmx4_pc_sfx_group != 5)
                func_80012EB8();
            result = func_8001540C(
                mmx4_pc_sfx_group, mmx4_pc_sfx_index, NULL);
            fprintf(stderr,
                "MMX4 SFX fixture: group=%d index=%u result=%d\n",
                mmx4_pc_sfx_group, mmx4_pc_sfx_index, result);
            if (mmx4_pc_sfx_raw == NULL)
                return;

            output = fopen(mmx4_pc_sfx_raw, "wb");
            samples = malloc(735 * 2 * sizeof(*samples));
            if (output == NULL || samples == NULL) {
                free(samples);
                if (output != NULL)
                    fclose(output);
                fprintf(stderr, "MMX4 SFX fixture: cannot open %s\n",
                    mmx4_pc_sfx_raw);
                exit(EXIT_FAILURE);
            }
            for (frame = 0; frame < mmx4_pc_sfx_frames; frame++) {
                VSync(0);
                Psyz_SpuPullSamples(samples, 735);
                if (fwrite(samples, 735 * 2 * sizeof(*samples), 1, output) != 1) {
                    fprintf(stderr, "MMX4 SFX fixture: write failed for %s\n",
                        mmx4_pc_sfx_raw);
                    free(samples);
                    fclose(output);
                    exit(EXIT_FAILURE);
                }
            }
            free(samples);
            fclose(output);
            fprintf(stderr, "MMX4 SFX fixture: rendered %u frames to %s\n",
                mmx4_pc_sfx_frames, mmx4_pc_sfx_raw);
            exit(EXIT_SUCCESS);
        }
    }
#endif
    PlayCapcomLogo();
    fill = 0;
    var_a0 = (s8*)&game_info;
    var_v1 = sizeof(game_info);
    while (var_v1-- != 0) {
        *var_a0++ = fill;
    }
    D_8013BD44 = 1;
    game_info.unk0 = 0;
    game_info.mode = 0;
    game_info.unk2 = 0;
    game_info.unk3 = 0;
#ifdef MMX4_PC
    {
        const char* scene = getenv("MMX4_ORACLE_SCENE");
        int character_select = scene != NULL && strcmp(scene, "character-select") == 0;
        int mission_briefing = scene != NULL && strcmp(scene, "mission-briefing") == 0;
        int initial_stage = scene != NULL && strcmp(scene, "initial-stage") == 0;

        if (character_select) {
            D_80173C80 = MAIN_ARCHIVE_ARENA;
            reset_game_engine();
            engine_obj.state = 1;
            engine_update_funcs[engine_obj.state](&engine_obj);
            func_800128B8(func_8001FB50);
            return;
        }
        if (mission_briefing) {
            u8 stage = direct_u8("MMX4_DIRECT_STAGE");
            u8 character = direct_u8("MMX4_DIRECT_CHARACTER");
            u8 loadout = direct_u8("MMX4_DIRECT_LOADOUT");
            u8 story = direct_u8("MMX4_DIRECT_STORY");

            D_80173C80 = MAIN_ARCHIVE_ARENA;
            reset_game_engine();
            engine_obj.stage = 0xE;
            engine_obj.substage = 0;
            engine_obj.cur_character = character;
            func_80013014();
            func_800160AC();
            engine_obj.substage = 1;
            func_80013014();
            func_800160AC();
            func_80012EB8();
            reset_game_engine();
            engine_obj.state = 3;
            engine_obj.stage = 0;
            engine_obj.substage = 0;
            engine_obj.cur_character = character;
            apply_direct_progress(stage, character, loadout, story);
            if (loadout == 2)
                engine_obj.palette_flags = 0;
            engine_update_funcs[engine_obj.state](&engine_obj);
            func_800128B8(func_8001FB50);
            return;
        }
        if (initial_stage) {
            u8 stage = 0;
            u8 substage = 0;
            u8 checkpoint = 0;
            u8 character = 0;
            u8 loadout = 0;
            u8 story = 0;
            const char* value;

            value = getenv("MMX4_DIRECT_STAGE");
            if (value != NULL)
                stage = (u8)strtoul(value, NULL, 0);
            value = getenv("MMX4_DIRECT_SUBSTAGE");
            if (value != NULL)
                substage = (u8)strtoul(value, NULL, 0);
            value = getenv("MMX4_DIRECT_CHECKPOINT");
            if (value != NULL)
                checkpoint = (u8)strtoul(value, NULL, 0);
            value = getenv("MMX4_DIRECT_CHARACTER");
            if (value != NULL)
                character = (u8)strtoul(value, NULL, 0);
            value = getenv("MMX4_DIRECT_LOADOUT");
            if (value != NULL)
                loadout = (u8)strtoul(value, NULL, 0);
            value = getenv("MMX4_DIRECT_STORY");
            if (value != NULL)
                story = (u8)strtoul(value, NULL, 0);
            D_80173C80 = MAIN_ARCHIVE_ARENA;
            reset_game_engine();
            engine_obj.stage = 0xE;
            engine_obj.substage = 0;
            engine_obj.cur_character = character;
            func_80013014();
            func_800160AC();
            engine_obj.substage = 1;
            func_80013014();
            func_800160AC();
            func_80012EB8();
            reset_game_engine();
            engine_state_0(&engine_obj);
            engine_obj.stage = stage;
            engine_obj.substage = substage;
            engine_obj.cur_character = character;
            apply_direct_progress(stage, character, loadout, story);
            engine_obj.state = 4;
            engine_state_4(&engine_obj);
            engine_obj.checkpoint = checkpoint;
            func_800128B8(func_8001FB50);
            return;
        }
    }
#endif
    func_800128B8(&func_8001DAF8);
}

void func_8001D104(void)
{
}

void PlayCapcomLogo(void)
{
    func_800182E8(); // nop out to skip capcom logo
    SetDispMask(0);
}

void func_8001D134(void)
{
    func_80023D30();
    func_80016F0C();
    stop_sound(0xFF, 0);
    reset_objects();
    func_8002AB20();
}

void func_8001D178(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unkD = 0;
        arg0->mode++;
    }
}

void func_8001D1A4(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unkD = 1;
        func_8001D134();
        arg0->mode = 0;
        arg0->unk0++;
    }
}

void func_8001D1F0(struct GameInfo* arg0)
{
    if (arg0->mode == 0) {
        func_8001D230(arg0);
    } else {
        func_8001D284(arg0);
    }
}

void func_8001D230(struct GameInfo* arg0)
{
    arg0->unkD = 1;
    D_80173C80 = (u8*)0x80178000;
    func_80018000(1); // nop out to skip opening cinematic
    arg0->mode++;
}

void func_8001D284(struct GameInfo* arg0)
{
    arg0->unk0 = 1;
    arg0->mode = 0;
}

void func_8001D294(struct GameInfo* arg0)
{
    D_800F2170[arg0->mode](arg0);
}

void func_8001D2D0(struct GameInfo* arg0)
{
    arg0->unkD = 1;
    D_80141BDE[0] = 1;
    func_8001D134();
    reset_game_engine();
    func_80013890(D_800F2180[arg0->unkC], REPLAY_DATA);
    func_80014C70();
    func_80021E3C();
    func_80012EB8();
    func_80013014();
    arg0->unk4 = 0x960;
    arg0->mode++;
}

void func_8001D364(struct GameInfo* arg0)
{
    u32 var_s0;
    struct MiscObj* temp_v0;

    reset_objects();
    func_8002AB20();
    func_800160AC();
    func_80021E74();
    func_8002771C();
    func_80028BF0();
    func_80027850();
    func_80027D40();
    func_800281E8();
    player_spawn();
    func_80028DB4();
    func_80028F58();
    func_80023CE0();
    func_8001FDBC();
    for (var_s0 = 2; var_s0 < 5; var_s0++) {
        temp_v0 = find_free_misc_obj();
        if (temp_v0 != NULL) {
            temp_v0->active = 1;
            temp_v0->id = 0x12;
            temp_v0->unk2 = var_s0;
        }
    }
    func_8001FEC0();
    arg0->unk2 = 0;
    arg0->mode++;
    func_800129A4(8);
    func_80023D68();
}

void func_8001D460(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unkD = 0;
    }
    if (--arg0->unk4 == 0 || g_Player.active == 0 || g_Player.state == 3) {
        func_800129F0(8);
        func_80022074();
        arg0->mode++;
    } else {
        get_random();
        func_80021F34();
    }
    func_80023D68();
}

void func_8001D514(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unkD = 1;
        D_80141BDE[0] = 0;
        func_8001D134();
        reset_game_engine();
        arg0->unk0 = 3;
        arg0->mode = 0;
    } else {
        func_80023D68();
    }
}

void func_8001D57C(struct GameInfo* arg0)
{
    D_800F2184[arg0->mode](arg0);
    update_misc_objects();
    init_objects();
}

void func_8001D5C8(struct GameInfo* arg0)
{
    struct MiscObj* temp_v0;

    arg0->unkD = 1;
    func_8001D134();
    func_80012E80();
    func_800160F4();
    temp_v0 = find_free_misc_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 1;
        temp_v0->id = 0x15;
    }
    arg0->unk4 = 0x12C;
    func_800129A4(8);
    arg0->mode++;
}

void func_8001D64C(struct GameInfo* arg0)
{
    if (--arg0->unk4 == 0) {
        arg0->mode++;
        func_800129F0(8);
    }
}

void func_8001D698(struct GameInfo* arg0)
{
    arg0->unkD = 1;
    arg0->unk0 = 0;
    arg0->mode = 0;
    arg0->unk2 = 0;
    arg0->unk3 = 0;
    if (++arg0->unkC == 4) {
        arg0->unkC = 0;
    }
}

void func_8001D6DC(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (arg0->unkE == 1) {
            arg0->unk0 = 6;
        } else {
            arg0->unk0 = 1;
        }
        return;
    }

    switch (arg0->unkE) {
    case 0:
        break;
    case 1:
        update_misc_objects();
        func_80023D68();
        break;
    case 2:
        func_80023D68();
        break;
    case 3:
        update_misc_objects();
        init_objects();
        break;
    }
}

void func_8001D77C(struct GameInfo* arg0)
{
    D_800F2194[arg0->mode](arg0);
    update_misc_objects();
    func_8002A484();
    func_80023D68();
}

void func_8001D7D0(struct GameInfo* /* D_80173C70 */ arg0)
{
    u8 var_s0;
    struct MiscObj* temp_v0;

    D_80141BDE[0] = 0;
    func_80016F0C();
    stop_sound(0xFF, 0);
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 0;
    D_8013E188[0] = 0;
    D_8013E188[1] = 0;
    D_8013E188[2] = 0;
    D_8013E188[3] = 0;
    need_palette_load |= 1;
    reset_objects();
    for (var_s0 = 0;
#ifdef VERSION_JP
         var_s0 < 9;
#elif defined(MMX4_WIN32)
         var_s0 < 13;
#else
         var_s0 < 14;
#endif
         var_s0++) {
        temp_v0 = find_free_misc_obj();
        if (temp_v0 != NULL) {
            temp_v0->active = 1;
            temp_v0->id = 0x13;
            temp_v0->unk2 = D_800F21A0[var_s0];
        }
    }
    func_800129A4(8);
    arg0->mode++;
}

void func_8001D8DC(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (controller_state & PADLup) {
            func_8001540C(0, 0xC, 0);
            if (arg0->unk2 == 0) {
                arg0->unk2 = 2;
            } else {
                arg0->unk2--;
            }
        }
        if (controller_state & PADLdown) {
            func_8001540C(0, 0xC, 0);
            if (arg0->unk2 == 2) {
                arg0->unk2 = 0;
            } else {
                arg0->unk2++;
            }
        }
        if (controller_state & (PAD_CONFIRM | PADstart)) {
            func_8001540C(0, 0x22, 0);
            func_800129F0(8);
            arg0->mode++;
        }
    }
}

void func_8001D9D0(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        switch (arg0->unk2) {
        case 0:
            engine_obj.state = 0;
            engine_obj.unk1 = 0;
            engine_obj.unk2 = 0;
            engine_obj.unk3 = 0;
            func_80012740(1, &func_8001FB50);
            func_800127FC();
            return;
            break;
        case 1:
            arg0->unk0 = 7;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        default:
        case 2:
            arg0->unk0 = 8;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
            break;
        }
    }
}

// never called?
void func_8001DA70(void)
{
    func_80012740(1, &func_8001FB50);
    func_800127FC();
}

// never called?
void func_8001DAA0(void)
{
    func_80012740(1, &func_8001FB50);
    func_800127FC();
}

void func_8001DAD0(struct GameInfo* arg0)
{
    func_8001A9EC(&engine_obj);
}

void func_8001DAF8(void)
{
    s16 var_v1;

    game_info.unkD = 1;
    D_80141BDE[0] = 0;
    D_80141BE0 = 1;
    func_8001D134();
    while (1) {
        D_800F21B0[game_info.unk0](&game_info);
        if (game_info.unkD == 0) {
            var_v1 = game_info.unk0 != 1 ? 0x8F0 : 0x800;
            if (var_v1 & controller_state) {
                func_8001540C(0, 0x22, 0);
                game_info.unkD = 1;
                game_info.unkE = game_info.unk0;
                func_80012854(1);
                if (D_80141BDC[0] == 0) {
                    func_800129F0(8);
                }
                game_info.unk0 = 5;
                game_info.mode = 0;
                game_info.unk2 = 0;
                game_info.unk3 = 0;
            }
        }
        func_800127C8(1);
    }
}

void func_8001DC30(void)
{
    game_info.unk0 = 1;
    game_info.mode = 0;
    game_info.unk2 = 0;
    game_info.unk3 = 0;
    func_80012740(0, &func_8001DAF8);
}

void (*D_800F2170[4])(struct GameInfo*) = {
    func_8001D2D0,
    func_8001D364,
    func_8001D460,
    func_8001D514,
};

u8 D_800F2180[4] = { 0x50, 0x51, 0x52, 0x53 };

void (*D_800F2184[4])(struct GameInfo*) = {
    func_8001D5C8,
    func_8001D178,
    func_8001D64C,
    func_8001D1A4,
};

void (*D_800F2194[3])(struct GameInfo*) = {
    func_8001D7D0,
    func_8001D8DC,
    func_8001D9D0,
};

#ifdef VERSION_JP
u8 D_800F21A0[] = {
    0x00,
    0x01,
    0x02,
    0x05,
    0x07,
    0x09,
    0x0D,
    0x0E,
    0x0F,
    0x08,
    0x03,
    0x00,
};
#elif defined(MMX4_WIN32)
u8 D_800F21A0[] = {
    0x12, 0x13, 0x00, 0x0b, 0x0c, 0x06, 0x09, 0x02,
    0x0d, 0x0e, 0x0f, 0x10, 0x05, 0x00, 0x00, 0x00
};
#else
u8 D_800F21A0[] = {
    0x12, 0x13, 0x00, 0x0b, 0x0c, 0x07, 0x11, 0x09,
    0x02, 0x0d, 0x0e, 0x0f, 0x10, 0x05, 0x00, 0x00
};
#endif

void (*D_800F21B0[11])(struct GameInfo*) = {
    func_8001D1F0,
    func_8001E708,
    func_8001D294,
    func_8001D57C,
    func_8001D698,
    func_8001D6DC,
    func_8001D77C,
    func_8001F0BC,
    func_8001EC34,
    func_8001DAD0,
    func_8002A41C,
};

#ifdef VERSION_JP

extern void func_8001DF24_jp(struct GameInfo*);
extern void func_8001E194_jp(struct GameInfo*);

#endif
