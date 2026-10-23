#include "common.h"
#include "main/objects.h"
#include "main/1263C.h"
#include "main/128C4.h"
#include "main/14A60.h"
#include "main/55C4.h"
#ifdef MMX4_SATURN
#include "main/13A8C.h"
extern struct DialogueGlyphData D_801396C8;
#include "weapon_resources.h"
#include "saturn/game_low.h"
#define DIALOGUE_TEXTURE(index, high) \
    ((u16)(((((saturn_stage_graphics_offsets_pointer[index] >> 7) + ((high) ? SATURN_DIALOGUE_HIGH_TEXTURE : 0)) << 7) + SATURN_DIALOGUE_TEXTURE_BASE) >> 3))
#define DIALOGUE_PAD_PRESSED (saturn_pad_pressed & SATURN_DIALOGUE_PAD_MASK)
#else
#define DIALOGUE_PAD_PRESSED (*(u8*)&controller_input.pressed)
#endif

#ifdef MMX4_PC
#include <psyz/audio.h>
#include <psyz/spu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif
void func_80016F0C();
extern u8 D_800F2B5C[21][12];
extern u8 D_800F2C58[];
extern u8 D_800F2D18[];
extern u32 D_800F2F08[12];
extern u32 D_800F2F38[2];
extern union AnimationStep D_800F2F60[];
extern union AnimationStep D_800F3000[10];
extern union AnimationStep D_800F3028[11];
extern union AnimationStep D_800F3054[10];
extern union AnimationStep* D_800F307C[3];
extern s16 D_800F3088[16];
extern s16 D_800F30A8[16];
extern struct HudSpriteOrigin D_800F30F4[8];
extern struct PlayerGaugePosition D_800F3124[2];

void func_80021DBC(s16* arg0, s16* arg1, s32 arg2);

void func_80021E3C(void);

#ifdef MMX4_PC
struct SerializedEngineObj {
    s8 state, unk1, unk2, unk3;
    s16 unk4;
    s8 unk6, unk7;
    s16 unk8, unkA;
    s8 stage, substage, unkE, unkF;
    s8 unk10, unk11, unk12, unk13;
    s8 unk14, unk15, unk16, unk17;
    s8 unk18, unk19, unk1A, unk1B;
    s8 gameplay_locked, checkpoint, unk1E, unk1F;
    u32 boss_ptr;
    s8 enable_boss, unk25;
    union EngineCharacterState character_state;
    s8 unk36, unk37;
    u32 unk38, unk3C;
    u8 unk40;
    s8 unk41;
    u8 unk42;
    s8 cur_character, player_lives;
    u8 checkpoint_hp;
    s8 max_hp, armor_parts, arm_type;
    s8 player_initial_data[0x10];
    s8 palette_flags;
    u16 collected_upgrades;
    s8 sub_tanks[3];
    u8 unk5F, unk60;
    u8 pad61[3];
};

_Static_assert(sizeof(struct SerializedEngineObj) == 0x64,
    "replay engine state must use the PSX layout");

struct ReplayData {
    u32 frame;
    s32 flags;
    u16 random;
    u16 padA;
    struct SerializedEngineObj initial_engine;
    struct SerializedEngineObj saved_engine;
    u16 inputs[0xE10];
};

#define PSX_MAIN_OBJECTS_ADDRESS 0x8013BED0
#define PSX_MAIN_OBJ_SIZE 0x9C

struct MainObj* restore_replay_main_object(u32 address);

u32 save_replay_main_object(struct MainObj* object);

void restore_replay_engine(const struct SerializedEngineObj* source);

void save_replay_engine(struct SerializedEngineObj* target);
#else
struct ReplayData {
    u32 frame;
    s32 flags;
    u16 random;
    u16 padA;
    struct EngineObj initial_engine;
    struct EngineObj saved_engine;
    u16 inputs[0xE10];
};
#define REPLAY_SAVED_ENGINE (((struct ReplayData*)REPLAY_DATA)->saved_engine)
#endif

void func_80021E74(void);

void func_80022074(void);

void func_800220C4(void)
{
    struct ReplayData* replay = (struct ReplayData*)REPLAY_DATA;

    replay->frame = 0;
    replay->flags = main_bss_state.frame_counter;
    replay->random = cur_random;
#ifdef MMX4_PC
    save_replay_engine(&replay->initial_engine);
#else
    replay->initial_engine = engine_obj;
#endif
}
void func_80022138(void)
{
    struct ReplayData* replay = (struct ReplayData*)REPLAY_DATA;
    s32 frame;

    frame = replay->frame;
    if (frame != 0xE10) {
        replay->inputs[frame] = g_Player.input.buttons.held;
        replay->frame += 1;
    }
}
// start_dialogue
#ifdef MMX4_SATURN
static void hide_dialogue_part(struct MiscObj* part)
{
    if (part != NULL && part->id == 0x16) {
        part->active = 0;
        part->on_screen = 0;
    }
}

static void copy_dialogue_palette(u16* dst, const u16* src, u32 count)
{
    u32 i;

    for (i = 0; i < count; i++) {
        dst[i] = src[i];
    }
}

void func_8002217C(arg_u16 message, u8 portrait, s32 delay_only)
{
    struct MiscObj* window;
    u16* dialogue_palette;
    u8 track;

    if (abc_object.unkC != 0) {
        if (abc_object.unkC != 0x80) {
            hide_dialogue_part(D_801397C0);
            hide_dialogue_part(D_801397C4);
            hide_dialogue_part(D_801397CC);
            hide_dialogue_part(D_801397C8);
            hide_dialogue_part(D_801397D4);
            hide_dialogue_part(D_801397D0);
            abc_object.unkC = 0x80;
            abc_object.unkA = 0x27;
            abc_object.unkD = 4;
        }
        abc_object.unk10 = message | 0x8000;
        return;
    }
    abc_object.unkC = 0x80;
    abc_object.unk10 = 0;
    D_801397D8 = portrait;
    D_801397BC = D_801397C0 = D_801397C4 = D_801397C8 = NULL;
    D_801397CC = D_801397D0 = D_801397D4 = NULL;
    abc_object.unkE = 0;
    if (delay_only) {
        abc_object.unkA = 0x3C;
        abc_object.unkD = 6;
        return;
    }
    D_80139828 = engine_obj.enable_boss;
    D_80139824 = engine_obj.unk1F;
    engine_obj.unk1F = 0;
    engine_obj.enable_boss = 0;
    dialogue_palette = saturn_color_ram + (engine_obj.stage == 0xD ? SATURN_DIALOGUE_FORTRESS_PALETTE : SATURN_DIALOGUE_PALETTE);
    copy_dialogue_palette(D_801397E4, dialogue_palette, 0x20);
    copy_dialogue_palette(dialogue_palette, SATURN_DIALOGUE_WINDOW_PALETTE, 0x20);
    if (!(portrait & 0x80)) {
        D_801397DC = (struct Func80022730Config*)(D_800F2DD0[(u8)engine_obj.cur_character] + portrait * sizeof(struct Func80022730Config));
        if (engine_obj.cur_character == 0) {
            copy_dialogue_palette(saturn_color_ram + (D_801397DC->unk3 * 4 + SATURN_DIALOGUE_PORTRAIT_PALETTE) * 16, D_800F2F40, 16);
        }
    }
    need_palette_load |= 1;
    abc_object.unk0 = (u16*)((u8*)SATURN_DIALOGUE_MESSAGES + SATURN_DIALOGUE_MESSAGES[message]);
    abc_object.unk4 = *abc_object.unk0;
    abc_object.unk6 = -0x78;
    abc_object.unk8 = 0x1D;
    abc_object.unkF = 1;
    D_801397E0 = 0;
    window = find_free_misc_obj();
    if (window != NULL) {
        D_801397BC = window;
        window->active = 1;
        window->id = 0x16;
        window->unk2 = 2;
        window->unk16 = 0x11;
        window->animation_table = (u32**)saturn_dialogue_window_animations;
        window->unk40 = SATURN_DIALOGUE_WINDOW_TEXTURE;
        window->unk42 = engine_obj.stage == 0xD ? SATURN_DIALOGUE_FORTRESS_WINDOW_PALETTE : SATURN_DIALOGUE_WINDOW_PALETTE_INDEX;
        window->unk3C = (u8*)SATURN_OPTION_CURSOR_FRAMES + *(s32*)SATURN_OPTION_CURSOR_FRAMES;
        window->bg_offset = -1;
        window->x_pos.i.hi = 0xA0;
        if (!(abc_object.unk4 & 0x800)) {
            saturn_dialogue_flags = SATURN_DIALOGUE_TOP;
            window->y_pos.i.hi = portrait == 0x80 ? 0x74 : 0x3C;
        } else {
            saturn_dialogue_flags = SATURN_DIALOGUE_BOTTOM;
            window->y_pos.i.hi = portrait == 0xFF ? 0xB4 : 0xAC;
        }
        window->unk15 = 0;
        set_animation(window, 0);
    }
    if (engine_obj.cur_character == 0) {
        if (message >= SATURN_DIALOGUE_X_TRACK_FIRST) {
            track = saturn_dialogue_tracks[message - SATURN_DIALOGUE_X_TRACK_FIRST];
        } else if (message == SATURN_DIALOGUE_CAPSULE_MESSAGE) {
            track = SATURN_DIALOGUE_CAPSULE_TRACK;
        } else {
            track = SATURN_DIALOGUE_KEEP_TRACK;
        }
    } else {
        if (message >= SATURN_DIALOGUE_ZERO_TRACK_FIRST) {
            track = saturn_dialogue_tracks[SATURN_DIALOGUE_X_TRACKS + message - SATURN_DIALOGUE_ZERO_TRACK_FIRST];
        } else if (message == SATURN_DIALOGUE_CAPSULE_MESSAGE) {
            track = SATURN_DIALOGUE_CAPSULE_TRACK;
        } else {
            track = SATURN_DIALOGUE_KEEP_TRACK;
        }
    }
    if (track != SATURN_DIALOGUE_KEEP_TRACK) {
        if (track == SATURN_DIALOGUE_STOP_TRACK) {
            saturn_music_stop();
        } else {
            saturn_music_play(track, 0);
        }
    }
    abc_object.unkA = 0x27;
    abc_object.unkD = 0;
}

#else
INCLUDE_ASM("main/nonmatchings/128C4", func_8002217C);
#endif
void func_8002328C(struct AbcObj*);

#define CONFIG D_801397DC

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/128C4", func_80022730);
#else
void func_80022730(struct AbcObj* arg0)
{
    s32 charOffset;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v0;
    signed long temp_v1;
    u16 temp_a2;
    struct MiscObj* obj;
    u8* readyText;
    u16 value;
    u16* src;
    u16* dst;

    switch (arg0->unkD) {
    case 0:
        value = --arg0->unkA;

        if ((value << 0x10) == 0) {
            if (!(D_801397D8 & 0x80)) {
                readyText = D_800F2DD8[engine_obj.cur_character][D_801397D8];

                obj = find_free_misc_obj();
                if (obj != NULL) {
                    obj->active = 0x41;
                    obj->id = 0x16;
                    obj->unk2 = 5;
                    obj->unk15 = 0;
                    obj->bg_offset = -1;

                    if (CONFIG->unk5 != 0) {
                        obj->x_pos.i.hi = 0xA0;
                    } else {
                        obj->x_pos.i.hi = 0x50;
                    }

                    obj->y_pos.i.hi = 0x48;
                    obj->unk16 = 0x10;

                    obj->animation_table = D_800F2EE8[engine_obj.cur_character];

#ifdef MMX4_SATURN
                    obj->unk40 = DIALOGUE_TEXTURE(CONFIG->unk0 + engine_obj.cur_character + 2, CONFIG->unk4);
                    obj->unk42 = CONFIG->unk3 * 4 + engine_obj.cur_character + 0x1A;
#else
                    if (CONFIG->unk4 != 0) {
                        obj->unk40 = (D_801406A8[CONFIG->unk0 + engine_obj.cur_character + 2] >> 7) + 0xB0;
                    } else {
                        obj->unk40 = D_801406A8[CONFIG->unk0 + engine_obj.cur_character + 2] >> 7;
                    }

                    temp_v1 = CONFIG->unk3 * 4;
                    charOffset = engine_obj.cur_character + 0x1A;
                    temp_v1 += charOffset;

                    temp_v0 = temp_v1;
                    if (temp_v1 < 0) {
                        temp_v0 = temp_v1 + 0xF;
                    }

                    temp_a0 = temp_v0 >> 4;
                    temp_v0 = temp_a0 << 4;
                    temp_a1 = temp_v1 - temp_v0;

                    obj->unk42 = temp_a1 | ((temp_a0 + 0x1E0) << 6);
#endif

                    temp_v0 = func_8002938C(engine_obj.cur_character + 0x91);

                    temp_v1 = (signed long)SP_MENU_FRAMES;
                    temp_v0 = ((s32*)temp_v1)[temp_v0];

                    obj->ext.pointer.unk50 = readyText;
                    obj->state = 0;
                    temp_v1 += temp_v0;
                    obj->unk3C = (void*)temp_v1;

                    if ((engine_obj.armor_parts & 3) == 3) {
                        obj->ext.title_logo
                            .palette_shift_speed
                            = 6;
                    } else if (engine_obj.armor_parts & 1) {
                        obj->ext.title_logo
                            .palette_shift_speed
                            = 2;
                    } else if (engine_obj.armor_parts & 2) {
                        obj->ext.title_logo
                            .palette_shift_speed
                            = 4;
                    } else {
                        obj->ext.title_logo
                            .palette_shift_speed
                            = 0;
                    }

                    obj->ext.title_logo
                        .palette_shift_value
                        = 0;

                    set_animation(
                        obj,
                        (s32)(s8)obj->ext.title_logo
                            .palette_shift_speed);
                }

                D_801397C8 = obj;

                obj = find_free_misc_obj();
                if (obj != NULL) {
                    obj->active = 0x41;
                    obj->id = 0x16;
                    obj->unk2 = 4;
                    obj->unk15 = 0;
                    obj->bg_offset = -1;

                    if (CONFIG->unk5 != 0) {
                        obj->x_pos.i.hi = 0xA0;
                    } else {
                        obj->x_pos.i.hi = 0x50;
                    }

                    value = 0x48;
                    obj->y_pos.i.hi = value;

                    value = 0x11;
                    obj->unk16 = value;

                    obj->animation_table = D_800F2EE8[6];

#ifdef MMX4_SATURN
                    obj->unk40 = DIALOGUE_TEXTURE(CONFIG->unk0, CONFIG->unk4);
                    obj->unk42 = CONFIG->unk3 * 4 + 0x18;
#else
                    if (CONFIG->unk4 != 0) {
                        obj->unk40 = (D_801406A8[CONFIG->unk0] >> 7) + 0xB0;
                    } else {
                        obj->unk40 = D_801406A8[CONFIG->unk0] >> 7;
                    }

                    value = CONFIG->unk3;
                    temp_v0 = value * 4;

                    temp_v1 = temp_v0 + 0x18;
                    temp_a2 = temp_v1;

                    if (temp_v1 < 0) {
                        temp_a2 = temp_v0 + 0x27;
                    }

                    temp_a1 = value + 6;
                    temp_v1 -= temp_a2 & 0x7F0;

                    if (temp_a1 < 0) {
                        temp_a1 = value;
                        temp_a1 += 9;
                    }

                    obj->unk42 = temp_v1 | (((temp_a1 >> 2) + 0x1E0) << 6);
#endif

                    temp_v0 = func_8002938C(0x97);
                    temp_v1 = (signed long)SP_MENU_FRAMES;
                    temp_v0 = ((s32*)temp_v1)[temp_v0];

                    obj->state = 0;
                    temp_v1 += temp_v0;
                    obj->unk3C = (void*)temp_v1;

                    set_animation(obj, 0);
                }

                D_801397D0 = obj;

                if (CONFIG->unk5 == 0) {
#ifdef MMX4_SATURN
                    saturn_dialogue_flags |= SATURN_DIALOGUE_TWO_SPEAKERS;
#endif
                    obj = find_free_misc_obj();

                    if (obj != NULL) {
                        obj->active = 0x41;
                        obj->id = 0x16;
                        obj->unk2 = 3;
                        obj->bg_offset = -1;
                        obj->unk15 = 0;
                        obj->unk16 = 0x10;
                        obj->x_pos.i.hi = 0xF0;
                        obj->y_pos.i.hi = 0x48;

                        obj->animation_table = D_800F2EE8[CONFIG->unk2 - 0x91];

#ifdef MMX4_SATURN
                        obj->unk40 = DIALOGUE_TEXTURE(CONFIG->unk1, CONFIG->unk4);
                        obj->unk42 = CONFIG->unk3 * 4 + 0x19;
#else
                        if (CONFIG->unk4 != 0) {
                            obj->unk40 = (D_801406A8[CONFIG->unk1] >> 7) + 0xB0;
                        } else {
                            obj->unk40 = D_801406A8[CONFIG->unk1] >> 7;
                        }

                        value = CONFIG->unk3;
                        temp_v0 = value * 4;

                        temp_a0 = temp_v0 + 0x19;
                        temp_a2 = temp_a0;

                        if (temp_a0 < 0) {
                            temp_a2 = temp_v0 + 0x28;
                        }

                        temp_v1 = value + 6;
                        temp_a0 -= temp_a2 & 0x7F0;

                        if (temp_v1 < 0) {
                            temp_v1 = value + 9;
                        }

                        obj->unk42 = temp_a0 | (((temp_v1 >> 2) + 0x1E0) << 6);
#endif

                        temp_v0 = func_8002938C(CONFIG->unk2);

                        temp_v1 = (signed long)SP_MENU_FRAMES;
                        temp_v0 = ((s32*)temp_v1)[temp_v0];

                        obj->state = 0;
                        obj->ext.pointer.unk50 = readyText;

                        obj->ext.title_logo
                            .palette_shift_value
                            = 0;

                        temp_v1 += temp_v0;
                        obj->unk3C = (void*)temp_v1;

                        set_animation(obj, 0);
                    }

                    D_801397CC = obj;

                    obj = find_free_misc_obj();

                    if (obj != NULL) {
                        obj->active = 0x41;
                        obj->id = 0x16;
                        obj->unk2 = 4;
                        obj->unk15 = PLAYER_FACING_RIGHT;
                        obj->bg_offset = -1;

                        *(volatile s16*)&obj->x_pos.i.hi = 0xF0;

                        *(volatile s16*)&obj->y_pos.i.hi = 0x48;

                        *(volatile u8*)&obj->unk16 = 0x11;

                        obj->animation_table = D_800F2EE8[6];

#ifdef MMX4_SATURN
                        obj->unk40 = DIALOGUE_TEXTURE(CONFIG->unk0, CONFIG->unk4);
                        obj->unk42 = CONFIG->unk3 * 4 + 0x18;
#else
                        if (CONFIG->unk4 != 0) {
                            obj->unk40 = (D_801406A8[CONFIG->unk0] >> 7) + 0xB0;
                        } else {
                            obj->unk40 = D_801406A8[CONFIG->unk0] >> 7;
                        }

                        value = CONFIG->unk3;
                        temp_v0 = value * 4;

                        temp_v1 = temp_v0 + 0x18;
                        temp_a2 = temp_v1;

                        if (temp_v1 < 0) {
                            temp_a2 = temp_v0 + 0x27;
                        }

                        temp_a1 = value + 6;
                        temp_v1 -= temp_a2 & 0x7F0;

                        if (temp_a1 < 0) {
                            temp_a1 = value + 9;
                        }

                        obj->unk42 = temp_v1 | (((temp_a1 >> 2) + 0x1E0) << 6);
#endif

                        temp_v0 = func_8002938C(0x97);

                        temp_v1 = (signed long)SP_MENU_FRAMES;
                        temp_v0 = ((s32*)temp_v1)[temp_v0];

                        obj->state = 0;
                        temp_v1 += temp_v0;
                        obj->unk3C = (void*)temp_v1;

                        set_animation(obj, 0);
                    }

                    D_801397D4 = obj;
                }
            }

            arg0->unkC = 1;
            arg0->unkD = 1;
            return;
        }

    default:
        return;

    case 1:
        func_8002328C(arg0);
        return;

    case 2:
        if (DIALOGUE_PAD_PRESSED != 0) {
            arg0->unkF = 0;
        }

        value = --arg0->unkA;

        if ((value << 0x10) == 0) {
            arg0->unkD = 1;
            return;
        }
        break;

    case 3:
        if (DIALOGUE_PAD_PRESSED != 0) {
            if ((D_801397C4 != NULL) && (D_801397C4->id == 0x16)) {
                D_801397C4->active = 0;
                D_801397C4->on_screen = 0;
            }

            if (arg0->unk4 & 0x8000) {
                if ((D_801397C0 != NULL) && (D_801397C0->id == 0x16)) {
                    D_801397C0->active = 0;
                    D_801397C0->on_screen = 0;
                }

                if ((D_801397CC != NULL) && (D_801397CC->id == 0x16)) {
                    D_801397CC->active = 0;
                    D_801397CC->on_screen = 0;
                }

                if ((D_801397D4 != NULL) && (D_801397D4->id == 0x16)) {
                    D_801397D4->active = 0;
                    D_801397D4->on_screen = 0;
                }

                if ((D_801397C8 != NULL) && (D_801397C8->id == 0x16)) {
                    D_801397C8->active = 0;
                    D_801397C8->on_screen = 0;
                }

                if (D_801397D0 != NULL) {
                    if (D_801397D0->id == 0x16) {
                        D_801397D0->active = 0;
                        D_801397D0->on_screen = 0;
                    }
                }

                arg0->unkA = 0x27;
                arg0->unkD = 4;
                arg0->unkC = 0x80;
                return;
            }

            D_801397E0 = 0;
            arg0->unkC = 1;
            arg0->unk6 = -0x78;
            arg0->unk8 = 0x1D;
            arg0->unkE = (u8)(arg0->unkE + 1);

            func_8002328C(arg0);
            return;
        }
        break;

    case 4:
        value = --arg0->unkA;

        if ((value << 0x10) == 0) {
#ifdef MMX4_SATURN
            if (engine_obj.stage != 0xD) {
                dst = saturn_color_ram + SATURN_DIALOGUE_PALETTE;
            } else {
                dst = saturn_color_ram + SATURN_DIALOGUE_FORTRESS_PALETTE;
            }
#else
            if (engine_obj.stage != 0xD) {
                dst = SP_PALETTE + 0x150;
            } else {
                dst = SP_PALETTE + 0x3E0;
            }
#endif

            src = D_801397E4;
            temp_a0 = 0;

            do {
                *dst = *src;
                src += 1;
                temp_a0 += 1;
                dst += 1;
            } while (temp_a0 < 0x20);

            need_palette_load |= 1;

            engine_obj.enable_boss = D_80139828;
            engine_obj.unk1F = D_80139824;

            if ((D_801397BC != NULL) && (D_801397BC->id == 0x16)) {
                D_801397BC->active = 0;
                D_801397BC->on_screen = 0;
            }

            if ((D_801397C0 != NULL) && (D_801397C0->id == 0x16)) {
                D_801397C0->active = 0;
                D_801397C0->on_screen = 0;
            }

            if ((D_801397C4 != NULL) && (D_801397C4->id == 0x16)) {
                D_801397C4->active = 0;
                D_801397C4->on_screen = 0;
            }

            if ((D_801397CC != NULL) && (D_801397CC->id == 0x16)) {
                D_801397CC->active = 0;
                D_801397CC->on_screen = 0;
            }

            if ((D_801397C8 != NULL) && (D_801397C8->id == 0x16)) {
                D_801397C8->active = 0;
                D_801397C8->on_screen = 0;
            }

            if ((D_801397D4 != NULL) && (D_801397D4->id == 0x16)) {
                D_801397D4->active = 0;
                D_801397D4->on_screen = 0;
            }

            if (D_801397D0 != NULL) {
                if (D_801397D0->id == 0x16) {
                    D_801397D0->active = 0;
                    D_801397D0->on_screen = 0;
                }
            }

            arg0->unkE = 0;
            arg0->unkD = 5;
            goto block_110;
        }
        break;

    case 6:
        value = --arg0->unkA;

        if ((value << 0x10) != 0) {
            return;
        }

    block_110:
        arg0->unkC = 0;
        break;
    }
}

#ifdef MMX4_SATURN
void func_8002328C(struct AbcObj* arg0)
{
    struct MiscObj* text;
    u8 skip;

    do {
        arg0->unk4 = *arg0->unk0;
        if ((arg0->unk4 & 0x1FF) != 0x1FF) {
            if (D_801397E0 == 0 && D_801397C0 == NULL) {
                text = find_free_misc_obj();
                if (text != NULL) {
                    D_801397C0 = text;
                    text->active = 1;
                    text->id = 0x16;
                    text->unk2 = 0;
                    text->unk16 = 0x10;
                    text->unk40 = SATURN_DIALOGUE_TEXT_TEXTURE;
                    text->unk3C = &D_801396C8.count;
                    text->unk42 = engine_obj.stage == 0xD ? SATURN_DIALOGUE_FORTRESS_TEXT_PALETTE : SATURN_DIALOGUE_TEXT_PALETTE;
                    text->bg_offset = -1;
                    text->x_pos.val = 0xA00000;
                    if (!(arg0->unk4 & 0x800)) {
                        text->y_pos.val = D_801397D8 == 0x80 ? 0x380000 : 0;
                    } else {
                        text->y_pos.val = D_801397D8 == 0xFF ? 0x780000 : 0x700000;
                    }
                    text->animation_step.fields.frame_index = 0;
                    text->unk15 = 0;
                }
                D_801396C8.active = 1;
            }
            D_801396C8.glyphs[D_801397E0].frame = 0;
            D_801396C8.glyphs[D_801397E0].character = (u8)arg0->unk4;
            D_801396C8.glyphs[D_801397E0].x = (u8)arg0->unk6;
            D_801396C8.glyphs[D_801397E0].y = (u8)arg0->unk8;
            D_801397E0++;
            D_801396C8.count = D_801397E0;
        }
        arg0->unk0++;
        if (arg0->unk4 & 0x4000) {
            arg0->unk8 += 0x12;
            arg0->unk6 = -0x78;
        } else {
            arg0->unk6 += 0xC;
        }
        if (arg0->unkF == 0) {
            arg0->unk4 &= 0xEFFF;
        }
    } while (!(arg0->unk4 & 0xB000));
    func_8001540C(0, SATURN_SOUND(0xE, 0x14), 0);
    if ((arg0->unk4 & 0xB000) == 0x1000) {
        if (DIALOGUE_PAD_PRESSED != 0 && arg0->unkF != 0) {
            arg0->unkF--;
        }
        arg0->unkA = 4;
        arg0->unkD = 2;
        return;
    }
    arg0->unkF = 2;
    if (arg0->unk4 & 0x2000) {
        text = find_free_misc_obj();
        if (text != NULL) {
            D_801397C4 = text;
            text->active = 1;
            text->id = 0x16;
            text->unk2 = 1;
            text->unk16 = 0x10;
            text->unk40 = SATURN_DIALOGUE_ARROW_TEXTURE;
            text->unk3C = D_800F2F38;
            text->unk42 = engine_obj.stage == 0xD ? SATURN_DIALOGUE_FORTRESS_TEXT_PALETTE : SATURN_DIALOGUE_TEXT_PALETTE;
            text->bg_offset = -1;
            text->x_pos.i.hi = 0x98;
            if (!(arg0->unk4 & 0x800)) {
                text->y_pos.i.hi = D_801397D8 == 0x80 ? 0x85 : 0x4D;
            } else {
                text->y_pos.i.hi = D_801397D8 == 0xFF ? 0xC5 : 0xBD;
            }
            text->animation_step.fields.frame_index = 0;
            text->unk15 = 0;
            text->ext.title_logo.palette_shift_speed = 0;
            text->ext.ready_text.stay_up_timer = 0x20;
        }
    }
    arg0->unkC = 0xFF;
    arg0->unkD = 3;
}
#endif
#endif
