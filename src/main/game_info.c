// GameInfo
// 8001D064..8001F118
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
            func_80012EB8();
            reset_game_engine();
            engine_obj.state = 3;
            engine_obj.stage = 0;
            engine_obj.substage = 0;
            engine_obj.cur_character = CHARACTER_X;
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
            engine_obj.checkpoint = checkpoint;
            engine_obj.cur_character = character;
            if (loadout == 1) {
                engine_obj.unk44 = 4;
                engine_obj.unk45 = 0x30;
                engine_obj.unk46 = 0x30;
                engine_obj.palette_flags = 0xFF;
                engine_obj.unk5A = 0xF0FF;
                engine_obj.unk5C[0] = 0xA0;
                engine_obj.unk5C[1] = 0xA0;
                engine_obj.unk5C[2] = 0x20;
                if (character == CHARACTER_X) {
                    engine_obj.unk47 = 0x0F;
                    engine_obj.unk48 = 2;
                }
            }
            engine_obj.state = 4;
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
    func_80015930(0xFF, 0);
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
    func_80035240();
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
    func_80015930(0xFF, 0);
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
    s32 var_v1;

    game_info.unkD = 1;
    D_80141BDE[0] = 0;
    D_80141BE0 = 1;
    func_8001D134();
    while (1) {
        D_800F21B0[game_info.unk0](&game_info);
        if (game_info.unkD == 0) {
            var_v1 = 0x800;
            if (game_info.unk0 != 1) {
                var_v1 = 0x8F0;
            }
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

struct QuadObj* func_8001DC7C(s8 arg0, s8 arg1)
{
    struct QuadObj* quad = find_free_quad_obj();
    if (quad != NULL) {
        quad->active = 1;
        quad->id = arg0;
        quad->unk2 = arg1;
        return quad;
    }
    return NULL;
}

void func_8001DCCC(struct GameInfo* arg0)
{
    arg0->unkD = 2;
    arg0->unkA = 0;
    func_8001D134();
    reset_game_engine();
    engine_obj.stage = 0xE;
    engine_obj.substage = 0;
    func_80013014();
    func_800160AC();
    reset_objects();
    func_8002AB20();
    func_80028BF0();
    func_8002771C();
    func_80023CE0();
    background_objects[0].unk3 = 0;
    background_objects[1].unk3 = 1;
    background_objects[2].unk3 = 0;
    need_palette_load |= 1;
#ifdef VERSION_JP
    func_8001DC7C(0xB, 0);
    func_8001DC7C(0xB, 1);
    func_8001DC7C(0xB, 5);
    func_8001DC7C(0xB, 9);
#else
    D_80139690 = OBJECT_HEADER(func_8001DC7C(0xB, 0xA));
#endif
    func_800129A4(8);
    arg0->unk4 = 0;
    arg0->mode++;
}

void func_8001DDB0(struct GameInfo* arg0)
{
    if (arg0->unk4 == 0) {
        func_8001663C(0x20, 0x7F);
        arg0->unk4 = 1;
    }
    if (D_80173C84 == 2) {
        arg0->unkD = 1;
#ifdef VERSION_JP
        D_80139690 = OBJECT_HEADER(func_8001DC7C(0xB, 2));
        func_8001DC7C(0xB, 3);
        func_8001DC7C(0xB, 4);
        arg0->unk4 = 0x3C;
#else
        arg0->unk4 = 0xA;
#endif
        arg0->mode++;
    }
}

void func_8001DE20(struct GameInfo* arg0)
{
    arg0->unk4--;
    if (arg0->unk4 == 0) {
#ifdef VERSION_JP
        arg0->unkA = 1;
        arg0->unk4 = 0x46;
#else
        arg0->unkA = 2;
#endif
        arg0->mode++;
    }
}

#ifdef VERSION_JP
extern s16 D_800F2368_jp[];
#else
extern s16 D_800F2204[];
#endif

#ifdef VERSION_JP
void func_8001DF24_jp(struct GameInfo* arg0)
{
    arg0->unk4--;
    if (arg0->unk4 == 0) {
        arg0->unkA = 2;
        arg0->mode++;
    }
    if (background_objects[1].x_pos.i.hi >= 10) {
        background_objects[1].x_pos.i.hi -= 9;
    }
}
#endif

void func_8001DE54(struct GameInfo* arg0)
{
    s16 temp_v0_2;
    s32 temp_v1;
    s16 var_a2;
    s16* var_a1;
    s32* var_a0;
    struct MiscObj* temp_v0;
#ifdef VERSION_JP
    struct MiscObj* first;
#else
    s32 saved_reg_s2;
#endif

    background_objects[1].x_pos.i.hi = 0x400;
    background_objects[1].unk4C = 1;
    if (D_80139690->state == 2) {
#ifdef VERSION_JP
        first = find_free_misc_obj();
        if (first != NULL) {
            first->id = 0x13;
            first->active = 1;
            first->unk2 = 0xA;
        }
#endif
        temp_v0 = find_free_misc_obj();
        if (temp_v0 != 0) {
            temp_v0->id = 0x1D;
            temp_v0->active = 1;
            temp_v0->unk2 = 0x20;
#ifdef VERSION_JP
            temp_v0->ext.unk.unk50 = (struct MiscUnk50_2*)first;
#else
            temp_v0->ext.unk.unk50 = (struct MiscUnk50_2*)saved_reg_s2;
#endif
            D_80139690 = OBJECT_HEADER(temp_v0);
        }
#ifdef VERSION_JP
        var_a1 = D_800F2368_jp;
#else
        var_a1 = D_800F2204;
#endif
        var_a0 = D_80169498.sector;
        var_a2 = 0;
        do {
            temp_v1 = *var_a1;
            var_a1 += 1;
            temp_v0_2 = var_a2 + 1;
            var_a2 = temp_v0_2;
            *var_a0 = temp_v1 << 0x10;
            var_a0++;
        } while (temp_v0_2 < 0x24);
        D_80169498.title.settled = 1;
        background_objects[0].unk3 = 1;
        arg0->mode++;
    }
}

void func_8001DF48(struct GameInfo* arg0)
{
    if (D_80139690->id == 0x13) {
#ifdef VERSION_JP
        ZeroObjectState(OBJECT_HEADER(((struct MiscObj*)D_80139690)->ext.pointer.unk50));
#endif
        arg0->unk4 = 0x32;
        arg0->mode++;
    }
}

void func_8001DF7C(struct GameInfo* arg0)
{
    struct EffectObj* obj;

    if (--arg0->unk4 == 0) {
        obj = find_free_effect_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 2;
            obj->unk2 = 0xC;
            D_80139690 = OBJECT_HEADER(obj);
        }
        arg0->unk4 = 0xA;
        arg0->mode++;
    }
#ifdef VERSION_JP
    background_objects[0].x_pos.i.hi += 6;
#endif
}

#ifdef VERSION_JP
void func_8001E194_jp(struct GameInfo* arg0)
{
    if (--arg0->unk4 == 0) {
        arg0->mode++;
    }
}
#endif

void func_8001E000(struct GameInfo* arg0)
{
#ifndef VERSION_JP
    if (arg0->unk4 != 0) {
        arg0->unk4--;
        return;
    }
#endif
    if (D_80139690->active == 0) {
        g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 0;
        D_8013E188[0] = 0;
        D_8013E188[1] = 0;
        D_8013E188[2] = 0;
        D_8013E188[3] = 0;
        need_palette_load |= 1;
        func_8001DC7C(0xC, 0);
        func_8001DC7C(0xC, 1);
        func_8001DC7C(0xC, 2);
        func_8001DC7C(0xC, 3);
        func_8001DC7C(0xC, 4);
        func_8001DC7C(0xC, 5);
        func_8001DC7C(0xC, 6);
        func_8001DC7C(0xC, 7);
        func_8001DC7C(0xC, 8);
        arg0->unk6 = 0x3C;
        background_objects[0].unk3 = 0;
        arg0->unkA = 0;
        arg0->mode++;
    }
#ifdef VERSION_JP
    background_objects[0].x_pos.i.hi += 11;
#endif
}

INCLUDE_ASM("main/nonmatchings/game_info", func_8001E130);

void func_8001E3FC(struct GameInfo* arg0)
{
    if (D_80139690->active == 0) {
#ifdef VERSION_JP
        arg0->unk4 = 6;
#else
        arg0->unk4 = 0x10;
        arg0->unk6 = 0;
#endif
        arg0->mode++;
#ifndef VERSION_JP
        SP_PALETTE[0x306 / 2] = 0x8000;
        need_palette_load |= 1;
#endif
    }
}

#ifndef VERSION_JP
void func_8001E458(struct GameInfo* arg0)
{
    s16 temp_a1;

    if (--arg0->unk4 == 0) {
        temp_a1 = arg0->unk6;
        if (temp_a1 != 0xE) {
            arg0->unk6++;
            SP_PALETTE[0x106 / 2] = D_800F21DC[temp_a1];
            arg0->unk4 = 6;
            need_palette_load |= 1;
            return;
        }
        arg0->unk4 = 1;
        arg0->mode++;
    }
}
#endif

#ifndef VERSION_JP
void func_8001E4F0(struct GameInfo* arg0)
{
    if (--arg0->unk4 == 0) {
        reset_objects();
        arg0->unk4 = 1;
        arg0->mode++;
    }
}
#endif

void func_8001E54C(struct GameInfo* /* D_80173C70 */ arg0)
{
    u32 var_s0;
    struct BaseObj* obj;

    if (--arg0->unk4 == 0) {
        obj = (struct BaseObj*)find_free_effect_obj();
        if (obj != NULL) {
            obj->active = 1;
            obj->id = 2;
            obj->unk2 = 0xD;
        }
        for (var_s0 = 0;
#ifdef VERSION_JP
             var_s0 < 5;
#else
             var_s0 < 9;
#endif
             var_s0++) {
            obj = (struct BaseObj*)find_free_misc_obj();
            if (obj != NULL) {
                obj->active = 1;
                obj->id = 0x13;
                obj->unk2 = D_800F21F8[var_s0];
            }
        }
        arg0->unk4 = 0x258;
        arg0->mode++;
        background_objects[2].unk3 = 1;
        arg0->unkD = 0;
    }
}

void func_8001E638(struct GameInfo* arg0)
{
    arg0->unk4--;
    if (arg0->unk4 == 0) {
        func_800129F0(8);
        arg0->mode++;
    }
}

void func_8001E690(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->mode++;
    }
}

void func_8001E6BC(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->unkD = 1;
        func_8001D134();
        arg0->mode = 0;
        arg0->unk0++;
    }
}

void func_8001E708(struct GameInfo* arg0)
{
    D_800F2294[arg0->mode](arg0);
    if (controller_state & PADstart && arg0->unkD == 1) {
        func_80016F0C();
        func_8001540C(0, 0x22, 0);
        arg0->mode = 0xC;
        g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 0;
        D_8013E188[0] = 0;
        D_8013E188[1] = 0;
        D_8013E188[2] = 0;
        D_8013E188[3] = 0;
        background_objects[0].unk3 = 0;
        background_objects[1].unk3 = 1;
        background_objects[2].unk3 = 0;
        need_palette_load |= 1;
        reset_objects();
        background_objects[1].x_pos.i.hi = 0x400;
        background_objects[1].unk4C = 1;
        arg0->unk4 = 1;
    }
    update_effect_objects();
    update_misc_objects();
    update_quad_objects();
    func_8002A484();
    func_80023D68();
}

s32 func_8001E850(u8* arg0, u8 arg1)
{
    s8 counter = 0;
    struct MiscObj* misc;

    if (arg0[0] != 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 1;
            misc->id = 0x20;
            misc->ext.pointer.unk50 = arg0;
            misc->x_pos.i.hi = arg0[0];
            misc->ext.title_logo.palette_shift_value = arg1;
            arg0++;
        }
    } else {
        arg0++;
    }

    while (arg0[0] != 0xFF) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 1;
            misc->id = 0x1F;
            misc->unk2 = arg0[0];
            arg0++;
            misc->unk7 = counter++;
#ifdef VERSION_JP
            misc->y_pos.i.hi = arg0[0];
#else
            misc->y_pos.i.hi = arg0[0] & 0xF0;
#endif
            misc->ext.title_logo.palette_shift_value = arg1;
            arg0++;
        }
    }
    return arg0[1];
}

void func_8001E954(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        arg0->mode++;
    }
}

void func_8001E980(u8 arg0)
{
    if (arg0 == 0) {
        LoadImage(&D_800F2388,
            (u_long*)(WINDOW_ARCHIVE_DATA + ((s32*)WINDOW_ARCHIVE_DATA)[1]));
    } else {
        need_palette_load |= 1;
    }
}

void func_8001E9E0(struct GameInfo* arg0)
{
    struct MiscObj* obj;

    reset_objects();
    obj = find_free_misc_obj();
    if (obj != 0) {
        obj->active = 1;
        obj->id = 0x1F;
        obj->unk2 = 0x56;
        obj->y_pos.i.hi = 0x80;
    }
    D_80141BDF[0] = 0;
    arg0->unk8 = func_8001E850(D_800F22F0, 0) & 0xFF;
    background_objects[0].unk3 = 0;
    background_objects[1].unk3 = 0;
    background_objects[2].unk3 = 0;
    func_8001E980(0);
    func_800129A4(8);
    arg0->mode++;
}

void func_8001EA90(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (controller_state & (PADstart | PAD_SELECTION_ALT)) {
            func_800129F0(8);
            D_80141BDF[0] = 2;
            arg0->mode++;
            return;
        }
        if ((controller_state & PAD_CONFIRM) && D_80141BDF[0] != 1) {
            func_8001540C(0, 0x22, 0);
            func_800129F0(8);
            arg0->mode++;
            return;
        }
        func_800204CC(D_80141BDF, arg0->unk8);
        if ((controller_state & (PADLleft | PADLright | PAD_CONFIRM)) && D_80141BDF[0] == 1) {
            func_8001540C(0, 0xC, 0);
            D_80171EA9 ^= 1;
            func_800153D4(D_80171EA9);
        }
    }
}

INCLUDE_ASM("main/nonmatchings/game_info", func_8001EBA0);

void func_8001EC34(struct GameInfo* arg0)
{
    D_800F2390[arg0->mode](arg0);
    update_misc_objects();
    func_8002A484();
    func_80016124();
    func_80023D68();
}

void func_8001EC90(struct GameInfo* arg0)
{
    reset_objects();
    D_80141BDF[0] = 0;
    if (D_800F1D90.save.character != 0xFF) {
        arg0->unk8 = func_8001E850(D_800F22D0, 0) & 0xFF;
        arg0->mode = arg0->mode + 1;
    } else {
        arg0->unk8 = func_8001E850(D_800F22E0, 0) & 0xFF;
        arg0->mode = arg0->mode + 3;
    }
    background_objects[0].unk3 = 0;
    background_objects[1].unk3 = 0;
    background_objects[2].unk3 = 0;
    func_8001E980(0);
    func_800129A4(8);
}

void func_8001ED44(struct GameInfo* arg0)
{
    if (*D_80141BDC == 0) {
        if (controller_state & PAD_CONFIRM) {
            func_8001540C(0, 0x22, 0);
            if (D_80141BDF[0] != 1) {
                func_800129F0(8);
            }
            arg0->mode = (u8)arg0->mode + 1;
#ifdef VERSION_JP
        } else if (controller_state & PADRdown) {
#else
        } else if (controller_state & PADRup) {
#endif
            func_800129F0(8);
            D_80141BDF[0] = 2;
            arg0->mode = (u8)arg0->mode + 1;
        } else {
            func_800204CC(D_80141BDC + 3, arg0->unk8);
        }
    }
}

void func_8001EE08(struct GameInfo* arg0)
{
    if (D_80141BDC[0] == 0) {
        if (D_80141BDF[0] != 1) {
            func_8001E980(1);
        }
        {
            s32 state = (u8)D_80141BDC[3];

            if (state != 1) {
                if (state < 2 && state == 0) {
                    func_8001C30C(&D_800F1D90.save);
                    engine_obj.state = 1;
                    engine_obj.unk1 = 6;
                    engine_obj.unk2 = 0;
                    engine_obj.unk3 = 0;
                    func_80012740(1, &func_8001FB50);
                    func_800127FC();
                    return;
                }
            } else {
                arg0->unk0 = 9;
                engine_obj.unk1 = 0;
                engine_obj.unk2 = 0;
                engine_obj.unk3 = 0;
                return;
            }
            background_objects[0].unk4C = 1;
            background_objects[1].unk4C = 1;
            background_objects[2].unk4C = 1;
            background_objects[1].unk3 = 1;
            background_objects[2].unk3 = 1;
            background_objects[2].x_pos.i.hi = 0;
            arg0->unk0 = 6;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
        }
    }
}

void func_8001EF48(struct GameInfo* arg0)
{
    if (D_80141BDC[0] != 0) {
        return;
    }

    if (controller_state & PAD_CONFIRM) {
        func_8001540C(0, 0x22, 0);
        if (D_80141BDF[0] != 0) {
            func_800129F0(8);
        }
#ifdef VERSION_JP
    } else if (controller_state & PADRdown) {
#else
    } else if (controller_state & PADRup) {
#endif
        func_800129F0(8);
        D_80141BDF[0] = 2;
    } else {
        return;
    }

    arg0->mode++;
}

void func_8001EFF0(struct GameInfo* arg0)
{
    struct TransitionState* transition;

    transition = (struct TransitionState*)D_80141BDC;
    if (D_80141BDC[0] == 0) {
        if ((transition->selection == 0) || (func_8001E980(1), D_80141BDF[0] == 0)) {
            arg0->unk0 = 9;
            engine_obj.unk1 = 0;
            engine_obj.unk2 = 0;
            engine_obj.unk3 = 0;
        } else {
            background_objects[0].unk4C = 1;
            background_objects[1].unk4C = 1;
            background_objects[2].unk4C = 1;
            background_objects[1].unk3 = 1;
            background_objects[2].unk3 = 1;
            background_objects[2].x_pos.i.hi = 0;
            arg0->unk0 = 6;
            arg0->mode = 0;
            arg0->unk2 = 0;
            arg0->unk3 = 0;
        }
    }
}

void func_8001F0BC(struct GameInfo* arg0)
{
    D_800F239C[arg0->mode](arg0);
    update_misc_objects();
    func_8002A484();
    func_80016124();
    func_80023D68();
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
u8 D_800F21F8[4] = { 0x00, 0x01, 0x04, 0x07 };
s16 D_800F21DC[2] = { 0x0809, 0x0000 };

s16 D_800F2368_jp[12] = {
    -176,
    -220,
    308,
    -220,
    374,
    -220,
    792,
    -220,
    -77,
    -143,
    176,
    -154,
};

u8 D_800F2380_jp[] = {
    0x97,
    0x01,
    0x50,
    0xFF,
    0xDA,
    0xFD,
    0xB5,
    0x02,
    0x71,
    0xFF,
    0x73,
    0x02,
};

s16 D_800F2204[18] = {
    -110,
    693,
    110,
    605,
    363,
    583,
    -22,
    693,
    484,
    693,
    11,
    187,
    220,
    0,
    275,
    242,
    66,
    429,
};

s16 D_800F23B0_jp[18] = {
    181,
    27,
    225,
    27,
    231,
    27,
    269,
    27,
    190,
    34,
    213,
    33,
    234,
    31,
    147,
    110,
    184,
    104,
};

s16 D_800F224C[18] = {
    187,
    110,
    207,
    102,
    230,
    100,
    195,
    110,
    241,
    110,
    198,
    64,
    217,
    47,
    222,
    69,
    203,
    86,
};

extern void func_8001DF24_jp(struct GameInfo*);
extern void func_8001E194_jp(struct GameInfo*);

void (*D_800F2294[15])(struct GameInfo*) = {
    func_8001DCCC,
    func_8001E690,
    func_8001DDB0,
    func_8001DE20,
    func_8001DF24_jp,
    func_8001DE54,
    func_8001DF48,
    func_8001DF7C,
    func_8001E194_jp,
    func_8001E000,
    func_8001E130,
    func_8001E3FC,
    func_8001E54C,
    func_8001E638,
    func_8001E6BC,
};

u8 D_800F22D0[16] = { 0x20, 0x03, 0x80, 0x04, 0xA0, 0x00, 0x10, 0x01, 0x30, 0x02, 0x40, 0x05, 0xD0, 0xFF, 0x01, 0x00 };
u8 D_800F22E0[16] = { 0x20, 0x04, 0xA0, 0x03, 0x80, 0x00, 0x10, 0x01, 0x30, 0x02, 0x40, 0x05, 0xD0, 0xFF, 0x00, 0x00 };
u8 D_800F22F0[16] = { 0x40, 0x54, 0x40, 0x55, 0x70, 0x58, 0xB0, 0x53, 0x10, 0x05, 0xD0, 0xFF, 0x02, 0x00, 0x00, 0x00 };
u8 D_800F2300[16] = { 0x50, 0x2A, 0x40, 0x2B, 0x60, 0x2C, 0x90, 0x29, 0x10, 0x72, 0xD0, 0xFF, 0x02, 0x00, 0x00, 0x00 };
u8 D_800F2474_jp[4] = { 0x50, 0x2E, 0x70, 0x2C };
#else
s16 D_800F21DC[14] = {
    0x8442,
    0x8C84,
    0x94C6,
    0x9908,
    0xA16B,
    0xA9AD,
    0xADEF,
    0xB631,
    0xBE73,
    0xC6D6,
    0xCB18,
    0xD35A,
    0xDB9C,
    0xE3FF,
};

u8 D_800F21F8[] = {
    0x12, 0x13, 0x00, 0x0b, 0x0c, 0x04, 0x07, 0x09, 0x11, 0, 0, 0
};

s16 D_800F2204[36] = {
    -154,
    -297,
    319,
    -297,
    429,
    -297,
    869,
    -297,
    -77,
    -187,
    176,
    -220,
    473,
    -242,
    -605,
    649,
    -220,
    605,
    -154,
    649,
    132,
    572,
    396,
    572,
    -11,
    649,
    473,
    649,
    11,
    154,
    231,
    -33,
    275,
    154,
    77,
    308,
};

s16 D_800F224C[36] = {
    169,
    26,
    212,
    26,
    222,
    26,
    262,
    26,
    176,
    36,
    199,
    33,
    229,
    31,
    128,
    112,
    163,
    108,
    169,
    112,
    195,
    105,
    219,
    105,
    182,
    112,
    226,
    112,
    184,
    67,
    204,
    50,
    208,
    67,
    190,
    81,
};

void (*D_800F2294[15])(struct GameInfo*) = {
    func_8001DCCC,
    func_8001E690,
    func_8001DDB0,
    func_8001DE20,
    func_8001DE54,
    func_8001DF48,
    func_8001DF7C,
    func_8001E000,
    func_8001E130,
    func_8001E3FC,
    func_8001E458,
    func_8001E4F0,
    func_8001E54C,
    func_8001E638,
    func_8001E6BC,
};

u8 D_800F22D0[16] = {
    0x40,
    0x03,
    0x70,
    0x73,
    0x98,
    0x00,
    0x10,
    0x01,
    0x30,
    0x02,
    0x40,
    0x05,
    0xD0,
    0xFF,
    0x01,
    0x00,
};

u8 D_800F22E0[16] = {
    0x40,
    0x73,
    0x98,
    0x03,
    0x70,
    0x00,
    0x10,
    0x01,
    0x30,
    0x02,
    0x40,
    0x05,
    0xD0,
    0xFF,
    0x00,
    0x00,
};

u8 D_800F22F0[16] = {
    0x58,
    0x54,
    0x40,
    0x55,
    0x70,
    0x58,
    0xB0,
    0x53,
    0x10,
    0x05,
    0xD0,
    0xFF,
    0x02,
    0x00,
    0x00,
    0x00,
};

u8 D_800F2300[16] = {
    0x40,
    0x2A,
    0x40,
    0x2B,
    0x60,
    0x2C,
    0x90,
    0x29,
    0x10,
    0x72,
    0xD0,
    0xFF,
    0x02,
    0x00,
    0x00,
    0x00,
};
#endif

#ifdef VERSION_JP
u8 D_800F2310[12] = { 0x90, 0x29, 0x10, 0x2D, 0x40, 0x72, 0xD0, 0xFF, 1, 0, 0, 0 };
u8 D_800F231C[12] = { 0x50, 0x30, 0x40, 0x2C, 0x70, 0x2F, 0x10, 0x72, 0xD0, 0xFF, 1, 0 };
#else
u8 D_800F2310[12] = { 0x40, 0x2E, 0x40, 0x2C, 0x70, 0x29, 0x10, 0x72, 0xD0, 0xFF, 1, 0 };
u8 D_800F231C[12] = { 0x40, 0x2E, 0x40, 0x2C, 0x70, 0x2F, 0x10, 0x72, 0xD0, 0xFF, 1, 0 };
#endif

#ifdef VERSION_JP
#define GAME_INFO_ALT_X 0x50
#define GAME_INFO_ALT_Y 0x30
#else
#define GAME_INFO_ALT_X 0x40
#define GAME_INFO_ALT_Y 0x2E
#endif

u8 D_800F2328[16] = {
    GAME_INFO_ALT_X,
    GAME_INFO_ALT_Y,
    0x40,
    0x31,
    0x60,
    0x2A,
    0x80,
    0x2C,
    0xB0,
    0x2F,
    0x10,
    0x72,
    0xD0,
    0xFF,
    0x03,
    0x00,
};

struct GameInfoAuxData D_800F2338 = {
#ifdef VERSION_JP
    {
        { 0x50, 0x30, 0x40, 0x31, 0x60, 0x2C, 0x90, 0x2F, 0x10, 0x72, 0xD0, 0xFF, 2, 0, 0, 0 },
        { 0x40, 0x5D, 0x70, 0x5C, 0x90, 0x59, 0x10, 0x2D, 0x40, 5, 0xD0, 0xFF, 2, 0, 0 },
        { 0x78, 0x51, 0x70, 0x52, 0x90, 0x59, 0x10, 0x5A, 0x40, 5, 0xD0, 0xFF, 2, 0, 0 },
    },
#else
    {
        { 0x40, 0x2E, 0x40, 0x31, 0x60, 0x2C, 0x90, 0x2F, 0x10, 0x72, 0xD0, 0xFF, 2, 0, 0, 0 },
        { 0x70, 0x5B, 0x70, 0x5C, 0x90, 0x59, 0x10, 0x5A, 0x40, 0x72, 0xD0, 0xFF, 2, 0, 0, 0 },
        { 0x80, 0x51, 0x70, 0x52, 0x90, 0x59, 0x10, 0x78, 0x40, 0x72, 0xD0, 0xFF, 2, 0, 0, 0 },
    },
#endif
    {
        0x0C000020,
        0x14001000,
        0x24001C00,
        0x28012400,
        0x30212C01,
        0x3C413821,
        0x4C604441,
        0x58805060,
    },
};

RECT D_800F2388 = { 0, 480, 256, 2 };

void (*D_800F2390[3])(struct GameInfo*) = {
    func_8001E9E0,
    func_8001EA90,
    func_8001EBA0,
};

void (*D_800F239C[5])(struct GameInfo*) = {
    func_8001EC90,
    func_8001ED44,
    func_8001EE08,
    func_8001EF48,
    func_8001EFF0,
};
